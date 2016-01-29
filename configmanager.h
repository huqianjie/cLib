/**
  ******************************************************************************
  * @file    configmanager.c
  * @author  Dragon.Chen
  * @version V2.0.0
  * @date    05-30-2013
  * @brief   ���������ļ�����Ҫ�����޸Ļ��ȡ��������Ժ�ֵ
  ******************************************************************************
  *         �ڵ���getAttributtionItem��setAttributtionItem����֮ǰ�����ȵ���һ��
  *         read_content_from_configfile��������Ҫ��Ԥ�Ȼ�ȡ�����ļ��е���Ϣ����
  *         ��ֻ������getAttributtionItem��ֻ�����һ��free_ xmlconfigfile_memory
  *         �ͷŵ�����ռ�õ��ڴ漴�ɣ������������setAttributtionItem����Ӧ�õ�
  *         ��save_content_to_configfile��������(�ڲ��Ѿ��������ڴ��ͷź���)��
  *         <֧�ֶ��߳�ͬʱ����>
  *
  * <h2><center>&copy; COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ </center></h2>
  ******************************************************************************
  */

#ifndef __CONFIGMANAGER__H__
#define __CONFIGMANAGER__H__

#include "includes.h"
#include "stringx.h"

#define CONFIG_MAXLEN              300

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief		�ͷ�memory
  * @param		arg1:�����ļ������б�  arg2:�����ļ����ݳ���
  * @retval		none
  * @attention	��ֹ�����ظ����ã����������쳣��ֹ����!!!
  */
void free_configfile_memory(char **m_list, int *count);


/**
  * @brief      ��ȡ�����ļ��е���Ϣ��������
  * @param      arg1��·��  arg2:�����ļ������б�  arg3:�����ļ����ݳ���
  * @retval     �ɹ�����true��ʧ�ܷ���false
  * @attention  �������ļ�������ʱ���ȴ��������ļ�,Ȼ��Ĭ��ֵд�������ļ���
  *             �ٴ������ļ��ж�ȡֵ������(��Ҫstrtok�޷������ַ�������)
  */
BOOL read_content_from_configfile(const char *path, char ***m_list, int *count);


/**
  * @brief		��ȡ�����ļ���ָ����������Ϣ
  * @param		arg1:���� arg2:������ arg3:��������С arg4:Ĭ��ֵ  arg5:�����ļ������б�  arg6:�����ļ����ݳ���
  * @retval		�ɹ���������ֵ��ʧ�ܷ���Ĭ��ֵ
  * @attention	���ջ������Ĵ�С������������ļ��е������г��ȣ��˴�δ���κμ��!!!(�����ļ�ÿ�в��˴���300���ֽ�)
  */
char *getAttributtionItem(const char *attribution, char *receiveValue, int size,
                          char *defaultValue, char **m_list, const int count);


/**
  * @brief   ���������ļ���ָ����������Ϣ
  * @param   arg1:����  arg2:ȱʡֵ  arg3:�����ļ������б�  arg4:�����ļ����ݳ���
  * @retval  �ɹ�����true��ʧ�ܷ���false
  */
BOOL setAttributtionItem(const char *attribution, const char *d_value, char **m_list,
                         const int count);


/**
  * @brief		���������ļ�
  * @param		arg:����㣻arg2:���ԣ�arg3:ȱʡֵ arg4:�����ļ������б�  arg4:�����ļ����ݳ���
  * @retval		�ɹ�����true��ʧ�ܷ���false
  * @attention	��ֹ�����ظ����ã����������쳣��ֹ����!!!
  */
BOOL save_content_to_configfile(const char *path, char **m_list, int *count);

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/
