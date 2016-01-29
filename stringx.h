/**
  ******************************************************************************
  * @file    stringx.h
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

#ifndef __STRINGX__H__
#define __STRINGX__H__

#ifdef USE_LINUX
#include <string.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief      �ж��ַ����Ƿ���ָ���ַ�����ʼ
  * @param      arg1��Դ�ַ�����arg2�����ַ���
  * @retval     1������ָ���ַ�����ʼ��0�����ǣ�-1�����ַ�����ԽԴ�ַ�������
  */
int start_with(const char *ptr_src, const char *start_str);

/**
  * @brief      �ж��ַ����Ƿ���ָ���ַ�������
  * @param      arg1��Դ�ַ�����arg2�����ַ���
  * @retval     1������ָ���ַ���������0�����ǣ�-1�����ַ�����ԽԴ�ַ�������
  */
int end_with(const char *ptr_src, const char *end_str);

/**
  * @brief      ��ȡָ���ַ��������ַ���
  * @param      arg1������ַ�����arg2��Դ�ַ�����arg3����ַ�
  * @retval     ����ַ���
  * @attention  src�������ַ�������
  */
char *get_last_str_by_token(char *last_str, char *src, const char *token);

/**
  * @brief      ��ȡָ���ַ���ĵ�һ���ַ���
  * @param      arg1������ַ�����arg2��Դ�ַ�����arg3����ַ�
  * @retval     ����ַ���
  * @attention  src�������ַ�������
  */
char *get_first_str_by_token(char *first_str, char *src, const char *token);

/**
  * @brief      ��ȡsrcǰlen�������ַ�������ָ���ַ����ֵĴ���
  * @param      arg1��Դ�ַ�����arg2���������ַ���arg3��ָ���ĳ���
  * @retval     ����ָ���ַ����ֵĴ���
  */
int get_count_specified_char(const char *src, const char ch, int len);

/**
  * @brief      �����ж�Ŀ���ַ����Ƿ���Դ�ַ������ַ���
  * @param      arg1��Դ�ַ�����arg2���������ַ�
  * @retval     �Ƿ���1�����򷵻�-1
  */
int contains(const char *source, const char *target);

/**
  * @brief      Դ�ַ�������Ŀ���ַ����Ĵ���
  * @param      arg1��Դ�ַ�����arg2���������ַ�
  * @retval     �������ذ����Ĵ���(>0)�����򷵻�-1
  */
int containc(const char *src, const char *dst);

/**
  * @brief      ��ȡ���ַ���
  * @param      arg1��Ŀ���ַ����� arg2�� Ŀ���ַ�����С arg3��Դ�ַ�����arg4���ַ�����ʼλ�ã�arg5�ַ�������λ��
  * @retval     �ɹ��������ַ�����ʧ�ܷ���NULL
  */
char *substr(char *dst, int size, const char *src, int begin, int end);

/**
  * @brief      ��ȡ���ַ���
  * @param      arg1��Ŀ���ַ���  arg2�� Ŀ���ַ�����С  arg3��Դ�ַ���  arg4���ַ�����ʼλ��
  * @retval     �ɹ��������ַ�����ʧ�ܷ���NULL
  */
char *substr_by_start_position(char *dst, int size, const char *src, int begin);

/**
  * @brief      ȥ���ַ�������β�ո�ͻس�
  * @param      arg1��Ŀ���ַ���  arg2�� Ŀ���ַ�����С  arg3��Դ�ַ���
  * @retval     �ɹ�����ȥ���ո���ַ���
  * @attention  ���������ɵ��ַ��������ṩ�Ļ�������Сʱ�����ػ�������С���ַ���
  */
char *trim(char *dst, int size, const char *src);

/**
  * @brief      ȥ���ַ�������β�ո�ͻس�
  * @param      arg1���������ַ���
  * @retval     �ɹ�����ȥ���ո���ַ���
  */
void trim2(char *s);

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/
