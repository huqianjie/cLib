/**
  ******************************************************************************
  * @file    stringx.c
  * @author  Dragon.Chen
  * @version V1.5.0
  * @date    04-27-2013
  * @brief   �ַ����߼����������ӿ�
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ </center></h2>
  ******************************************************************************
  */

#include "stdafx.h"
#include "stringx.h"

/**
  * @brief      �ж��ַ����Ƿ���ָ���ַ�����ʼ
  * @param      arg1��Դ�ַ�����arg2�����ַ���
  * @retval     1������ָ���ַ�����ʼ��0�����ǣ�-1�����ַ�����ԽԴ�ַ�������
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
  * @brief      �ж��ַ����Ƿ���ָ���ַ�������
  * @param      arg1��Դ�ַ�����arg2�����ַ���
  * @retval     1������ָ���ַ���������0�����ǣ�-1�����ַ�����ԽԴ�ַ�������
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
  * @brief      ��ȡָ���ַ��������ַ���
  * @param      arg1������ַ�����arg2��Դ�ַ�����arg3����ַ�
  * @retval     ����ַ���
  * @attention  src�������ַ�������
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
  * @brief      ��ȡָ���ַ���ĵ�һ���ַ���
  * @param      arg1������ַ�����arg2��Դ�ַ�����arg3����ַ�
  * @retval     ����ַ���
  * @attention  src�������ַ�������
  */
char *get_first_str_by_token(char *first_str, char *src, const char *token)
{
	if (first_str == NULL || src == NULL || token == NULL)
		return NULL;

    first_str = strtok(src, token);
    return first_str;
}

/**
  * @brief      ��ȡsrcǰlen�������ַ�������ָ���ַ����ֵĴ���
  * @param      arg1��Դ�ַ�����arg2���������ַ���arg3��ָ���ĳ���
  * @retval     ����ָ���ַ����ֵĴ���, ������-1
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
  * @brief      �����ж�Ŀ���ַ����Ƿ���Դ�ַ������ַ���(�״γ��ֵ�λ��)
  * @param      arg1��Դ�ַ�����arg2���������ַ�
  * @retval     �Ƿ���1�����򷵻�-1
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
  * @brief      Դ�ַ�������Ŀ���ַ����Ĵ���
  * @param      arg1��Դ�ַ�����arg2���������ַ�
  * @retval     �������ذ����Ĵ���(>0)�����򷵻�-1
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
  * @brief      ��ȡ���ַ���
  * @param      arg1��Ŀ���ַ����� arg2�� Ŀ���ַ�����С arg3��Դ�ַ�����arg4���ַ�����ʼλ�ã�arg5�ַ�������λ��
  * @retval     �ɹ��������ַ�����ʧ�ܷ���NULL
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
  * @brief      ��ȡ���ַ���
  * @param      arg1��Ŀ���ַ��� arg2�� Ŀ���ַ�����С  arg3��Դ�ַ�����arg4���ַ�����ʼλ��
  * @retval     �ɹ��������ַ�����ʧ�ܷ���NULL
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
  * @brief      ȥ���ַ�������β�ո�ͻس�
  * @param      arg1��Ŀ���ַ���  arg2�� Ŀ���ַ�����С  arg3��Դ�ַ���
  * @retval     �ɹ�����ȥ���ո���ַ���
  * @attention  ���������ɵ��ַ��������ṩ�Ļ�������Сʱ�����ػ�������С���ַ���
  */
char *trim(char *dst, int size, const char *src)
{
	int st = 0;
	int len;

	if (dst == NULL || src == NULL) 
		return NULL;
	len = strlen(src);
    while ((st < len) && (src[st] == ' '))  		//ȥ��ǰ�ո� while ((st < len) && (src[st] < ' '))
            st++;
    while ((st < len) && (src[len - 1] == ' '))		//ȥ����ո�
            len--;
    memset(dst, 0, size);
    strncpy(dst, src+st, (len-st) >= size ? (size-1) : (len-st));
    return dst;
}

/**
  * @brief      ȥ���ַ�������β�ո�ͻس�
  * @param      arg1���������ַ���
  * @retval     �ɹ�����ȥ���ո���ַ���
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



/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/

