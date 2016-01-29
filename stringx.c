/**
  ******************************************************************************
  * @file    stringx.c
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

#include "stdafx.h"
#include "stringx.h"

/**
  * @brief      判断字符串是否以指定字符串开始
  * @param      arg1、源字符串；arg2、子字符串
  * @retval     1、是以指定字符串开始；0、不是；-1、子字符串超越源字符串长度
  */
int start_with(const char *ptr_src, const char *start_str)
{
    size_t len;

	if (ptr_src == NULL || start_str == NULL)
		return 0;
    len = strlen(start_str);
    if(strlen(ptr_src) < len)
		return -1;
    if (!strncmp(ptr_src, start_str, len))
		return 1;
    return 0;
}


/**
  * @brief      判断字符串是否以指定字符串结束
  * @param      arg1、源字符串；arg2、子字符串
  * @retval     1、是以指定字符串结束；0、不是；-1、子字符串超越源字符串长度
  */
int end_with(const char *ptr_src, const char *end_str)
{
    int len1, len2;

	if (ptr_src == NULL || end_str == NULL)
		return 0;
    len1 = strlen(ptr_src);
    len2 = strlen(end_str);
    if (len1 < len2)
		return -1;
    if (!strncmp(ptr_src+len1-len2, end_str, len2))
		return 1;
    return 0;
}


/**
  * @brief      截取指定字符后的最后字符串
  * @param      arg1、最后字符串；arg2、源字符串；arg3、拆分符
  * @retval     最后字符串
  * @attention  src必须是字符串数组
  */
char *get_last_str_by_token(char *last_str, char *src, const char *token)
{
    char *temp = NULL;

	if (last_str == NULL || src == NULL || token == NULL)
		return NULL;
    temp = strtok(src, token);
    while(temp != NULL)
    {
        strcpy(last_str, temp);
        temp = strtok(NULL, token);
    }
    return last_str;
}

/**
  * @brief      截取指定字符后的第一个字符串
  * @param      arg1、最后字符串；arg2、源字符串；arg3、拆分符
  * @retval     最后字符串
  * @attention  src必须是字符串数组
  */
char *get_first_str_by_token(char *first_str, char *src, const char *token)
{
	if (first_str == NULL || src == NULL || token == NULL)
		return NULL;

    first_str = strtok(src, token);
    return first_str;
}

/**
  * @brief      获取src前len个长度字符数组中指定字符出现的次数
  * @param      arg1、源字符串；arg2、待检测的字符；arg3、指定的长度
  * @retval     返回指定字符出现的次数, 出错返回-1
  */
int get_count_specified_char(const char *src, const char ch, int len)
{
    int i, cnt=0;

	if (src == NULL)
		return -1;
    if (len > (int)strlen(src))
		return -1;
    for (i=0; i<len; i++)
    {
        if(src[i] == ch)
            cnt++;
    }
    return cnt;
}


/**
  * @brief      用于判断目标字符串是否是源字符串子字符串(首次出现的位置)
  * @param      arg1、源字符串；arg2、待检测的字符
  * @retval     是返回1，否则返回-1
  */
int contains(const char *source, const char *target)
{
	if (source == NULL || target == NULL)
		return -1;
	if (strstr(source, target) != NULL)
		return 1;
    return -1;
}


/**
  * @brief      源字符串包含目标字符串的次数
  * @param      arg1、源字符串；arg2、待检测的字符
  * @retval     正常返回包含的次数(>0)，否则返回-1
  */
int containc(const char *src, const char *dst)
{
    int cnt = 0;
    char *last = (char*)src;

    if (src == NULL || dst == NULL)  return -1;
    while ( (last = strstr(last, dst)) != NULL)
    {
        last += 1;
        cnt++;
    }

    return cnt;
}


/**
  * @brief      获取子字符串
  * @param      arg1、目标字符串； arg2、 目标字符串大小 arg3、源字符串；arg4、字符串开始位置；arg5字符串结束位置
  * @retval     成功返回子字符串，失败返回NULL
  */
char *substr(char *dst, int size, const char *src, int begin, int end)
{
	int len;

	if (dst == NULL || src == NULL) 
		return NULL;
    len = strlen(src);
	if (begin < 0)  
		begin = 0;
	if ((end - begin) < 0)  
		return NULL;
    if (len < end)  
		return NULL;
    memset(dst, 0, size);
    strncpy(dst, src+begin-1, (end-begin+1) >= size ? (size-1) : (end-begin+1));
    return dst;
}


/**
  * @brief      获取子字符串
  * @param      arg1、目标字符串 arg2、 目标字符串大小  arg3、源字符串；arg4、字符串开始位置
  * @retval     成功返回子字符串，失败返回NULL
  */
char *substr_by_start_position(char *dst, int size, const char *src, int begin)
{
	int len;

	if (dst == NULL || src == NULL) 
		return NULL;
    len = strlen(src);
	if (begin < 0)  
		begin = 0;
    if (len < begin)  
		return NULL;
    memset(dst, 0, size);
    strncpy(dst, src+begin-1, (len-begin+1) >= size ? (size-1) : (len-begin+1));
    return dst;
}


/**
  * @brief      去除字符串的首尾空格和回车
  * @param      arg1、目标字符串  arg2、 目标字符串大小  arg3、源字符串
  * @retval     成功返回去除空格的字符串
  * @attention  如果处理完成的字符串大于提供的缓冲区大小时，返回缓冲区大小的字符串
  */
char *trim(char *dst, int size, const char *src)
{
	int st = 0;
	int len;

	if (dst == NULL || src == NULL) 
		return NULL;
	len = strlen(src);
    while ((st < len) && (src[st] == ' '))  		//去除前空格 while ((st < len) && (src[st] < ' '))
            st++;
    while ((st < len) && (src[len - 1] == ' '))		//去除后空格
            len--;
    memset(dst, 0, size);
    strncpy(dst, src+st, (len-st) >= size ? (size-1) : (len-st));
    return dst;
}

/**
  * @brief      去除字符串的首尾空格和回车
  * @param      arg1、待处理字符串
  * @retval     成功返回去除空格的字符串
  */
void trim2(char *s) 
{
    char *p = s;
    int len = strlen(p);

    while(isspace(p[len - 1])) 
		p[--len] = 0;
    while(*p && isspace(*p)) 
		++p, --len;

    memmove(s, p, len + 1);
}



/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/

