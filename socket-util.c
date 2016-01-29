/**
  ******************************************************************************
  * @file    socket-util.h
  * @author  Dragon.Chen
  * @version V1.0.2
  * @date    11-08-2013
  * @brief   socket通用函数接口
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#include "socket-util.h"

/**
  * @brief  设置socket阻塞状态
  * @param  arg1:fd 
  * @retval	成功返回0, 失败返回-1
  */
int setblocking(int fd)
{
#ifdef USE_WIN32
	u_long val = 0;

	if (ioctlsocket(fd, FIONBIO, &val) != 0)
		return -1;
	return 0;
#elif defined (USE_LINUX)
	int val;

	if ( (val = fcntl(fd, F_GETFL, 0)) < 0)
		return -1;
	val &= ~O_NONBLOCK;
	if (fcntl(fd, F_SETFL, val) < 0)
		return -1;
	return 0;
#endif
}

/**
  * @brief  设置socket非阻塞状态
  * @param  arg1:fd 
  * @retval	成功返回0, 失败返回-1
  */
int setnonblocking(int fd)
{
#ifdef USE_WIN32
	u_long val = 1;

	if (ioctlsocket(fd, FIONBIO, &val) != 0)
	{
		GetLastSocketErrorMessage(LOG_ERROR, "[setnonblocking:ioctlsocket]");
		return -1;
	}
	return 0;
#elif defined (USE_LINUX)
	int val;

	if ( (val = fcntl(fd, F_GETFL, 0)) < 0)
		return -1;
	val |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, val) < 0)
		return -1;
	return 0;
#endif
}

/**
  * @brief  初始化客户端socket
  * @param  arg1 ip  arg2 port
  * @retval 返回监听fd,失败程序exit
  */
int tcp_client(const char *ip, int port)
{
    int serfd;
    struct sockaddr_in sin;

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(ip);

    if ( (serfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        GetLastSocketErrorMsg(LOG_FATAL, "[socket]");
        return -1;
    }

    if ( connect(serfd, (struct sockaddr*)&sin, sizeof(sin)) <0)
    {
        closesocket(serfd);
        GetLastSocketErrorMsg(LOG_FATAL, "[connect]");
        return -1;
    }

    return serfd;
}

/**
  * @brief  初始化服务器socket
  * @param  arg1 port
  * @retval 返回监听fd,失败程序exit
  */
int tcp_server(int port)
{
    int serfd;
    int flag = 1;
    struct sockaddr_in sin;

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;

    if ( (serfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        GetLastSocketErrorMsg(LOG_FATAL, "[tcp_server:socket]");
    }

    if (setsockopt(serfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)))
    {
        closesocket(serfd);
        GetLastSocketErrorMsg(LOG_FATAL, "[tcp_server:setsockopt]");
    }

    if (setnonblocking(serfd) != 0)
    {
        closesocket(serfd);
        MSG(LOG_ERROR, "[tcp_server:setnonblocking] Fail to set serfd nonblocking!");
    }

    if (bind(serfd, (struct sockaddr*)&sin, sizeof(sin)))
    {
        closesocket(serfd);
        GetLastSocketErrorMsg(LOG_FATAL, "[tcp_server:bind]");
    }

    if ( listen(serfd, 5))
    {
        closesocket(serfd);
        GetLastSocketErrorMsg(LOG_FATAL, "[tcp_server:listen]");
    }

    return serfd;
}

/**
  * @brief  从文件描述符中读取n个字节数据
  * @param  arg1 socket描述符  arg2 缓冲区指针  arg3 读取数据的大小
  * @retval 返回读取到的字节数
  */
ssize_t readn(int fd, void *vptr, size_t n)
{
    size_t  nleft;
    ssize_t nread;
    char   *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0)
    {
        if ( (nread = read(fd, ptr, nleft)) < 0)
        {
            if (errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if (nread == 0)
            break;

        nleft -= nread;
        ptr += nread;
    }
    return (n - nleft);
}

/**
  * @brief  往文件描述符中写n个字节数据
  * @param  arg1 socket描述符  arg2 缓冲区指针  arg3 写数据的大小
  * @retval 返回写入的字节数
  */
ssize_t writen(int fd, const void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0)
    {
        if ( (nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return (n);
}


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/


















