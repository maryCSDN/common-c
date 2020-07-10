/* windows system */
#ifdef _WIN32

#include <stdio.h>
#include <fcntl.h>
#include <winsock2.h>
#include <Windows.h>
 
#include "_cmlogwrap.h"

/* log 系统调用API */
int log_server_start(void)
{
    //初始化网络环境
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		log_error("log server start failed, WSAStartup failed");
		return -1;
	}
 
	//建立一个UDP的socket
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == SOCKET_ERROR)
	{
		log_error("log server start failed, create socket failed");
		return -1;
	}
 
	//绑定地址信息
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(LOG_SERV_PORT);
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
 
	bind(sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
	
	log_info("log server start.");
	char log_cache[LOG_FORMAT_SIZE];
	while (TRUE)
	{
		memset(log_cache, 0, LOG_FORMAT_SIZE);
		struct sockaddr_in client_addr;
		memset(&client_addr, 0, sizeof(struct sockaddr_in));
 
		int client_addr_len = sizeof(struct sockaddr);
		recvfrom(sock, log_cache, LOG_FORMAT_SIZE, 0, (struct sockaddr*) &client_addr,&client_addr_len );
		printf("%s", log_cache);
	}
	return 0;
}

int log_server_restart();
int log_server_stop();
int log_server_status();

char *log_server_conf_path(char *dest_buf)
{
    if (dest_buf == null)
    {
        log_error("The parameter to get the configuration file path cannot be null (this parameter is the user stores processing results)");
        return null;
    }

    char home_path[LOG_DEFAULT_PATH_SIZE] = {0};
    unsigned int path_size = GetEnvironmentVariable(LOG_CONF_HOME_WIN, home_path, LOG_DEFAULT_PATH_SIZE);
    if (path_size == 0 || path_size > LOG_DEFAULT_PATH_SIZE)
    {
        // 当前用户家目录获取失败
        log_error("Configuration file path is too long [%d]", GetLastError());
        return null;
    }
    
    sprintf(home_path, "%s\\%s\\%s", home_path, LOG_CONF_SUB_DIR, LOG_CONF_NAME);
    int fd = open(home_path, O_RDONLY);
    if (fd < 0)
    {
        log_error("Failed to open configuration file, path:[%s]", home_path);
        return null;
    }
    close(fd);
    
    strcpy(dest_buf, home_path);
    return dest_buf;
}

#endif
