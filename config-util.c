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

#include "config-util.h"

#define CONFIG_MAXLEN 512

static int count = 0;
static char **nameList = NULL;
static char **valueList = NULL;

/**
  * @brief      去除字符串的首尾空格和回车
  * @param      arg1、待处理字符串
  * @retval     成功返回去除空格的字符串
  */
static char *trim2(char *s)
{
    char *p = s;
    int len = strlen(p);

/*    while(isspace(p[len - 1]))
		p[--len] = 0;
    while(*p && isspace(*p))
		++p, --len; */
	while( p[len - 1] == ' ' || p[len - 1] == '\r' || p[len - 1] == '\t' || p[len - 1] == '\n' )
		p[--len] = 0;
    while( *p && (*p == ' ' || *p == '\r' || *p == '\t' || *p == '\n') )
		++p, --len;

    memmove(s, p, len + 1);
    return s;
}

/**
  * @brief      读取文件字段
  * @param      arg1、文件名
  * @retval     成功返回0，失败-1
  */
int readContent(IN const char *fileName)
{
    char *temp = NULL;
    char buffer[CONFIG_MAXLEN] = {0};
    FILE *fp = NULL;

    if ((fp = fopen(fileName, "rt")) == NULL)
    	return -1;

    while (fgets(buffer, CONFIG_MAXLEN , fp))
    {
		if (strlen(buffer) < 2)
			continue;
	
        temp = strtok(buffer, "=");
        trim2(temp);
        nameList = (char**) realloc(nameList, sizeof(char*)*(count+1));
        nameList[count] = (char*)calloc(strlen(temp)+1, 1);   //分配空间
        strcpy(nameList[count], temp);

        temp = strtok(NULL, "=");
        trim2(temp);
        valueList = (char**) realloc(valueList, sizeof(char*)*(count+1));
        valueList[count] = (char*)calloc(strlen(temp)+1, 1);
        strcpy(valueList[count++], temp);
    }

	fclose(fp);
	return 0;
}

/**
  * @brief      获取整型数据
  * @param      arg1、field
  * @retval     成功对应数值，失败defaultvalue
  */
int getInt(IN const char *field, IN int defaultvalue)
{
    int i = 0;

    for (i=0; i<count; i++)
    {
        if (strcmp(field, nameList[i]) == 0)
            return atoi(valueList[i]);
    }
    return defaultvalue;
}

/**
  * @brief      获取字符串
  * @param      arg1、field
  * @retval     成功对应数值，失败defaultValue
  */
char *getString(IN const char *field, IN char *defaultValue)
{
    int i = 0;

    for (i=0; i<count; i++)
    {
        if (strcmp(field, nameList[i]) == 0)
            return valueList[i];
    }

    return defaultValue;
}

/**
  * @brief      设置整型数据
  * @param      arg1、field arg2、newValue
  * @retval     NULL
  */
void setInt(IN const char *field, IN int newValue)
{
    int i = 0;
    char buf[5] = {0};
    snprintf(buf, 5, "%d", newValue);

    for (i=0; i<count; i++)
    {
        if (strcmp(field, nameList[i]) == 0)
        {
            free(valueList[i]);
            valueList[i] = (char*)calloc(strlen(buf)+1, 1);
            strcpy(valueList[i], buf);
        }
    }
}

/**
  * @brief      设置字符串数据
  * @param      arg1、field arg2、newValue
  * @retval     NULL
  */
void setString(IN const char *field, const char *newValue)
{
    int i = 0;

    for (i=0; i<count; i++)
    {
        if (strcmp(field, nameList[i]) == 0)
        {
            free(valueList[i]);
            valueList[i] = (char*)calloc(strlen(newValue)+1, 1);
            strcpy(valueList[i], newValue);
        }
    }
}

/**
  * @brief      保存数据到文件(修改文件数据时需调用)
  * @param      arg1、pathName
  * @retval     NULL
  */
void commit(const char *pathName)
{
    int i = 0;
    char buffer[CONFIG_MAXLEN];
    FILE *fp = NULL;

    if ( (fp = fopen(pathName, "wt")) == NULL)
        return;

    for (i=0; i<count; i++)
    {
        memset(buffer, 0, CONFIG_MAXLEN);
        snprintf(buffer, CONFIG_MAXLEN, "%s = %s\n", nameList[i], valueList[i]);
        fputs(buffer, fp);
    }

    fflush(fp);
    fclose(fp);
}

/**
  * @brief      释放占用的内存(必须调用)
  * @param      arg1、pathName
  * @retval     NULL
  */
void freeContent()
{
    int i = 0;

    for (; i<count; i++)
    {
        free(nameList[i]);
        nameList[i] = NULL;
        free(valueList[i]);
        valueList[i] = NULL;
    }

    free(nameList);
    nameList = NULL;
    free(valueList);
    valueList = NULL;
    count = 0;
}

/******************* (C) COPYRIGHT 2014 上海今中网络科技有限公司 *****END OF FILE****/














