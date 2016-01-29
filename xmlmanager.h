/**
  ******************************************************************************
  * @file    xmlmanager.c
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    05-30-2013
  * @brief   解析xml文件，主要用于修改或读取里面的属性和值
  ******************************************************************************
  * @attention
  *         在调用getAttributtionItem和setAttributtionItem函数之前必须先调用一下
  *         read_content_from_configfile函数，主要是预先获取配置文件中的信息。如
  *         果至调用了getAttributtionItem，只需调用一下free_ xmlconfigfile_memory
  *         释放掉集合占用的内存即可，但是如果调用setAttributtionItem，则应该调
  *         用save_content_to_configfile保存设置(内部已经调用了内存释放函数)。
  *			<不支持多线程同时访问>
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
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
  * @brief      读取配置文件中的信息读集合中
  * @param      arg1、路径
  * @retval     成功返回true，失败返回false
  * @attention  当配置文件不存在时，先创建配置文件,然后将默认值写到配置文件中
  *             再从配置文件中读取值到集合(主要strtok无法处理字符串常量)
  */
BOOL read_content_from_configfile(const char *path);

/**
  * @brief   保存配置文件
  * @param   arg:父结点；arg2:属性；arg3:缺省值
  * @retval  成功返回true，失败返回false
  */
BOOL save_content_to_configfile(const char *path);

/**
  * @brief   获取配置文件中指定的属性信息
  * @param   arg:父结点；arg2:属性；arg3:缺省值
  * @retval  成功返回属性值，失败返回默认值
  */
char *getAttributtionItem(const char *lastNode, const char *attribution, char *defaultValue, char *receiveValue);

/**
  * @brief   设置配置文件中指定的属性信息
  * @param   arg:父结点；arg2:属性；arg3:缺省值
  * @retval  成功返回true，失败返回false
  */
BOOL setAttributtionItem(const char *lastNode, const char *attribution, const char *defaultValue);

/**
  * @brief   释放memory
  * @param   none
  * @retval  none
  */
void free_xmlconfigfile_memory();

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
