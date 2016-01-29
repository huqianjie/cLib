/**
  ******************************************************************************
  * @file    base64.h
  * @author  Dragon.Chen
  * @version V2.0.0
  * @date    07-03-2013
  * @brief	 base64�ӽ���
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ </center></h2>
  ******************************************************************************
  */

#ifndef __BASE64X__H__
#define __BASE64X__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DECODE_ERROR 0xffffffff

/**
  * @brief   base64����
  * @param   arg1:����������  arg2:���������ݴ�С  arg3:��������ָ��
  * @retval  base64�������ݳ���
  */
int base64x_encode(const void *data, int size, char **str);

/**
  * @brief   base64����
  * @param   arg1:����������  arg2:���ջ�����  arg3:���ջ�������С
  * @retval  base64�������ݳ���
  */
int base64x_decode(const char *str, void *data, int size);

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/










