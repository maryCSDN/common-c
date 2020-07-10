/* windows system */
#ifdef _WIN32

#include <stdio.h>
#include <fcntl.h>
#include <winsock2.h>
#include <Windows.h>
 
#include "_cmlogwrap.h"

/* 1. 检查cmlog是否已经启动 */
/* 2. 检查配置文件是否存在，并获取配置文件路径 */
/* 3. 读取配置信息或赋默认值 */
/* 4. 获取配置信息 */
/* 5. 初始化配置信息到共享内存 */

/* log 系统调用API */
int log_server_start()
{
    //初始化网络环境
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("WSAStartup failed\n");
		return -1;
	}
 
	//建立一个UDP的socket
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == SOCKET_ERROR)
	{
		printf("create socket failed\n");
		return -1;
	}
 
	//绑定地址信息
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(LOG_SERV_PORT);
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
 
	bind(sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
	
	char log_cache[LOG_FORMAT_SIZE];
	while (TRUE)
	{
		memset(log_cache, 0, LOG_FORMAT_SIZE);
		// 网络节点的信息，用来保存客户端的网络信息
		struct sockaddr_in client_addr;
		memset(&client_addr, 0, sizeof(struct sockaddr_in));
 
		int client_addr_len = sizeof(struct sockaddr);
		//接收客户端发来的数据
		recvfrom(sock, log_cache, LOG_FORMAT_SIZE, 0, (struct sockaddr*) &client_addr,&client_addr_len );
		printf("%s", log_cache);
		//printf("Recv msg:%s from IP:[%s] Port:[%d]\n", buf,inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
		// 发一个数据包返回给客户
		//sendto(sock, "Hello World!", strlen("Hello World!"), 0, (sockaddr*)&clientAddr, clientAddrLen);
		//printf("Send msg back to IP:[%s] Port:[%d]\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	}
	return 0;

    // 1. 
    // 2.
    // 3.
    // 4.
    // 5.
    // 6.
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
