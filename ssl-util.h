/**
  ******************************************************************************
  * @file    ssl-util.c
  * @author  Dragon.Chen
  * @version V1.0.2
  * @date    01-15-2013
  * @brief   SSL操作相关函数
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#ifndef __SSL_UTIL__H__
#define __SSL_UTIL__H__

#include "includes.h"

#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

/**
  * @brief	获取SSL错误
  * @param	arg1:错误等级  arg2:错误的发动者
  * @retval NULL
  */
void GetLastSslErrorMessage(int level, const char *who);

/**
  * @brief  客户端ssl初始化
  * @param	arg1 ra_info
  * @retval 成功为TRUE，否则FALSE
  */
BOOL ssl_client_init(RA_INFO *ra_info);

/**
  * @brief  客户端链接ssl
  * @param  arg1 ra_info
  * @retval 成功返回SSL，否则返回NULL
  */
SSL *ssl_client_negotiate(RA_INFO *ra_info);

/**
  * @brief  客户端释放占用资源
  * @param  arg1:cpi  arg2: serfd
  * @retval NULL
  */
void client_release_resource(RA_INFO *ri, int serfd);


/**
  * @brief  服务器ssl初始化
  * @param  arg1 server_info
  * @retval 成功为TRUE，否则FALSE
  */
BOOL ssl_server_init(SERVER_INFO *server_info);

/**
  * @brief  服务器接受链接ssl
  * @param  arg1 server_info
  * @retval 成功返回SSL，否则返回NULL
  */
SSL *ssl_server_negotiate(SERVER_INFO *server_info);

/**
  * @brief  服务器释放占用资源
  * @param  arg1:cpi  arg2: serfd
  * @retval NULL
  */
void server_release_resource(RA_INFO *ri, int cltfd);


#endif

/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
