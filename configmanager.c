/**
  ******************************************************************************
  * @file    configmanager.c
  * @author  Dragon.Chen
  * @version V2.0.0
  * @date    05-30-2013
  * @brief   解析配置文件，主要用于修改或读取里面的属性和值
  ******************************************************************************
  * @attention
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

#include "configmanager.h"

#ifndef ENABLE_BACKEUP
#define ENABLE_BACKEUP
#undef  ENABLE_BACKEUP
#endif


/**
  * @brief		释放memory
  * @param		arg1:配置文件内容列表  arg2:配置文件内容长度
  * @retval		none
  */
void free_configfile_memory(char **m_list, int *count)
{
    int i = 0;

	for (i=0; i<*count; i++)
	{
		free(m_list[i]);										//释放配置文件
		m_list[i] = NULL;
	}
	free(m_list);												//释放集合
	m_list = NULL;
	*count = 0;
}


/**
  * @brief      读取配置文件中的信息读集合中
  * @param      arg1：路径  arg2:配置文件内容列表  arg3:配置文件内容长度
  * @retval     成功返回true，失败返回false
  * @attention  当配置文件不存在时，先创建配置文件,然后将默认值写到配置文件中
  *             再从配置文件中读取值到集合(主要strtok无法处理字符串常量)
  */
BOOL read_content_from_configfile(const char *path, char ***m_list, int *count)
{
    FILE *fp = NULL;
#ifdef ENABLE_BACKEUP
	FILE *fp2 = NULL;
#endif
    char temp[CONFIG_MAXLEN ]={0};

	assert(path != NULL && m_list != NULL && count != NULL);	//路径是否合法									//路径是否合法
	*count = 0;

#ifdef ENABLE_BACKEUP
    strncpy(temp, path,strlen(path)-4);
    strcat(temp, "bak.conf");
#endif

    if ((fp = fopen(path, "rt")) == NULL)                    	//已可读方式打开文件
    	return FALSE;

#ifdef ENABLE_BACKEUP
    if ((fp2 = fopen(temp, "wt")) == NULL)
        return FALSE;
    memset(temp, 0, CONFIG_MAXLEN );
#endif

    while (fgets(temp, CONFIG_MAXLEN , fp) != NULL)				//从文件读取数据到配置文件中
    {
		*m_list = (char**)realloc(*m_list, sizeof(char*) * ((*count)+1));
        (*m_list)[*count] = (char*)calloc(strlen(temp)+1, 1);   //分配空间
		strcpy((*m_list)[(*count)++], temp);                    //将读取到的数据保存到集合中
#ifdef ENABLE_BACKEUP
		fputs(temp, fp2);                                       //将数据写到备份文件
		fputs("\n", fp2);
#endif
    }

	fclose(fp); 												//关闭文件
#ifdef ENABLE_BACKEUP
	fclose(fp2);
#endif

    return TRUE;
}


/**
  * @brief		获取配置文件中指定的属性信息
  * @param		arg1:属性 arg2:接收区 arg3:接收区大小 arg4:默认值  arg5:配置文件内容列表  arg6:配置文件内容长度
  * @retval		成功返回属性值，失败返回默认值
  * @attention	接收缓存区的大小必须大于配置文件中的做大行长度，此处未做任何检查!!!(配置文件每行不宜大于300个字节)
  */
char *getAttributtionItem(const char *attribution, char *receiveValue, int size, char *defaultValue, char **m_list, const int count)
{
    int i = 0;
    char temp[CONFIG_MAXLEN]={0};

    for (i=0; i<count; i++)
    {
        if (contains(m_list[i], attribution) == 1)          	//获取指定属性值
        {
            strcpy(temp, m_list[i]);                            //备份该属性和值
            get_last_str_by_token(receiveValue, temp, "="); 	//获取属性值
            memset(temp, 0, CONFIG_MAXLEN );                    //初始化数组为0
            strcpy(temp, receiveValue);                     	//备份属性值
            memset(receiveValue, 0, size);  	                //初始化数组为0
            trim(receiveValue, size, temp);                     //去除属性值首尾空格和回车
            return receiveValue;                            	//返回属性值
        }
    }

    strcpy(receiveValue, defaultValue);
    return receiveValue;                                    	//返回默认值
}


/**
  * @brief   设置配置文件中指定的属性信息
  * @param   arg1:属性  arg2:缺省值  arg3:配置文件内容列表  arg4:配置文件内容长度
  * @retval  成功返回true，失败返回false
  */
BOOL setAttributtionItem(const char *attribution, const char *d_value, char **m_list, const int count)
{
    int i = 0;
    char temp[CONFIG_MAXLEN ]={0};

    for (i=0; i<count; i++)
    {
        if (contains(m_list[i], attribution) == 1)
        {
            strcpy(temp, attribution);                      	//创建属性和值
            strcat(temp, " = ");
            strcat(temp, d_value);
            strcat(temp, "\n");

            free(m_list[i]);                                	//释放原来的属性的元素
            m_list[i] = (char*)calloc(strlen(temp)+1, 1);
            strcpy(m_list[i], temp);                        	//为指定元素分配空间，并赋值
            return TRUE;
        }
    }

    return FALSE;
}


/**
  * @brief		保存配置文件
  * @param		arg:父结点；arg2:属性；arg3:缺省值 arg4:配置文件内容列表  arg4:配置文件内容长度
  * @retval		成功返回true，失败返回false
  */
BOOL save_content_to_configfile(const char *path, char **m_list, int *count)
{
    int i = 0;
    FILE *fp = NULL;

    if ((fp = fopen(path, "wt")) == NULL)                 		//以只写方式打开文件
        return FALSE;

	for (i=0; i< *count; i++)									//保存集合中的数据
		fputs(m_list[i], fp);
	fclose(fp);													//关闭文件
    free_configfile_memory(m_list, count);						//释放内存

    return TRUE;
}


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
