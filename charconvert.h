/**
  ******************************************************************************
  * @file    charconvert.h
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    07-22-2013
  * @brief   字符编码相互转化
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#ifndef __CHARCONVERT__H__
#define __CHARCONVERT__H__

#include <string.h>
#include <stdlib.h>
#include <iconv.h>

#define     CHARTSET_MAXLEN         512

/**
  * @brief  UTF8转GB2312
  * @param  arg1:待转换字符
            arg2:带转换字符个数
            arg3:转换的字符
            arg4:剩余的字符个数
  * @retval 0:转换成功  1：转换失败
  */
int UTF8_to_GB2312(char *inbuf, size_t inlen, char *outbuf, size_t outlen);

/**
  * @brief  GB2312转UTF8
  * @param  arg1:待转换字符
            arg2:带转换字符个数
            arg3:转换的字符
            arg4:剩余的字符个数
  * @retval 0:转换成功  1：转换失败
  */
int GB2312_to_UTF8(char *inbuf, size_t inlen, char *outbuf, size_t outlen);


#endif


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/

