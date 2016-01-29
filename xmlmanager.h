/**
  ******************************************************************************
  * @file    xmlmanager.c
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    05-30-2013
  * @brief   ����xml�ļ�����Ҫ�����޸Ļ��ȡ��������Ժ�ֵ
  ******************************************************************************
  * @attention
  *         �ڵ���getAttributtionItem��setAttributtionItem����֮ǰ�����ȵ���һ��
  *         read_content_from_configfile��������Ҫ��Ԥ�Ȼ�ȡ�����ļ��е���Ϣ����
  *         ����������getAttributtionItem��ֻ�����һ��free_ xmlconfigfile_memory
  *         �ͷŵ�����ռ�õ��ڴ漴�ɣ������������setAttributtionItem����Ӧ�õ�
  *         ��save_content_to_configfile��������(�ڲ��Ѿ��������ڴ��ͷź���)��
  *			<��֧�ֶ��߳�ͬʱ����>
  *
  * <h2><center>&copy; COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ </center></h2>
  ******************************************************************************
  */

#ifndef __XMLMANAGER__H__
#define __XMLMANAGER__H__

#include "stdafx.h"
#include <assert.h>
#include "mystring.h"
#include "commom.h"


#define XML_MAXLEN              200

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief      ��ȡ�����ļ��е���Ϣ��������
  * @param      arg1��·��
  * @retval     �ɹ�����true��ʧ�ܷ���false
  * @attention  �������ļ�������ʱ���ȴ��������ļ�,Ȼ��Ĭ��ֵд�������ļ���
  *             �ٴ������ļ��ж�ȡֵ������(��Ҫstrtok�޷������ַ�������)
  */
BOOL read_content_from_configfile(const char *path);

/**
  * @brief   ���������ļ�
  * @param   arg:����㣻arg2:���ԣ�arg3:ȱʡֵ
  * @retval  �ɹ�����true��ʧ�ܷ���false
  */
BOOL save_content_to_configfile(const char *path);

/**
  * @brief   ��ȡ�����ļ���ָ����������Ϣ
  * @param   arg:����㣻arg2:���ԣ�arg3:ȱʡֵ
  * @retval  �ɹ���������ֵ��ʧ�ܷ���Ĭ��ֵ
  */
char *getAttributtionItem(const char *lastNode, const char *attribution, char *defaultValue, char *receiveValue);

/**
  * @brief   ���������ļ���ָ����������Ϣ
  * @param   arg:����㣻arg2:���ԣ�arg3:ȱʡֵ
  * @retval  �ɹ�����true��ʧ�ܷ���false
  */
BOOL setAttributtionItem(const char *lastNode, const char *attribution, const char *defaultValue);

/**
  * @brief   �ͷ�memory
  * @param   none
  * @retval  none
  */
void free_xmlconfigfile_memory();

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/
