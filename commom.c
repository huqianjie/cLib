/**
  ******************************************************************************
  * @file    commom.c
  * @author  Dragon.Chen
  * @version V1.5.0
  * @date    07-10-2013
  * @brief   对常用功能封装的函数库(这些函数无法划分到某个具体函数库的头文件中)
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#include "commom.h"


#if defined USE_LINUX
/**
  * @brief  获取API执行失败的原因
  * @param  arg1:错误等级, arg2:谁发生异常
  * @retval 返回错误信息
  */
void get_last_error_message(char *level, char *who)
{
	char *str = NULL;
    char *msg = NULL;

    msg = strdup(strerror(errno));
    str = (char*)malloc((size_t)(strlen(msg) + (who == NULL ? 0 : strlen(who)) + 20));
    sprintf(str, "%s %s", (who == NULL ? "" : who), msg);
	MSG(level, "%s", str);
	free(msg);
	free(str);
}
#endif


#if defined USE_WIN32
/**
  * @brief  获取API执行失败的原因
  * @param  arg1:错误等级, arg2:谁发生异常
  * @retval 返回错误信息
  */
void Get_Last_Error_Message(LPTSTR level, LPTSTR who)
{
	DWORD dw;
	LPTSTR str1 = NULL;
	LPTSTR str2 = NULL;

	assert(level != NULL);
	dw=GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&str1, 0, NULL);
	str2 = (LPTSTR)malloc((who == NULL ? 0 : strlen(who)) + strlen(str1) + 20);
	sprintf(str2, "%s %s", (who == NULL ? "" : who), str1);
	str2[strlen(str2)-2] = 0;
	MSG(level, "%s", str2);

	LocalFree(str1);
	free(str2);
}

/**
  * @brief  获取socket执行失败的原因
  * @param  arg1:错误等级, arg2:谁发生异常
  * @retval 返回错误信息
  */
void Get_Last_Socket_Error_Message(LPTSTR level, LPTSTR who)
{
	DWORD dw;
	LPTSTR str1 = NULL;
	LPTSTR str2 = NULL;

	assert(level != NULL);
	dw = WSAGetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&str1, 0, NULL);
	str2 = (LPTSTR)malloc((who == NULL ? 0 : strlen(who)) + strlen(str1) + 20);
	sprintf(str2, "%s %s", (who == NULL ? "" : who), str1);
	str2[strlen(str2)-2] = 0;
	MSG(level, "%s", str2);

	LocalFree(str1);
	free(str2);
}
#endif


/**
  * @brief  计算文件的大小
  * @param  arg1：文件名
  * @retval 文件大小
  */
long get_file_size(const char *file)
{
    FILE *fp;
    long file_size;

    if((fp=fopen(file, "rt")) == NULL)
        return -1;

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fclose(fp);

	return file_size;
}


/**
  * @brief  获取当前时间
  * @param  arg1：存储时间字符数组, arg2：时间格式
  * @retval 成功返回当前时间，失败返回NULL
  */
char *get_system_date(char *time_buf, int flag)
{
    time_t lt;
    struct tm *date_time;
    char fmt_time_buf[30] = {0};

    lt = time(NULL);
    date_time = localtime(&lt);
    strftime(fmt_time_buf, 30, "%x %X\n", date_time);

    if (flag == 0)
    {   ///年月日时分秒中间无点 20130703214724
        strcpy(time_buf, "20");
        strncat(time_buf, fmt_time_buf+6, 2);
        strncat(time_buf, fmt_time_buf, 2);
        strncat(time_buf, fmt_time_buf+3, 2);
        strncat(time_buf, fmt_time_buf+9, 2);
        strncat(time_buf, fmt_time_buf+12, 2);
        strncat(time_buf, fmt_time_buf+15, 2);
        return time_buf;
    }
    else
    {   ///年月日时分秒  2013/07/03 21:46:28
        strcpy(time_buf, "20");
        strncat(time_buf, fmt_time_buf+6, 2);
        strcat(time_buf, "/");
        strncat(time_buf, fmt_time_buf, 2);
        strcat(time_buf, "/");
        strncat(time_buf, fmt_time_buf+3, 2);
        strcat(time_buf, " ");
        strncat(time_buf, fmt_time_buf+9, 8);
        return time_buf;
    }
    return NULL;
}


/**
  * @brief  获取10的多少次方
  * @param  arg1：指数
  * @retval 次方数
  */
