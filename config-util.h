/**
******************************************************************************
* @file    config-util.c
* @author  Dragon.Chen
* @version V1.0.0
* @date    05-20-2014
* @brief   ��ȡ�����ļ���Ϣ����֧�ֶ��߳�ͬʱ����
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2014 �Ϻ���������Ƽ����޹�˾ </center></h2>
******************************************************************************
*/

#ifndef __CONFIG_UTIL__H__
#define __CONFIG_UTIL__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN
#define OUT

/**
  * @brief      ��ȡ�ļ��ֶ�
  * @param      arg1���ļ���
  * @retval     �ɹ�����0��ʧ��-1
  */
int readContent(IN const char *fileName);

/**
  * @brief      ��ȡ��������
  * @param      arg1��field
  * @retval     �ɹ���Ӧ��ֵ��ʧ��defaultvalue
  */
int getInt(IN const char *field, IN int defaultvalue);

/**
  * @brief      ��ȡ�ַ���
  * @param      arg1��field
  * @retval     �ɹ���Ӧ��ֵ��ʧ��defaultValue
  */
char *getString(IN const char *field, IN char *defaultValue);

/**
  * @brief      ������������
  * @param      arg1��field arg2��newValue
  * @retval     NULL
  */
void setInt(IN const char *field, IN int newValue);

/**
  * @brief      �����ַ�������
  * @param      arg1��field arg2��newValue
  * @retval     NULL
  */
void setString(IN const char *field, const char *newValue);

/**
  * @brief      �������ݵ��ļ�(�޸��ļ�����ʱ�����)
  * @param      arg1��pathName
  * @retval     NULL
  */
void commit(const char *pathName);

/**
  * @brief      �ͷ�ռ�õ��ڴ�(�������)
  * @param      arg1��pathName
  * @retval     NULL
  */
void freeContent();


#endif // __CONFIG__H__

/******************* (C) COPYRIGHT 2014 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/
