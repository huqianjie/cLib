/**
  ******************************************************************************
  * @file    configmanager.c
  * @author  Dragon.Chen
  * @version V2.0.0
  * @date    05-30-2013
  * @brief   解析配置文件，主要用于修改或读取里面的属性和值
  ******************************************************************************
  *         在调用getAttributtionItem和setAttributtionItem函数之前必须先调用一下
  *         read_content_from_configfile函数，主要是预先获取配置文件中的信息。如
  *         果只调用了getAttributtionItem，只需调用一下free_ xmlconfigfile_memory
  *         释放掉集合占用的内存即可，但是如果调用setAttributtionItem，则应该调
  *         用save_content_to_configfile保存设置(内部已经调用了内存释放函数)。
  *         <支持多线程同时访问>
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
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
  * @brief		释放memory
  * @param		arg1:配置文件内容列表  arg2:配置文件内容长度
  * @retval		none
  * @attention	禁止函数重复调用，否则会出现异常终止程序!!!
  */
void free_configfile_memory(char **m_list, int *count);


/**
  * @brief      读取配置文件中的信息读集合中
  * @param      arg1：路径  arg2:配置文件内容列表  arg3:配置文件内容长度
  * @retval     成功返回true，失败返回false
  * @attention  当配置文件不存在时，先创建配置文件,然后将默认值写到配置文件中
  *             再从配置文件中读取值到集合(主要strtok无法处理字符串常量)
  */
BOOL read_content_from_configfile(const char *path, char ***m_list, int *count);


/**
  * @brief		获取配置文件中指定的属性信息
  * @param		arg1:属性 arg2:接收区 arg3:接收区大小 arg4:默认值  arg5:配置文件内容列表  arg6:配置文件内容长度
  * @retval		成功返回属性值，失败返回默认值
  * @attention	接收缓存区的大小必须大于配置文件中的做大行长度，此处未做任何检查!!!(配置文件每行不宜大于300个字节)
  */
char *getAttributtionItem(const char *attribution, char *receiveValue, int size,
                          char *defaultValue, char **m_list, const int count);


/**
  * @brief   设置配置文件中指定的属性信息
  * @param   arg1:属性  arg2:缺省值  arg3:配置文件内容列表  arg4:配置文件内容长度
  * @retval  成功返回true，失败返回false
  */
BOOL setAttributtionItem(const char *attribution, const char *d_value, char **m_list,
                         const int count);


/**
  * @brief		保存配置文件
  * @param		arg:父结点；arg2:属性；arg3:缺省值 arg4:配置文件内容列表  arg4:配置文件内容长度
  * @retval		成功返回true，失败返回false
  * @attention	禁止函数重复调用，否则会出现异常终止程序!!!
  */
BOOL save_content_to_configfile(const char *path, char **m_list, int *count);

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
