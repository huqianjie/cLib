/**
  ******************************************************************************
  * @file    log-util.c
  * @author  Dragon.Chen
  * @version V2.0.0
  * @date    05-20-2013
  * @modify  11-09-2013
  * @brief   ���Ժͼ�¼��־
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ </center></h2>
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

/************* ����ʵ����Ҫ����־·������ */
#ifdef ROOT_PRIORITY_LEVEL
#define LOG_PATH            "/var/log/vpnserver.log"
#else
#define LOG_PATH            "vpnserver.log"
#endif

/*************************** ��־�ȼ� */
#define LOG_FATAL			"FATAL   "		// ��������
#define LOG_ERROR			"ERROR   "		// ������Ϣ
#define LOG_WARNING			"WARNING "		// ������Ϣ
#define LOG_INFO			"INFO    "		// ���������Ϣ
#define LOG_DEBUG			"DEBUG   "		// ������Ϣ

#ifdef __cplusplus
extern "C" {
#endif

/*************************** ��ӡ��������Ϣ */
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

/** ��¼��־�ʹ�ӡ������Ϣ flag��ֹΪNULL */
#define MSG(flag, ...)	\
	do { \
		char log_buf[MESSAGE_LENGTH] = {0};	\
		SNPRINTF(log_buf, MESSAGE_LENGTH-1, __VA_ARGS__);\
		write_log(LOG_PATH, (flag), log_buf);\
		LOG("%s: %s\n" , (flag), log_buf);\
		if (!strcmp((flag), LOG_FATAL)) \
			exit(EXIT_FAILURE);	\
	} while (0)

/** ��¼�����쳣��־ */
#define EMG_MSG     write_emg_log

/*************************** ���������Ϸ�ʱ����¼������־���ر�Ӧ�ó��� */
#define assert_param(expr)  ( (expr) ? (void)0 : assert_fail(#expr, __FILE__, __LINE__) )
void assert_fail(char *expr, char *file, int line);

/**
  * @brief  ����־
  * @param  ��־·��
  * @retval �ɹ�ΪTRUE������FALSE
  */
BOOL open_log(const char *path);

/**
  * @brief		��¼��־
  * @param		arg1:��־�ļ�·��  arg2����־״̬  arg3������¼������
  * @retval		none
  * @attention	���������̰߳�ȫ
  */
void write_log(const char *path, const char *type, const char *msg);

/**
  * @brief  ��¼�����쳣��־
  * @param  arg1:��־�ļ�·��  arg2����־״̬  arg3������¼������
  * @retval none
  */
void write_emg_log(const char *path, const char *type, const char *msg);

/**
  * @brief  �ر���־
  * @param  NULL
  * @retval void
  */
void close_log();

/**
  * @brief  �Ƴ���־
  * @param  arg1:��־�ļ�·��
  * @retval none
  */
void remove_log(const char *path);


/**
  * @brief  �����Ƴ�����10M����־
  * @param  arg1:��־�ļ�·��
  * @retval none
  */
void try_remove_log(const char *path);

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/
