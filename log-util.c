/**
  ******************************************************************************
  * @file    log-util.c
  * @author  Dragon.Chen
  * @version V2.0.0
  * @date    05-20-2013
  * @brief   ���Ժͼ�¼��־
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ </center></h2>
  ******************************************************************************
  */

#include "log-util.h"

#ifdef  USE_WIN32
#define MUTEX  CRITICAL_SECTION
static  MUTEX  log_mutex;
#define Initialize_Critical_Section		InitializeCriticalSection
#define Enter_Critical_Section			EnterCriticalSection
#define Leave_Critical_Section			LeaveCriticalSection
#define Delete_Critical_Section			DeleteCriticalSection
#elif defined (USE_LINUX)
#define MUTEX  pthread_mutex_t
static  MUTEX  log_mutex;
#define Initialize_Critical_Section		pthread_mutex_init
#define Enter_Critical_Section			pthread_mutex_lock
#define Leave_Critical_Section			pthread_mutex_unlock
#define Delete_Critical_Section			pthread_mutex_destroy
#endif

static FILE* fp = NULL;								// ��־�ļ�ָ��
static BOOL  Critical_Flag = TRUE;					// �ٽ������(TRUEΪ�ر�)
static long  get_file_size(const char *path);		// ��ȡ�ļ���С


/**
  * @brief  ����ʧ��
  * @param  arg1:�ļ�·��  arg2:�к�
  * @retval none
  */
void assert_fail(char *expr, char *file, int line)
{
	MSG(LOG_FATAL, "%s%s %s%s%d", "Assertion failed: ", expr, file, ", line ", line);
}


/**
  * @brief  ����־
  * @param  ��־·��
  * @retval �ɹ�ΪTRUE������FALSE
  */
BOOL open_log(const char *path)
{
	/************* ����־ */
	if ((fp=fopen(path, "at")) == NULL)
		return FALSE;

	/************* ��ʼ���ٽ��� */
	Initialize_Critical_Section(&log_mutex
#ifdef USE_LINUX
		, NULL);
#else
		);
#endif
	/************* �����ٽ����򿪱�־ */
	Critical_Flag = FALSE;

	return TRUE;
}


/**
  * @brief		��¼��־
  * @param		arg1:��־�ļ�·��  arg2����־״̬  arg3������¼������
  * @retval		none
  * @attention	���������̰߳�ȫ
  */
void write_log(const char *path, const char *type, const char *msg)
{
#ifndef ENABLE_DEBUG
    if (!strcmp(type, LOG_DEBUG))
        goto finish;
#endif
	time_t lt;
    struct tm *date_time;
    char fmt_time_buf[30] = {0};
	char time_buffer[TIME_BUF_LENGTH] = {0};

	/************* ����ٽ�����־δ�������־��ʼ���ٽ��� */
	if (Critical_Flag)
		open_log(path);

	/************* �����ٽ��� */
	Enter_Critical_Section(&log_mutex);

	/************* ��ȡϵͳʱ�� */
    lt = time(NULL);
    date_time = localtime(&lt);
    strftime(fmt_time_buf, 30, "%x %X\n", date_time);

	/************* ��ʱ��д��buffer */
	strcpy(time_buffer, "20");
    strncat(time_buffer, fmt_time_buf+6, 2);
    strcat(time_buffer, "/");
    strncat(time_buffer, fmt_time_buf, 2);
    strcat(time_buffer, "/");
    strncat(time_buffer, fmt_time_buf+3, 2);
    strcat(time_buffer, " ");
    strncat(time_buffer, fmt_time_buf+9, 8);

	/************* ����־��Ϣд��buffer */
    strcat(time_buffer, "  ");
	strcat(time_buffer, type);
    strcat(time_buffer, "  ");
    strncat(time_buffer, msg, MESSAGE_LENGTH);
	strcat(time_buffer, "\n");
    fputs(time_buffer, fp);
	fflush(fp);

	/************* �뿪�ٽ��� */
	Leave_Critical_Section(&log_mutex);
#ifndef ENABLE_DEBUG
finish:;
#endif

}


/**
  * @brief  �ر���־
  * @param  NULL
  * @retval void
  */
void close_log()
{
    if (!Critical_Flag)
    {
        fclose(fp);
        fp = NULL;
        /************* ɾ���ٽ��� */
        Delete_Critical_Section(&log_mutex);
        /************* �ر��ٽ����򿪱�־ */
        Critical_Flag = TRUE;
	}
}


/**
  * @brief  ��¼�����쳣��־
  * @param  arg1:��־�ļ�·��  arg2����־״̬  arg3������¼������
  * @retval none
  */
void write_emg_log(const char *path, const char *type, const char *msg)
{
    time_t lt;
    struct tm *date_time;
    char fmt_time_buf[30] = {0};
	char time_buffer[TIME_BUF_LENGTH] = {0};
    FILE *fp2 = NULL;

    if ( (fp2=fopen(path, "at")) == NULL)
		return ;

    /************* ��ȡϵͳʱ�� */
    lt = time(NULL);
    date_time = localtime(&lt);
    strftime(fmt_time_buf, 30, "%x %X\n", date_time);

	/************* ��ʱ��д��buffer */
	strcpy(time_buffer, "20");
    strncat(time_buffer, fmt_time_buf+6, 2);
    strcat(time_buffer, "/");
    strncat(time_buffer, fmt_time_buf, 2);
    strcat(time_buffer, "/");
    strncat(time_buffer, fmt_time_buf+3, 2);
    strcat(time_buffer, " ");
    strncat(time_buffer, fmt_time_buf+9, 8);

	/************* ����־��Ϣд��buffer */
    strcat(time_buffer, "  ");
	strcat(time_buffer, type);
    strcat(time_buffer, "  ");
    strncat(time_buffer, msg, MESSAGE_LENGTH);
	strcat(time_buffer, "\n");
    fputs(time_buffer, fp2);

	fclose(fp2);
}

/**
  * @brief  �Ƴ���־
  * @param  arg1:��־�ļ�·��
  * @retval none
  */
void remove_log(const char *path)
{
#ifdef USE_WIN32_SAFE
	if (_access(path, 0) != 0)
		return;
#else
	if (access(path, 0) != 0)
		return;
#endif
	remove(path);
}


/**
  * @brief  �����Ƴ�����10M����־
  * @param  arg1:��־�ļ�·��
  * @retval none
  */
void try_remove_log(const char *path)
{
#ifdef USE_WIN32_SAFE
	if (_access(path, 0) != 0)
		return;
#else
	if (access(path, 0) != 0)
		return;
#endif
	if (10000000 == get_file_size(path) )
		remove(path);
}


/**
  * @brief  �����ļ��Ĵ�С
  * @param  arg1���ļ���
  * @retval �ļ���С
  */
static long get_file_size(const char *path)
{
    FILE *fp;
    long file_size;

    if((fp=fopen(path, "rt")) == NULL)
        return -1;

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fclose(fp);

	return file_size;
}


/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/


