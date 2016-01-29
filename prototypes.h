/**
  ******************************************************************************
  * @file    prototypes.h
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    12-02-2013
  * @brief
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#ifndef __PROTOTYPES__H__
#define __PROTOTYPES__H__

#include <ev.h>
#include <openssl/ssl.h>

#define DATA_PACK_MAXBUF        1020        // 数据包缓存区大小

/***************************服务器信息****************************
******* 配置文件结构体 */
typedef struct _config_file_info
{
    int   app_daemon;                       // 后台化
    int   thread_count;                     // 线程数
    int   server_port;                      // 端口号
    char *window_version;                   // window客户端最新版本
    char *window_f_version;                 // window客户端强制更新最低版本
    char *android_version;                  // android客户端最新版本
    char *android_f_version;                // android客户端强制更新最低版本
    char *pid_path;                         // 进程号路径
    char *rootcert;                         // 根证书路径
    char *servercert;                       // 服务器证书路径
    char *serverkey;                        // 服务器私鈅路径
    char *db_name;                          // 数据库路径
} CONFIG_FILE_INFO;

/****** 服务器信息 */
typedef struct _server_info
{
    int serfd;                              // 服务器监听套接字
    SSL_CTX *ssl_ctx;                       // ssl_ctx 上下文文本
    CONFIG_FILE_INFO *cfi;                  // 配置文件信息
} SERVER_INFO;

/***************************客户端信息****************************
******* 数据头部 */
typedef enum _pack_head
{
    IDX_EXPT    = 0,                        // 异常
    IDX_LGIN    = 1,                        // 用户登录
    IDX_EXIT    = 2,                        // 用户退出
    IDX_HTBG    = 3                         // 用户心跳包
} PACK_HEAD;


/****** 数据包 */
typedef struct _data_pack
{
	PACK_HEAD head;                         // 数据头部
	char buffer[DATA_PACK_MAXBUF];          // 数据缓存区(发送端数据长度不大于1016)
} DATA_PACK;


/****** 临时中转数据 */
typedef struct _relay_data
{
    PACK_HEAD   packhead;                     // 数据包头部
    void        *data;                        // 携带的数据
} RELAY_DATA;

/****** 复合数据 */
typedef union _compound_type
{
    int active;                             // 心跳包
} COMPOUND_TYPE;

/****** 用户信息 */
typedef struct  _client_info
{
    ev_io               *w;                 // ev_io事件
    COMPOUND_TYPE        ct;                // 复合数据
    SSL                 *ssl;               // ssl 上下文文本
    struct _client_info *next;              // 指向下一个变量指针
} CLIENT_INFO;


/****** 线程信息 */
typedef struct _thread_client_info
{
    pthread_t        ptid;                  // 线程号
    CLIENT_INFO     *head;                  // 用户信息链表头部
    struct ev_loop  *loop;                  // 消息循环者
    int              cmax;                  // 每个线程中的用户总数
} THREAD_CLIENT_INFO;


#endif

/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
















