/* windows system */
#ifdef _WIN32

#include "_cmlogwrap.h"

/* log color */
#define COLOR_DEFAULT               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07)   /* 正常 */
#define COLOR_INFO                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02)   /* 绿色 */
#define COLOR_WARN                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x06)   /* 黄色 */
#define COLOR_ERROR                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04)   /* 红色 */

static const char *g_log_level[LOG_OFF + 1] = {"ON", "DEBUG", "INFO", "WARN", "ERROR", "OFF"};
static char g_module[LOG_MODULE_SIZE] = {0};
static level_t g_level = LOG_ON;
static bool g_init_flag = false;
static SOCKET g_sock;
static struct sockaddr_in g_log_serv;

static void _cvlog(level_t level, const char *_file, const char *_func, int _line, const char *format, va_list args);
static bool _log_init_ipc(void);

void _log_debug(const char *file, const char *func, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    _cvlog(LOG_DEBUG, file, func, line, format, args);
    va_end(args);
}

void _log_info(const char *file, const char *func, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    COLOR_INFO;
    _cvlog(LOG_INFO, file, func, line, format, args);
    COLOR_DEFAULT;
    va_end(args);
}

void _log_warn(const char *file, const char *func, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    COLOR_WARN;
    _cvlog(LOG_WARN, file, func, line, format, args);
    COLOR_DEFAULT;
    va_end(args);
}

void _log_error(const char *file, const char *func, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    COLOR_ERROR;
    _cvlog(LOG_ERROR, file, func, line, format, args);
    COLOR_DEFAULT;
    va_end(args);
}

int log_init(const char *module)
{
    if (module == null)
    {
        log_warn("log init failed, param module is null");
        return -1;
    }

    if (strlen(g_module) > 0)
    {
        log_warn("log init failed, already initialized");
        return -1;
    }

    if (strlen(module) > LOG_MODULE_SIZE - 1)
    {
        log_warn("log init failed, module len too long");
        return -1;
    }

    if (!_log_init_ipc())
    {
        log_warn("log init failed, ipc init failed");
        return -1;
    }

    strcpy(g_module, module);
    g_init_flag = true;
    return 0;
}

void log_set_level(level_t level)
{
    if (level > LOG_OFF || level < LOG_ON)
    {
        log_warn("The log level you set is illegal");
    }
    else
    {
        g_level = level;
    }
}

static void _cvlog(level_t level, const char *_file, const char *_func, int _line, const char *format, va_list args)
{
    time_t _date;
    _date = time(&_date);
    struct tm *date = localtime(&_date);
    char _format[LOG_FORMAT_SIZE] = {0};
    char log_msg[LOG_FORMAT_SIZE] = {0};
    if (!g_init_flag)
    {
        sprintf(_format, LOG_FORMAT, date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec, 
            LOG_MODULE_SYSVALUE, g_log_level[level], _file, _func, _line, format);
    }
    else
    {
        sprintf(_format, LOG_FORMAT, date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec, 
            g_module, g_log_level[level], _file, _func, _line, format);
    }
    
    vsprintf(log_msg, _format, args);
    if (level >= g_level)
    {
        printf("%s", log_msg);
    }
    
    if (g_init_flag)
    {
        sendto(g_sock, log_msg, strlen(log_msg), 0, (SOCKADDR*)&g_log_serv, sizeof(SOCKADDR));
    }
}

static bool _log_init_ipc(void)
{
    WSADATA WSAData;
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
    {
        log_warn("log init ipc failed, winsocket error");
        return false;
    }
    g_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    g_log_serv.sin_family = AF_INET;
    g_log_serv.sin_port = htons(LOG_SERV_PORT);
    g_log_serv.sin_addr.S_un.S_addr = inet_addr(LOG_SERV_IP);

    return true;
}

#endif  