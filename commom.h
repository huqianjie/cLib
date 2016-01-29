/**
  ******************************************************************************
  * @file    commom.c
  * @author  Dragon.Chen
  * @version V1.5.0
  * @date    07-10-2013
  * @brief   对常用功能封装的函数库(因为这些函数无法划分到某个具体函数库的头文件中)
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */


#ifndef __COMMOM__H__
#define __COMMOM__H__

#include "includes.h"

#ifdef USE_WIN32
#include <windows.h>
#define GetLastErrorMsg			    Get_Last_Error_Message
#define GetLastSocketErrorMsg	    Get_Last_Socket_Error_Message
#elif defined USE_LINUX
#include <signal.h>
#include <unistd.h>
#define GetLastErrorMsg			    get_last_error_message
#define GetLastSocketErrorMsg	    get_last_error_message
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined USE_LINUX
void get_last_error_message(char *level, char *who);
#elif defined USE_WIN32
/**
  * @brief  获取API执行失败的原因
  * @param  arg1:错误等级, arg2:谁发生异常
  * @retval 返回错误信息
  */
void Get_Last_Error_Message(LPTSTR level, LPTSTR who);
void GetLastSocketErrorMessage(LPTSTR level, LPTSTR who);
#endif


/**
  * @brief  计算文件的大小
  * @param  arg1：文件名
  * @retval 文件大小
  */
long get_file_size(const char *file);


/**
  * @brief  获取当前时间
  * @param  arg1：存储时间字符数组, arg2：时间格式
  * @retval 成功返回当前时间，失败返回NULL
  */
char *get_system_date(char *time_buf, int flag);


/**
  * @brief  字符串转换成整型
  * @param  arg1：字符串
  * @retval 整型数
  × @attention 注意字符串必须是包含0～9的数字
  */
int string_to_integer(const char *src);


/**
  * @brief  整型转换成字符串
  * @param  arg1：目标字符串 arg2：整数 arg3：浮点数 arg4：转换标记
  * @retval 目标字符串
  × @attention arg4中的标记，当转换的是整数时，标记为0;当转换的是浮点数时，为非0,且flag也标记浮点数的有效位数
  */
char *integer_to_string(char *dst, int value1, float value2, int flag);


/**
  * @brief   版本号补齐
  * @param   arg1:补齐版本 arg2:原版本
  * @retval  返回补齐版本
  */
char *auto_complete_version(char *dst, const char *src);

/**
  * @brief     获取context的md5
  * @param     arg1 文件路径  arg2 flag为0获取32位md5值,否则为16位md5值
  * @retval    成功返回md5值,否则为NULL
  * @attention 此函数动态返回md5值,顾最终要调用free释放内存
  */
char *md5sum(const char *path, int flag);


#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
































