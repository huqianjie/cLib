/**
  ******************************************************************************
  * @file    ssl-util.h
  * @author  Dragon.Chen
  * @version V1.0.2
  * @date    01-15-2013
  * @brief   SSL操作相关函数
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#include "ssl-util.h"

/**
  * @brief	获取SSL错误
  * @param	arg1:错误等级  arg2:错误的发动者
  * @retval NULL
  */
void GetLastSslErrorMessage(int level, const char *who)
{
	char *str = NULL;
    char *msg = NULL;
	const char *eptr = NULL;

	eptr = ERR_reason_error_string(ERR_get_error());
#ifdef USE_WIN32_SAFE
    msg = _strdup(eptr == NULL ? "unknow ssl error" : eptr);
#else
	msg = strdup(eptr == NULL ? "unknow ssl error" : eptr);
#endif
    if ( (str = (char*)malloc((size_t)(strlen(msg) + (who == NULL ? 0 : strlen(who)) + 20))) == NULL)
        return;

    sprintf(str, "%s %s", (who == NULL ? "" : who), msg);
	MSG(level, "%s", str);
	free(msg);
	free(str);
}

/**
  * @brief  客户端ssl初始化
  * @param	arg1:cpi
  * @retval 成功为TRUE，否则FALSE
  */
BOOL ssl_client_init(RA_INFO *ra_info)
{
    SSL_library_init();
	SSL_load_error_strings();
	SSLeay_add_ssl_algorithms();
	ERR_load_crypto_strings();

	/********* 初始化SSL_CTX结构，并设置SSL协议算法 */
	if ( (ra_info->ssl_ctx = SSL_CTX_new(SSLv23_client_method())) == NULL)
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_client_init:SSL_CTX_new]");
		return FALSE;
	}

    ////////////////////////////////////////////////////////////////////////////
    /********* 载入客户端证书 */
    if (SSL_CTX_use_certificate_file(ra_info->ssl_ctx, ra_info->cert_crt, SSL_FILETYPE_PEM) <= 0)
    {
        GetLastSslErrorMessage(LOG_ERROR, "[ssl_client_init:SSL_CTX_use_certificate_file]");
        goto cleanup;
    }

    /********* 载入客户端私钥 */
    if (SSL_CTX_use_PrivateKey_file(ra_info->ssl_ctx, ra_info->cert_key, SSL_FILETYPE_PEM) <= 0)
    {
        GetLastSslErrorMessage(LOG_ERROR, "[ssl_client_init:SSL_CTX_use_PrivateKey_file]");
        goto cleanup;
    }

    /********* 检查用户私钥是否正确 */
    if (!SSL_CTX_check_private_key(ra_info->ssl_ctx))
    {
        GetLastSslErrorMessage(LOG_ERROR, "[ssl_client_init:SSL_CTX_check_private_key]");
        goto cleanup;
    }

    ////////////////////////////////////////////////////////////////////////////
	/********* 加载证书 */
	if (SSL_CTX_load_verify_locations(ra_info->ssl_ctx, ra_info->root_crt, NULL) != 1)
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_client_init:SSL_CTX_load_verify_locations]");
		goto cleanup;
	}

	/********* 验证服务器 */
	SSL_CTX_set_verify(ra_info->ssl_ctx, SSL_VERIFY_PEER, NULL);
	SSL_CTX_set_verify_depth(ra_info->ssl_ctx, 1);

	return TRUE;

cleanup:
    SSL_CTX_free(ra_info->ssl_ctx);
    ra_info->ssl_ctx = NULL;
    return FALSE;
}

/**
  * @brief  客户端ssl协商
  * @param  cpi
  * @retval 成功返回SSL，否则返回NULL
  */
SSL *ssl_client_negotiate(RA_INFO *ra_info)
{
	/********* 新建SSL结构变量 */
	if ( (ra_info->ssl = SSL_new(ra_info->ssl_ctx) ) == NULL)
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_client_negotiate:SSL_new]");
		return NULL;
	}

	/********* 为SSL设置socket连接句柄 */
#ifndef THIS_IS_SERVER
	if ( SSL_set_fd(ra_info->ssl, ra_info->serfd) != 1)
#else
    if ( SSL_set_fd(ra_info->ssl, ra_info->cltfd) != 1)
#endif
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_client_negotiate:SSL_set_fd]");
		goto cleanup;
	}
	/********* 建立SSL连接 */
	if ( SSL_connect(ra_info->ssl)!= 1)
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_client_negotiate:SSL_connect]");
		if ( SSL_shutdown(ra_info->ssl) != 1 )
			GetLastSslErrorMessage(LOG_ERROR, "[ssl_client_negotiate:SSL_shutdown]");
		goto cleanup;
	}

	return ra_info->ssl;

