/**
******************************************************************************
* @file    config-util.c
* @author  Dragon.Chen
* @version V1.0.0
* @date    05-20-2014
* @brief   读取配置文件信息，不支持多线程同时访问
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2014 上海今中网络科技有限公司 </center></h2>
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
  * @brief      读取文件字段
  * @param      arg1、文件名
  * @retval     成功返回0，失败-1
  */
int readContent(IN const char *fileName);

/**
  * @brief      获取整型数据
  * @param      arg1、field
  * @retval     成功对应数值，失败defaultvalue
  */
int getInt(IN const char *field, IN int defaultvalue);

/**
  * @brief      获取字符串
  * @param      arg1、field
  * @retval     成功对应数值，失败defaultValue
  */
char *getString(IN const char *field, IN char *defaultValue);

/**
  * @brief      设置整型数据
  * @param      arg1、field arg2、newValue
  * @retval     NULL
  */
void setInt(IN const char *field, IN int newValue);

/**
  * @brief      设置字符串数据
  * @param      arg1、field arg2、newValue
  * @retval     NULL
  */
void setString(IN const char *field, const char *newValue);

/**
  * @brief      保存数据到文件(修改文件数据时需调用)
  * @param      arg1、pathName
  * @retval     NULL
  */
void commit(const char *pathName);

/**
  * @brief      释放占用的内存(必须调用)
  * @param      arg1、pathName
  * @retval     NULL
  */
void freeContent();


#endif // __CONFIG__H__

/******************* (C) COPYRIGHT 2014 上海今中网络科技有限公司 *****END OF FILE****/
