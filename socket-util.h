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

#ifndef __SOCKET_UTIL__H__
#define __SOCKET_UTIL__H__

#include "includes.h"
#include "commom.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  设置socket阻塞状态
  * @param  arg1:fd 
  * @retval	成功返回0, 失败返回-1
  */
int setblocking(int fd);

/**
  * @brief  设置描述符为非阻塞状态
  * @param  arg1:fd  arg2:标记
  * @retval	成功返回0, 失败返回-1
  */
int setnonblocking(int fd);

/**
  * @brief  初始化客户端socket
  * @param  arg1 ip  arg2 port
  * @retval 返回监听fd,失败程序exit
  */
int tcp_client(const char *ip, int port);

/**
  * @brief  初始化服务器socket
  * @param  arg1 port
  * @retval 返回监听fd,失败程序exit
  */
int tcp_server(int port);

/**
  * @brief  从文件描述符中读取n个字节数据
  * @param  arg1 socket描述符  arg2 缓冲区指针  arg3 读取数据的大小
  * @retval 返回读取到的字节数
  */
ssize_t readn(int fd, void *vptr, size_t n);

/**
  * @brief  往文件描述符中写n个字节数据
  * @param  arg1 socket描述符  arg2 缓冲区指针  arg3 写数据的大小
  * @retval 返回写入的字节数
  */
ssize_t writen(int fd, const void *vptr, size_t n);

#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/


















