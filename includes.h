/**
  ******************************************************************************
  * @file    includes.h
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    02-10-2014
  * @brief   此头文件包含常用的头文件及一些常用功能的宏定义
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#ifndef __INCLUDES__H__
#define __INCLUDES__H__

#include "log-util.h"
#include "prototypes.h"

#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

/* 功能状态类型 */
typedef enum
{
    DISABLE = 0,
    ENABLE = !DISABLE
} FunctionalStatus;

/* 错误状态类型 */
typedef enum
{
    ERROR = 0,
    SUCCESS = !ERROR
} ErrorStatus;


/* 将表达式转换成bool值 */
#define BOOL_CAST(x) ((x) ? (true) : (false))

/* 测试数组的大小 */
#define SIZE(x) (sizeof(x)/sizeof(x[0]))

/* 清除一个对象 */
#define CLEAR(x) memset(&(x), 0, sizeof(x))

/* 比较两个字符串是否相等 */
#define streql	    !strcmp
#define strieql     !strcasecmp
#define strneql     !strncmp
#define strnieql    !strncasecmp

/************************** software self macro */
#define VPN_MAX_NUM_OF_THREAD   1                               // 最大线程数
#define SOCK_RECV_MAXBUF        1024                            // socket接收缓存区大小
#define MAX_USER_PER_THREAD     5000                            // 每个线程接收最大用户
#define VPN_SERVER_VERSION		"V1.0000"                       // 服务器版本号
#define THIS_IS_SERVER                                          // 服务器
#define CLog(...)               fprintf(stdout, __VA_ARGS__)    // 系统信息打印

/************************** config file infomation macro */
#define VPN_BASEPATH            "/sonicom/conf/openvpn/conf/"   // 基路径
#define VPN_CNF_PTPT		    VPN_BASEPATH		            // 配置文件父路径
#define VPN_CNF_PATH		    VPN_BASEPATH"vpnserver.conf"    // 配置文件路径
#define VPN_PID_PATH            cfi.pid_path	                // 进程号路径
#define VPN_ROOT_CERT_PATH      cfi.rootcert_path               // 根证书路径
#define VPN_APP_DAEMON          cfi.app_daemon                  // 后台化
#define VPN_NUM_OF_THREAD       cfi.thread_count                // 线程数
#define VPN_SERVER_PORT         cfi.server_port                 // 端口号
#define VPN_DATABASE_NAME       cfi.db_name                     // 数据库名称
#define VPN_WINDOW_VERSION      cfi.window_version              // window客户端最新版本
#define VPN_WINDOW_F_VERSION    cfi.window_f_version            // window客户端强制更新最低版本
#define VPN_ANDROID_VERSION     cfi.android_version             // android客户端最新版本
#define VPN_ANDROID_F_VERSION   cfi.android_f_version           // android客户端强制更新最低版本

#endif

/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
