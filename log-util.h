/**
  ******************************************************************************
  * @file    log-util.c
  * @author  Dragon.Chen
  * @version V2.0.0
  * @date    05-20-2013
  * @modify  11-09-2013
  * @brief   调试和记录日志
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#ifndef __LOG_UTIL__H__
#define __LOG_UTIL__H__

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#include "platform.h"

#ifdef USE_WIN32
#include <io.h>
#define SNPRINTF	_snprintf
#elif defined(USE_LINUX)
#include <pthread.h>
#define SNPRINTF	snprintf
#endif

#define MESSAGE_LENGTH	    250
#define TIME_BUF_LENGTH		300

/************* 定义实际需要的日志路径名称 */
#ifdef ROOT_PRIORITY_LEVEL
#define LOG_PATH            "/var/log/vpnserver.log"
#else
#define LOG_PATH            "vpnserver.log"
#endif

/*************************** 日志等级 */
#define LOG_FATAL			"FATAL   "		// 致命错误
#define LOG_ERROR			"ERROR   "		// 错误信息
#define LOG_WARNING			"WARNING "		// 警告信息
#define LOG_INFO			"INFO    "		// 正常输出信息
#define LOG_DEBUG			"DEBUG   "		// 调试信息

#ifdef __cplusplus
extern "C" {
#endif

/*************************** 打印出调试信息 */
#ifdef ENABLE_DEBUG
#ifdef WIN32_DLG
	#define LOG(...) \
	do { \
		TCHAR log_buf[MESSAGE_LENGTH] = {0}; \
		SNPRINTF(log_buf, MESSAGE_LENGTH-1, __VA_ARGS__);\
		AfxMessageBox(log_buf);	\
	} while (0)
#else
#define LOG(...)	fprintf(stdout, __VA_ARGS__)
#endif // WIN32_DLG
#else
#define LOG(...)	(void)0
#endif // ENABLE_DEBUG

/** 记录日志和打印调试信息 flag禁止为NULL */
#define MSG(flag, ...)	\
	do { \
		char log_buf[MESSAGE_LENGTH] = {0};	\
		SNPRINTF(log_buf, MESSAGE_LENGTH-1, __VA_ARGS__);\
		write_log(LOG_PATH, (flag), log_buf);\
		LOG("%s: %s\n" , (flag), log_buf);\
		if (!strcmp((flag), LOG_FATAL)) \
			exit(EXIT_FAILURE);	\
	} while (0)

/** 记录紧急异常日志 */
#define EMG_MSG     write_emg_log

/*************************** 当参数不合法时，记录致命日志并关闭应用程序 */
#define assert_param(expr)  ( (expr) ? (void)0 : assert_fail(#expr, __FILE__, __LINE__) )
void assert_fail(char *expr, char *file, int line);

/**
  * @brief  打开日志
  * @param  日志路径
  * @retval 成功为TRUE，否则FALSE
  */
BOOL open_log(const char *path);

/**
  * @brief		记录日志
  * @param		arg1:日志文件路径  arg2：日志状态  arg3：待记录的数据
  * @retval		none
  * @attention	本函数非线程安全
  */
void write_log(const char *path, const char *type, const char *msg);

/**
  * @brief  记录紧急异常日志
  * @param  arg1:日志文件路径  arg2：日志状态  arg3：待记录的数据
  * @retval none
  */
void write_emg_log(const char *path, const char *type, const char *msg);

/**
  * @brief  关闭日志
  * @param  NULL
  * @retval void
  */
void close_log();

/**
  * @brief  移除日志
  * @param  arg1:日志文件路径
  * @retval none
  */
void remove_log(const char *path);


/**
  * @brief  尝试移除大于10M的日志
  * @param  arg1:日志文件路径
  * @retval none
  */
void try_remove_log(const char *path);

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
