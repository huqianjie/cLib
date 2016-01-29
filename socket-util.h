/**
  ******************************************************************************
  * @file    socket-util.h
  * @author  Dragon.Chen
  * @version V1.0.2
  * @date    11-08-2013
  * @brief   socketͨ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ </center></h2>
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
  * @brief  ����socket����״̬
  * @param  arg1:fd 
  * @retval	�ɹ�����0, ʧ�ܷ���-1
  */
int setblocking(int fd);

/**
  * @brief  ����������Ϊ������״̬
  * @param  arg1:fd  arg2:���
  * @retval	�ɹ�����0, ʧ�ܷ���-1
  */
int setnonblocking(int fd);

/**
  * @brief  ��ʼ���ͻ���socket
  * @param  arg1 ip  arg2 port
  * @retval ���ؼ���fd,ʧ�ܳ���exit
  */
int tcp_client(const char *ip, int port);

/**
  * @brief  ��ʼ��������socket
  * @param  arg1 port
  * @retval ���ؼ���fd,ʧ�ܳ���exit
  */
int tcp_server(int port);

/**
  * @brief  ���ļ��������ж�ȡn���ֽ�����
  * @param  arg1 socket������  arg2 ������ָ��  arg3 ��ȡ���ݵĴ�С
  * @retval ���ض�ȡ�����ֽ���
  */
ssize_t readn(int fd, void *vptr, size_t n);

/**
  * @brief  ���ļ���������дn���ֽ�����
  * @param  arg1 socket������  arg2 ������ָ��  arg3 д���ݵĴ�С
  * @retval ����д����ֽ���
  */
ssize_t writen(int fd, const void *vptr, size_t n);

#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/


















