/**
  ******************************************************************************
  * @file    stringx.h
  * @author  Dragon.Chen
  * @version V1.5.0
  * @date    04-27-2013
  * @brief   字符串高级操作函数接口
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#ifndef __STRINGX__H__
#define __STRINGX__H__

#ifdef USE_LINUX
#include <string.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief      判断字符串是否以指定字符串开始
  * @param      arg1、源字符串；arg2、子字符串
  * @retval     1、是以指定字符串开始；0、不是；-1、子字符串超越源字符串长度
  */
int start_with(const char *ptr_src, const char *start_str);

/**
  * @brief      判断字符串是否以指定字符串结束
  * @param      arg1、源字符串；arg2、子字符串
  * @retval     1、是以指定字符串结束；0、不是；-1、子字符串超越源字符串长度
  */
int end_with(const char *ptr_src, const char *end_str);

/**
  * @brief      截取指定字符后的最后字符串
  * @param      arg1、最后字符串；arg2、源字符串；arg3、拆分符
  * @retval     最后字符串
  * @attention  src必须是字符串数组
  */
char *get_last_str_by_token(char *last_str, char *src, const char *token);

/**
  * @brief      截取指定字符后的第一个字符串
  * @param      arg1、最后字符串；arg2、源字符串；arg3、拆分符
  * @retval     最后字符串
  * @attention  src必须是字符串数组
  */
char *get_first_str_by_token(char *first_str, char *src, const char *token);

/**
  * @brief      获取src前len个长度字符数组中指定字符出现的次数
  * @param      arg1、源字符串；arg2、待检测的字符；arg3、指定的长度
  * @retval     返回指定字符出现的次数
  */
int get_count_specified_char(const char *src, const char ch, int len);

/**
  * @brief      用于判断目标字符串是否是源字符串子字符串
  * @param      arg1、源字符串；arg2、待检测的字符
  * @retval     是返回1，否则返回-1
  */
int contains(const char *source, const char *target);

/**
  * @brief      源字符串包含目标字符串的次数
  * @param      arg1、源字符串；arg2、待检测的字符
  * @retval     正常返回包含的次数(>0)，否则返回-1
  */
int containc(const char *src, const char *dst);

/**
  * @brief      获取子字符串
  * @param      arg1、目标字符串； arg2、 目标字符串大小 arg3、源字符串；arg4、字符串开始位置；arg5字符串结束位置
  * @retval     成功返回子字符串，失败返回NULL
  */
char *substr(char *dst, int size, const char *src, int begin, int end);

/**
  * @brief      获取子字符串
  * @param      arg1、目标字符串  arg2、 目标字符串大小  arg3、源字符串  arg4、字符串开始位置
  * @retval     成功返回子字符串，失败返回NULL
  */
char *substr_by_start_position(char *dst, int size, const char *src, int begin);

/**
  * @brief      去除字符串的首尾空格和回车
  * @param      arg1、目标字符串  arg2、 目标字符串大小  arg3、源字符串
  * @retval     成功返回去除空格的字符串
  * @attention  如果处理完成的字符串大于提供的缓冲区大小时，返回缓冲区大小的字符串
  */
char *trim(char *dst, int size, const char *src);

/**
  * @brief      去除字符串的首尾空格和回车
  * @param      arg1、待处理字符串
  * @retval     成功返回去除空格的字符串
  */
void trim2(char *s);

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
