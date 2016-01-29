/**
  ******************************************************************************
  * @file    charconvert.c
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

#include "charconvert.h"


/**
  * @brief  从一种编码转为另一种编码
  * @param  arg1:原字符编码
            arg2:转换成的字符编码
            arg3:待转换字符
            arg4:带转换字符个数
            arg5:转换的字符
            arg6:剩余的字符个数
  * @retval 0:转换成功  1：转换失败
  */
int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
    iconv_t cd;
    char **pin = &inbuf;
    char **pout = &outbuf;
    cd = iconv_open(to_charset, from_charset);
    if (iconv(cd, pin, &inlen, pout, &outlen) == -1)
        return 1;
    iconv_close(cd) ;
    return 0;
}


/**
  * @brief  UTF8转GB2312
  * @param  arg1:待转换字符
            arg2:带转换字符个数
            arg3:转换的字符
            arg4:剩余的字符个数
  * @retval 0:转换成功  1：转换失败
  */
int UTF8_to_GB2312(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
    return code_convert("UTF-8", "GB2312", inbuf, inlen ,outbuf , outlen);
}


/**
  * @brief  GB2312转UTF8
  * @param  arg1:待转换字符
            arg2:带转换字符个数
            arg3:转换的字符
            arg4:剩余的字符个数
  * @retval 0:转换成功  1：转换失败
  */
int GB2312_to_UTF8(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
    return code_convert("GB2312", "UTF-8", inbuf, inlen, outbuf, outlen);
}


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/










