/**
  ******************************************************************************
  * @file    commom.c
  * @author  Dragon.Chen
  * @version V1.5.0
  * @date    07-10-2013
  * @brief   �Գ��ù��ܷ�װ�ĺ�����(��Щ�����޷����ֵ�ĳ�����庯�����ͷ�ļ���)
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ </center></h2>
  ******************************************************************************
  */

#include "commom.h"


#if defined USE_LINUX
/**
  * @brief  ��ȡAPIִ��ʧ�ܵ�ԭ��
  * @param  arg1:����ȼ�, arg2:˭�����쳣
  * @retval ���ش�����Ϣ
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
  * @brief  ��ȡAPIִ��ʧ�ܵ�ԭ��
  * @param  arg1:����ȼ�, arg2:˭�����쳣
  * @retval ���ش�����Ϣ
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
  * @brief  ��ȡsocketִ��ʧ�ܵ�ԭ��
  * @param  arg1:����ȼ�, arg2:˭�����쳣
  * @retval ���ش�����Ϣ
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
  * @brief  �����ļ��Ĵ�С
  * @param  arg1���ļ���
  * @retval �ļ���С
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
  * @brief  ��ȡ��ǰʱ��
  * @param  arg1���洢ʱ���ַ�����, arg2��ʱ���ʽ
  * @retval �ɹ����ص�ǰʱ�䣬ʧ�ܷ���NULL
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
    {   ///������ʱ�����м��޵� 20130703214724
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
    {   ///������ʱ����  2013/07/03 21:46:28
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
  * @brief  ��ȡ10�Ķ��ٴη�
  * @param  arg1��ָ��
  * @retval �η���
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
  * @brief  �ַ���ת��������
  * @param  arg1���ַ���
  * @retval ������
  �� @attention ע���ַ��������ǰ���0��9������(�˴��Է������ַ�δ���κδ���)
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
  * @brief  ����ת�����ַ���
  * @param  arg1��Ŀ���ַ��� arg2������ arg3�������� arg4��ת�����
  * @retval Ŀ���ַ���
  �� @attention arg4�еı�ǣ���ת����������ʱ�����Ϊ0; ��ת�����Ǹ�����ʱ,flagҲ��Ǹ���������Чλ��
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
  * @brief   �汾�Ų���
  * @param   arg1:����汾 arg2:ԭ�汾
  * @retval  ���ز���汾
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
  * @brief   ��ȡ��������1�ĸ���
  * @param   1��Ŀ���ַ���  2����������
  * @retval  1�ĸ���
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
  * @brief     ��ȡcontext��md5
  * @param     arg1 �ļ�·��  arg2 flagΪ0��ȡ32λmd5ֵ,����Ϊ16λmd5ֵ
  * @retval    �ɹ�����md5ֵ,����ΪNULL
  * @attention �˺�����̬����md5ֵ,������Ҫ����free�ͷ��ڴ�
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

/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/






