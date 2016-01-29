/**
  ******************************************************************************
  * @file    logs-util.c
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    01-14-2013
  * @brief   记录日志
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#include "logs-util.h"

FILE *log_fp = NULL;

/**
  * @brief  根据指定模式打开日志文件
  * @param  无
  * @retval 0:  操作成功   -1: 打开失败
  */
int log_open()
{
    if ( (log_fp = fopen(_LOG_NAME, ACCESS_MODE)) == NULL)
        if ( (log_fp = fopen(_LOG_NAME, ACCESS_MODE)) == NULL)
            return -1;
    fputs("DATE \t\t\t\t LEVEL \t  INFORMATION\n", log_fp);
    fflush(log_fp);
    return 0;
}


/**
  * @brief  写入日志文件
  * @param  arg1 操作什么函数出错
            arg2 等级
            arg3错误信息
  * @retval 无
  */
void log_write(int level, char *msg)
{
	time_t lt;
    struct tm *date_time;
    char fmt_time_buf[30] = {0};
	char buffer[TIME_BUF_LENGTH] = {0};

	/************* 获取系统时间 */
    lt = time(NULL);
    date_time = localtime(&lt);
    strftime(fmt_time_buf, 30, "%x %X\n", date_time);

	/************* 将时间写入buffer */
	strcpy(buffer, "20");
    strncat(buffer, fmt_time_buf+6, 2);
    strcat(buffer, "-");
    strncat(buffer, fmt_time_buf, 2);
    strcat(buffer, "-");
    strncat(buffer, fmt_time_buf+3, 2);
    strcat(buffer, " ");
    strncat(buffer, fmt_time_buf+9, 8);

	/************* 将日志信息写入buffer */
    strcat(buffer, "  ");
    if (LOG_FATAL & level)
        strcat(buffer, "FATAL  ");
    else if (LOG_ERROR & level)
        strcat(buffer, "ERROR  ");
    else if (LOG_WARNING & level)
        strcat(buffer, "WARNING");
    else if (LOG_DEBUG & level)
        strcat(buffer, "DEBUG  ");
    else if (LOG_INFO & level)
        strcat(buffer, "INFO   ");
    strcat(buffer, "  ");
    strncat(buffer, msg, MESSAGE_LENGTH);
	strcat(buffer, "\n");

	if (log_fp == NULL)
        if (log_open() < 0)
            return;

    fputs(buffer, log_fp);
	fflush(log_fp);

	if (level & LOG_FATAL)
        exit(EXIT_FAILURE);
}

/**
  * @brief  关闭日志文件
  * @param  无
  * @retval 无
  */
void log_close()
{
    fclose(log_fp);
}


/**
  * @brief  获取API执行失败的原因
  * @param  arg1:错误等级, arg2:谁发生异常
  * @retval 返回错误信息
  */
void get_last_error_msg(int level, char *who)
{
	char *str = NULL;
    char *msg = NULL;

    msg = strdup(strerror(errno));
    if ( (str = (char*)malloc((size_t)(strlen(msg) + (who == NULL ? 0 : strlen(who)) + 20))) == NULL)
        return;
    sprintf(str, "%s %s", (who == NULL ? "" : who), msg);
	MSG(level, "%s", str);
	free(msg);
	free(str);
}

/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/










