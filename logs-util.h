/**
  ******************************************************************************
  * @file    logs-util.h
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    01-14-2013
  * @brief   记录日志
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#ifndef __LOGS_UTIL__H__
#define __LOGS_UTIL__H__

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "platform.h"

// 日志等级
#define LOG_FATAL           (1<<0)
#define LOG_ERROR           (1<<1)
#define LOG_WARNING         (1<<2)
#define LOG_DEBUG           (1<<3)
#define LOG_INFO            (1<<4)

// 访问模式
#define ACCESS_MODE         "wt"
// 日志文件名称
#define _LOG_NAME           "/var/log/raserver.log"
// 时间邮戳长度
#define TIME_BUF_LENGTH     300
// 信息长度
#define MESSAGE_LENGTH      250

/* 设置控制台调试输出 */
#ifdef ENABLE_DEBUG
#define CLog(...)	fprintf(stdout, __VA_ARGS__)
#else
#define CLog(...)	(void)0
#endif

/** 记录日志和打印调试信息 flag禁止为NULL */
#define MSG(flag, ...) \
	do {\
		char log_buf[MESSAGE_LENGTH] = {0}; \
		snprintf(log_buf, MESSAGE_LENGTH-1, __VA_ARGS__);\
		log_write(flag, log_buf);\
		CLog("console >> %s\n", log_buf);\
	} while (0)


#define GetLastErrorMsg     get_last_error_msg


/**
  * @brief  根据指定模式打开日志文件
  * @param  无
  * @retval 0:  操作成功   -1: 打开失败
  */
int log_open();


/**
  * @brief  写入日志文件
  * @param  arg1 操作什么函数出错
            arg2 等级
            arg3错误信息
  * @retval 无
  */
void log_write(int level, char *msg);


/**
  * @brief  关闭日志文件
  * @param  无
  * @retval 无
  */
void log_close();


/**
  * @brief  获取API执行失败的原因
  * @param  arg1:错误等级, arg2:谁发生异常
  * @retval 返回错误信息
  */
#if defined USE_LINUX
void get_last_error_msg(int level, char *who);
#endif

#endif

/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/





