/**
  ******************************************************************************
  * @file    base64.h
  * @author  Dragon.Chen
  * @version V2.0.0
  * @date    07-03-2013
  * @brief	 base64加解密
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
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
  * @brief   base64编码
  * @param   arg1:待编码数据  arg2:待编码数据大小  arg3:返回数据指针
  * @retval  base64编码数据长度
  */
int base64x_encode(const void *data, int size, char **str);

/**
  * @brief   base64解码
  * @param   arg1:待解码数据  arg2:接收缓冲区  arg3:接收缓冲区大小
  * @retval  base64解码数据长度
  */
int base64x_decode(const char *str, void *data, int size);

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/