int my_pow(int index)
{
    int i = 0;
    int sum = 1;
    for (i=0; i< index; i++)
        sum *= 10;
    return sum;
}


/**
  * @brief  字符串转换成整型
  * @param  arg1：字符串
  * @retval 整型数
  × @attention 注意字符串必须是包含0～9的数字(此处对非数字字符未做任何处理)
  */
int string_to_integer(const char *src)
{
    int i = 0;
    int sum = 0;
    int len = strlen(src);
    for (i=0; i<len; i++)
    {
        sum += (src[i]-48) * my_pow(len-i-1);
    }

    return sum;
}


/**
  * @brief  整型转换成字符串
  * @param  arg1：目标字符串 arg2：整数 arg3：浮点数 arg4：转换标记
  * @retval 目标字符串
  × @attention arg4中的标记，当转换的是整数时，标记为0; 当转换的是浮点数时,flag也标记浮点数的有效位数
  */
char *integer_to_string(char *dst, int value1, float value2, int flag)
{
    if (flag == 0)
    {
        sprintf(dst, "%d", value1);
        return dst;
    }
    else
    {
        sprintf(dst, "%f", value2);
        dst[flag+1] = '\0';
        return dst;
    }
    return NULL;
}


/**
  * @brief   版本号补齐
  * @param   arg1:补齐版本 arg2:原版本
  * @retval  返回补齐版本
  */
char *auto_complete_version(char *dst, const char *src)
{
    int  len = 0;
    char *temp;
    char buffer[15] = {0};

    strcpy(buffer, src);

    temp = strtok(buffer, ".");
    while(temp != NULL)
    {
        len = strlen(temp);
        if (len == 1)
        {
            strcat(dst, "00");
            strcat(dst, temp);
        }
        else if (len ==2)
        {
            strcat(dst, "0");
            strcat(dst, temp);
        }
        else
        {
            strcat(dst, temp);
        }
        strcat(dst, ".");

        temp = strtok(NULL, ".");
    }

    dst[strlen(dst)-1] = '\0';
    return dst;
}


/**
  * @brief   获取子网掩码1的个数
  * @param   1：目标字符串  2：子网掩码
  * @retval  1的个数
  */
char *handler_subnet_mask(char * src, char *subnet_mask)
{
    int  cnt1 = 4, cnt2 = 0, value;
    char *temp;
    char buffer[16] = {0};

    strcpy(buffer, subnet_mask);
    temp = strtok(buffer, ".");

    while(temp != NULL)
    {
        cnt1--;
        if (strcmp(temp, "255") != 0)
        {
            value = atoi(temp);
            while (value % 2 == 0)
            {
                value >>= 1;
                if (cnt2 == 8)
                    break;
                cnt2++;
            }
            break;
        }
        temp = strtok(NULL, ".");
    }

    sprintf(src, "%d", 32 - cnt2 - cnt1 * 8);
    return (src);
}

/**
  * @brief     获取context的md5
  * @param     arg1 文件路径  arg2 flag为0获取32位md5值,否则为16位md5值
  * @retval    成功返回md5值,否则为NULL
  * @attention 此函数动态返回md5值,顾最终要调用free释放内存
  */
char *md5sum(const char *path, int flag)
{
#include <openssl/evp.h>
#define MD5_BUF_MAX_LEN  1024
    int i;
    int len;
    FILE *fp;
    char *sum;
    EVP_MD_CTX mdctx;
    unsigned char buffer[MD5_BUF_MAX_LEN];

    if ( (fp = fopen(path, "rb")) == NULL)
        return NULL;

    OpenSSL_add_all_algorithms();
	EVP_MD_CTX_init(&mdctx);
	EVP_DigestInit_ex(&mdctx, EVP_md5(), NULL);
    memset(buffer, 0, MD5_BUF_MAX_LEN);
    while ( (len = fread(buffer, 1, MD5_BUF_MAX_LEN, fp)))
    {
        EVP_DigestUpdate(&mdctx, buffer, len);
        memset(buffer, 0, MD5_BUF_MAX_LEN);
    }
    fclose(fp);

	EVP_DigestFinal_ex(&mdctx, buffer, (unsigned int *)&len);
	EVP_MD_CTX_cleanup(&mdctx);

	sum = (char *)calloc(33, 1);
	if (flag == 0)
        for(i=0; i<len; i++)
            sprintf(sum+i*2, "%02x", buffer[i]);
	else
        for(i=4; i<12; i++)
            sprintf(sum+(i-4)*2, "%02x", buffer[i]);
	return sum;
}

/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/






