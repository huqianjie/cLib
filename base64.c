/**
******************************************************************************
* @file    base64.c
* @author  Dragon.Chen
* @version V2.0.0
* @date    07-03-2013
* @brief   base64加解密
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
******************************************************************************
*/

#include "stdafx.h"
#include "base64.h"

static char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
* @brief   base64编码
* @param   arg1:待编码数据  arg2:待编码数据大小  arg3:返回数据指针
* @retval  base64编码数据长度
*/
int base64_encode(const void *data, int size, char **str)
{
	int i;
	int c;
	char *s, *p;
	const unsigned char *q;

	if (size < 0)
		return -1;
	p = s = (char *) malloc(size * 4 / 3 + 4);
	if (p == NULL)
		return -1;
	q = (const unsigned char *) data;
	i = 0;
	for (i = 0; i < size;) 
	{
		c = q[i++];
		c *= 256;
		if (i < size)
			c += q[i];
		i++;
		c *= 256;
		if (i < size)
			c += q[i];
		i++;
		p[0] = base64_chars[(c & 0x00fc0000) >> 18];
		p[1] = base64_chars[(c & 0x0003f000) >> 12];
		p[2] = base64_chars[(c & 0x00000fc0) >> 6];
		p[3] = base64_chars[(c & 0x0000003f) >> 0];
		if (i > size)
			p[3] = '=';
		if (i > size + 1)
			p[2] = '=';
		p += 4;
	}
	*p = 0;
	*str = s;
	return strlen(s);
}

static int pos(char c)
{
	char *p;
	for (p = base64_chars; *p; p++)
		if (*p == c)
			return p - base64_chars;
	return -1;
}

static unsigned int token_decode(const char *token)
{
	int i;
	unsigned int val = 0;
	int marker = 0;
	if (strlen(token) < 4)
		return DECODE_ERROR;
	for (i = 0; i < 4; i++) 
	{
		val *= 64;
		if (token[i] == '=')
			marker++;
		else if (marker > 0)
			return DECODE_ERROR;
		else
			val += pos(token[i]);
	}
	if (marker > 2)
		return DECODE_ERROR;
	return (marker << 24) | val;
}


/**
* @brief   base64解码
* @param   arg1:待解码数据  arg2:接收缓冲区  arg3:接收缓冲区大小
* @retval  base64解码数据长度
*/
int base64_decode(const char *str, void *data, int size)
{
	const char *p;
	unsigned char *q;
	unsigned char *e = NULL;

	q = (unsigned char*)data;
	if (size >= 0)
		e = q + size;
	for (p = str; *p && (*p == '=' || strchr(base64_chars, *p)); p += 4) 
	{
		unsigned int val = token_decode(p);
		unsigned int marker = (val >> 24) & 0xff;
		if (val == DECODE_ERROR)
			return -1;
		if (e && q >= e)
			return -1;
		*q++ = (val >> 16) & 0xff;
		if (marker < 2)
		{
			if (e && q >= e)
				return -1;
			*q++ = (val >> 8) & 0xff;
		}
		if (marker < 1)
		{
			if (e && q >= e)
				return -1;
			*q++ = val & 0xff;
		}
	}
	return q - (unsigned char *) data;
}


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/