cleanup:
    SSL_free(ra_info->ssl);
    ra_info->ssl = NULL;
    return NULL;
}

/**
  * @brief  客户端释放占用资源
  * @param  arg1:cpi  arg2: serfd
  * @retval NULL
  */
void client_release_resource(RA_INFO *ri, int serfd)
{
    SSL_shutdown(ri->ssl);
    SSL_free(ri->ssl);
    ri->ssl = NULL;
    closesocket(serfd);
    SSL_CTX_free(ri->ssl_ctx);
    ri->ssl_ctx = NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
  * @brief  服务器ssl初始化
  * @param  arg1 server_info
  * @retval 成功为TRUE，否则FALSE
  */
BOOL ssl_server_init(SERVER_INFO *server_info)
{
    SSL_library_init();
	SSL_load_error_strings();
	SSLeay_add_ssl_algorithms();
	ERR_load_crypto_strings();

	/********* 初始化SSL_CTX结构，并设置SSL协议算法 */
	if ( (server_info->ssl_ctx = SSL_CTX_new(SSLv23_server_method())) == NULL)
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_server_init:SSL_CTX_new]");
		return FALSE;
	}

    ////////////////////////////////////////////////////////////////////////////
	/********* 设置服务器证书 */
	if (SSL_CTX_use_certificate_file(server_info->ssl_ctx, server_info->cert_crt, SSL_FILETYPE_PEM) <= 0)
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_server_init:SSL_CTX_use_certificate_file]");
		goto cleanup;
	}

	/********* 设置服务器私钥 */
	if (SSL_CTX_use_PrivateKey_file(server_info->ssl_ctx, server_info->cert_key, SSL_FILETYPE_PEM) <= 0)
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_server_init:SSL_CTX_use_PrivateKey_file]");
		goto cleanup;
	}

	/********* 检查私钥和证书是否匹配 */
	if (!SSL_CTX_check_private_key(server_info->ssl_ctx))
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_server_init:SSL_CTX_check_private_key]");
		goto cleanup;
	}

    ////////////////////////////////////////////////////////////////////////////
    /********* 加载CA证书 */
	if (SSL_CTX_load_verify_locations(server_info->ssl_ctx, server_info->root_crt, NULL) != 1)
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_client_init:SSL_CTX_load_verify_locations]");
		goto cleanup;
	}

	/********* 验证服务器 */
	SSL_CTX_set_verify(server_info->ssl_ctx, SSL_VERIFY_PEER, NULL);
	SSL_CTX_set_verify_depth(server_info->ssl_ctx, 1);

	return TRUE;

cleanup:
    SSL_CTX_free(server_info->ssl_ctx);
    server_info->ssl_ctx = NULL;
    return FALSE;
}

/**
  * @brief  服务器接受链接ssl
  * @param  arg1 server_info
  * @retval 成功返回SSL，否则返回NULL
  */
SSL *ssl_server_negotiate(SERVER_INFO *server_info)
{
	/********* 新建SSL结构变量 */
	if ( (server_info->ssl = SSL_new(server_info->ssl_ctx)) == NULL)
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_server_negotiate:SSL_new]");
	    return NULL;
	}

	/********* 为SSL结构体设置socket连接句柄 */
#ifndef THIS_IS_SERVER
	if ( SSL_set_fd(server_info->ssl, server_info->serfd) != 1)
#else
    if ( SSL_set_fd(server_info->ssl, server_info->cltfd) != 1)
#endif
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_server_negotiate:SSL_set_fd]");
		goto cleanup;
	}

	/********* 接受SSL链接 */
	if ( SSL_accept(server_info->ssl) != 1)
	{
		GetLastSslErrorMessage(LOG_ERROR, "[ssl_server_negotiate:SSL_accept]");
		if ( SSL_shutdown(server_info->ssl) != 1)
			GetLastSslErrorMessage(LOG_ERROR, "[ssl_server_negotiate:SSL_shutdown]");
		goto cleanup;
	}

	return server_info->ssl;

cleanup:
    SSL_free(server_info->ssl);
    server_info->ssl = NULL;
    return NULL;
}

/**
  * @brief  服务器释放占用资源
  * @param  arg1:cpi  arg2: serfd
  * @retval NULL
  */
void server_release_resource(RA_INFO *ri, int cltfd)
{
    SSL_shutdown(ri->ssl);
    SSL_free(ri->ssl);
    ri->ssl = NULL;
    closesocket(cltfd);
}

/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/















