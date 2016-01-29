/**
  ******************************************************************************
  * @file    commom.c
  * @author  Dragon.Chen
  * @version V1.5.0
  * @date    07-10-2013
  * @brief   �Գ��ù��ܷ�װ�ĺ�����(��Ϊ��Щ�����޷����ֵ�ĳ�����庯�����ͷ�ļ���)
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ </center></h2>
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
  * @brief  ��ȡAPIִ��ʧ�ܵ�ԭ��
  * @param  arg1:����ȼ�, arg2:˭�����쳣
  * @retval ���ش�����Ϣ
  */
void Get_Last_Error_Message(LPTSTR level, LPTSTR who);
void GetLastSocketErrorMessage(LPTSTR level, LPTSTR who);
#endif


/**
  * @brief  �����ļ��Ĵ�С
  * @param  arg1���ļ���
  * @retval �ļ���С
  */
long get_file_size(const char *file);


/**
  * @brief  ��ȡ��ǰʱ��
  * @param  arg1���洢ʱ���ַ�����, arg2��ʱ���ʽ
  * @retval �ɹ����ص�ǰʱ�䣬ʧ�ܷ���NULL
  */
char *get_system_date(char *time_buf, int flag);


/**
  * @brief  �ַ���ת��������
  * @param  arg1���ַ���
  * @retval ������
  �� @attention ע���ַ��������ǰ���0��9������
  */
int string_to_integer(const char *src);


/**
  * @brief  ����ת�����ַ���
  * @param  arg1��Ŀ���ַ��� arg2������ arg3�������� arg4��ת�����
  * @retval Ŀ���ַ���
  �� @attention arg4�еı�ǣ���ת����������ʱ�����Ϊ0;��ת�����Ǹ�����ʱ��Ϊ��0,��flagҲ��Ǹ���������Чλ��
  */
char *integer_to_string(char *dst, int value1, float value2, int flag);


/**
  * @brief   �汾�Ų���
  * @param   arg1:����汾 arg2:ԭ�汾
  * @retval  ���ز���汾
  */
char *auto_complete_version(char *dst, const char *src);

/**
  * @brief     ��ȡcontext��md5
  * @param     arg1 �ļ�·��  arg2 flagΪ0��ȡ32λmd5ֵ,����Ϊ16λmd5ֵ
  * @retval    �ɹ�����md5ֵ,����ΪNULL
  * @attention �˺�����̬����md5ֵ,������Ҫ����free�ͷ��ڴ�
  */
char *md5sum(const char *path, int flag);


#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/
































