/**
  ******************************************************************************
  * @file    log-util.c
  * @author  Dragon.Chen
  * @version V2.0.0
  * @date    05-20-2013
  * @brief   调试和记录日志
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
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

static FILE* fp = NULL;								// 日志文件指针
static BOOL  Critical_Flag = TRUE;					// 临界区标记(TRUE为关闭)
static long  get_file_size(const char *path);		// 获取文件大小


/**
  * @brief  断言失败
  * @param  arg1:文件路径  arg2:行号
  * @retval none
  */
void assert_fail(char *expr, char *file, int line)
{
	MSG(LOG_FATAL, "%s%s %s%s%d", "Assertion failed: ", expr, file, ", line ", line);
}


/**
  * @brief  打开日志
  * @param  日志路径
  * @retval 成功为TRUE，否则FALSE
  */
BOOL open_log(const char *path)
{
	/************* 打开日志 */
	if ((fp=fopen(path, "at")) == NULL)
		return FALSE;

	/************* 初始化临界区 */
	Initialize_Critical_Section(&log_mutex
#ifdef USE_LINUX
		, NULL);
#else
		);
#endif
	/************* 设置临界区打开标志 */
	Critical_Flag = FALSE;

	return TRUE;
}


/**
  * @brief		记录日志
  * @param		arg1:日志文件路径  arg2：日志状态  arg3：待记录的数据
  * @retval		none
  * @attention	本函数非线程安全
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

	/************* 如果临界区标志未打开则打开日志初始化临界区 */
	if (Critical_Flag)
		open_log(path);

	/************* 进入临界区 */
	Enter_Critical_Section(&log_mutex);

	/************* 获取系统时间 */
    lt = time(NULL);
    date_time = localtime(&lt);
    strftime(fmt_time_buf, 30, "%x %X\n", date_time);

	/************* 将时间写入buffer */
	strcpy(time_buffer, "20");
    strncat(time_buffer, fmt_time_buf+6, 2);
    strcat(time_buffer, "/");
    strncat(time_buffer, fmt_time_buf, 2);
    strcat(time_buffer, "/");
    strncat(time_buffer, fmt_time_buf+3, 2);
    strcat(time_buffer, " ");
    strncat(time_buffer, fmt_time_buf+9, 8);

	/************* 将日志信息写入buffer */
    strcat(time_buffer, "  ");
	strcat(time_buffer, type);
    strcat(time_buffer, "  ");
    strncat(time_buffer, msg, MESSAGE_LENGTH);
	strcat(time_buffer, "\n");
    fputs(time_buffer, fp);
	fflush(fp);

	/************* 离开临界区 */
	Leave_Critical_Section(&log_mutex);
#ifndef ENABLE_DEBUG
finish:;
#endif

}


/**
  * @brief  关闭日志
  * @param  NULL
  * @retval void
  */
void close_log()
{
    if (!Critical_Flag)
    {
        fclose(fp);
        fp = NULL;
        /************* 删除临界区 */
        Delete_Critical_Section(&log_mutex);
        /************* 关闭临界区打开标志 */
        Critical_Flag = TRUE;
	}
}


/**
  * @brief  记录紧急异常日志
  * @param  arg1:日志文件路径  arg2：日志状态  arg3：待记录的数据
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

    /************* 获取系统时间 */
    lt = time(NULL);
    date_time = localtime(&lt);
    strftime(fmt_time_buf, 30, "%x %X\n", date_time);

	/************* 将时间写入buffer */
	strcpy(time_buffer, "20");
    strncat(time_buffer, fmt_time_buf+6, 2);
    strcat(time_buffer, "/");
    strncat(time_buffer, fmt_time_buf, 2);
    strcat(time_buffer, "/");
    strncat(time_buffer, fmt_time_buf+3, 2);
    strcat(time_buffer, " ");
    strncat(time_buffer, fmt_time_buf+9, 8);

	/************* 将日志信息写入buffer */
    strcat(time_buffer, "  ");
	strcat(time_buffer, type);
    strcat(time_buffer, "  ");
    strncat(time_buffer, msg, MESSAGE_LENGTH);
	strcat(time_buffer, "\n");
    fputs(time_buffer, fp2);

	fclose(fp2);
}

/**
  * @brief  移除日志
  * @param  arg1:日志文件路径
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
  * @brief  尝试移除大于10M的日志
  * @param  arg1:日志文件路径
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
  * @brief  计算文件的大小
  * @param  arg1：文件名
  * @retval 文件大小
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


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/


