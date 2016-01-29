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

#include "xmlmanager.h"

int  count = 0;                             					//集合下标索引
char **m_list = NULL;											//配置文件集合


/**
  * @brief   释放memory
  * @param   none
  * @retval  none
  */
void free_xmlconfigfile_memory()
{
    int i = 0;

	for (i=0; i<count; i++)
	{
		free(m_list[i]);										//释放配置文件
		m_list[i] = NULL;
	}
	free(m_list);												//释放集合
	m_list = NULL;
	count = 0;													//防止重复释放
}


/**
  * @brief      读取配置文件中的信息读集合中
  * @param      arg1、路径
  * @retval     成功返回true，失败返回false
  * @attention  当配置文件不存在时，先创建配置文件,然后将默认值写到配置文件中
  *             再从配置文件中读取值到集合(主要strtok无法处理字符串常量)
  */
BOOL read_content_from_configfile(const char *path)
{
    FILE *fp = NULL;
    char temp[XML_MAXLEN]={0};

    assert(path != NULL);										//路径是否合法
    if ((fp = fopen(path, "rt")) == NULL)                    	//已可读方式打开文件
    	return FALSE;

    while (fgets(temp, XML_MAXLEN, fp) != NULL)            		//从文件读取数据到配置文件中
    {
		m_list = (char**)realloc(m_list, sizeof(*m_list) * (count+1));
        m_list[count] = (char*)calloc(strlen(temp)+1, 1);   	//分配空间
		strcpy(m_list[count++], temp);                     		//将读取到的数据保存到集合中
    }
	fclose(fp); 												//关闭文件

    return TRUE;
}


/**
  * @brief   获取配置文件中指定的属性信息
  * @param   arg:父结点；arg2:属性；arg3:缺省值；arg4:属性值
  * @retval  成功返回属性值，失败返回默认值
  */
char *getAttributtionItem(const char *lastNode, const char *attribution, char *defaultValue, char *receiveValue)
{
    int i = 0;
    char *spliteList[4];                                    //存放分割的字符串
    BOOL nodeFlag = FALSE;                                  //查找到前结点标记位
    char headNode[30] = {0};                                //前结点头结点
    char tailNode[30] = {0};                                //前结点尾结点
    char temp[XML_MAXLEN] = {0};
    strcpy(headNode, "<");
    strcat(headNode, lastNode);
    strcpy(tailNode, "</");
    strcat(tailNode, lastNode);

    for (i = 0; i < count; i++)
    {
        if (nodeFlag || (contains(m_list[i], headNode) == 1))//如果是前结点头结点将nodeflag置位，直到尾结点
        {
            nodeFlag = TRUE;                                //已经进入当前结点中
            if (contains(m_list[i], tailNode) == 1)         //扫描到尾结点退出
                break;
            else
            {
                if (contains(m_list[i], attribution) == 1)  //将要提取的字段
                {
                    strcpy(temp, m_list[i]);                //此处必须将指定值赋值到temp中否则将会将集合中数据修改掉
                    spliteList[0] = strtok(temp, "\"");
                    spliteList[1] = strtok(NULL, "\"");
                    spliteList[2] = strtok(NULL, "\"");
                    spliteList[3] = strtok(NULL, "\"");     //返回查询到的属性值
                    trim(receiveValue, spliteList[3]);      //去除空格
                    return receiveValue;
                }
            }
        }
    }

	strcpy(receiveValue, defaultValue);
    return receiveValue;                                    //查询失败返回默认值
}


/**
  * @brief   设置配置文件中指定的属性信息
  * @param   arg:父结点；arg2:属性；arg3:缺省值
  * @retval  成功返回true，失败返回false
  */
BOOL setAttributtionItem(const char *lastNode, const char *attribution, const char *d_value)
{
    int i = 0;
    char *spliteList[5];                                    //获取集合长度
    BOOL nodeFlag = FALSE;                                  //查找到前结点标记位
    char headNode[30] = {0};                                //前结点头结点
    char tailNode[30] = {0};                                //前结点尾结点
    char temp[XML_MAXLEN] = {0};
    char temp2[XML_MAXLEN] = {0};
    strcpy(headNode, "<");
    strcat(headNode, lastNode);
    strcpy(tailNode, "</");
    strcat(tailNode, lastNode);

    for (i = 0; i < count; i++)
    {
        if (nodeFlag || (contains(m_list[i], headNode) == 1))//如果是前结点头结点将nodeflag置位，直到尾结点
        {
            nodeFlag = TRUE;                                //已经进入当前结点中
            if (contains(m_list[i], tailNode) == 1)         //扫描到尾结点退出
                break;
            else
            {
                if (contains(m_list[i], attribution) == 1)
                {
					strcpy(temp, m_list[i]);
                    spliteList[0] = strtok(temp, "\"");
                    spliteList[1] = strtok(NULL, "\"");     //拆分字符串，获取字段
                    spliteList[2] = strtok(NULL, "\"");

                    strcpy(temp2, spliteList[0]);            //组合成xml文件格式
                    strcat(temp2, "\"");
                    strcat(temp2, spliteList[1]);
                    strcat(temp2, "\"");
                    strcat(temp2, spliteList[2]);
                    strcat(temp2, "\"");
					strcat(temp2, d_value);
                    strcat(temp2, "\"/>\n");

                    free(m_list[i]);                        //释放该属性的元素
                    m_list[i] = (char*)calloc(strlen(temp2)+1, 1);
                    strcpy(m_list[i], temp2);               
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}


/**
  * @brief   保存配置文件
  * @param   arg:父结点；arg2:属性；arg3:缺省值
  * @retval  成功返回true，失败返回false
  */
BOOL save_content_to_configfile(const char *path)
{
    int i = 0;
    FILE *fp = NULL;

    if ((fp = fopen(path, "wt")) == NULL)                 	//以只写方式打开文件
        return FALSE;

	for (i=0; i< count; i++)								//保存集合中的数据
		fputs(m_list[i], fp);
	fclose(fp);												//关闭文件
    free_xmlconfigfile_memory();				      		//释放内存

    return TRUE;
}


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
