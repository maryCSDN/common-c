/* windows system */
#ifdef _WIN32


#include <winsock2.h>
#include <Windows.h>
 
#pragma comment(lib,"ws2_32.lib")
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
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
 
	bind(sock, (sockaddr*)&serverAddr, sizeof(sockaddr));
	
	char buf[512];
	while (TRUE)
	{
		memset(buf, 0, 512);
		// 网络节点的信息，用来保存客户端的网络信息
		sockaddr_in clientAddr;
		memset(&clientAddr, 0, sizeof(sockaddr_in));
 
		int clientAddrLen = sizeof(sockaddr);
		//接收客户端发来的数据
		int ret = recvfrom(sock, buf, 512, 0,(sockaddr*) &clientAddr,&clientAddrLen );
		
		printf("Recv msg:%s from IP:[%s] Port:[%d]\n", buf,inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
		// 发一个数据包返回给客户
		sendto(sock, "Hello World!", strlen("Hello World!"), 0, (sockaddr*)&clientAddr, clientAddrLen);
		printf("Send msg back to IP:[%s] Port:[%d]\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
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
    unsigned int path_size = GetEnvironmentVariable(USER_HOME_WIN, home_path, LOG_DEFAULT_PATH_SIZE);
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
    
    strcpy(conf_path, home_path);
    return conf_path;
}

#endif
