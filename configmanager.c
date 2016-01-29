/**
  ******************************************************************************
  * @file    configmanager.c
  * @author  Dragon.Chen
  * @version V2.0.0
  * @date    05-30-2013
  * @brief   ���������ļ�����Ҫ�����޸Ļ��ȡ��������Ժ�ֵ
  ******************************************************************************
  * @attention
  *         �ڵ���getAttributtionItem��setAttributtionItem����֮ǰ�����ȵ���һ��
  *         read_content_from_configfile��������Ҫ��Ԥ�Ȼ�ȡ�����ļ��е���Ϣ����
  *         ��ֻ������getAttributtionItem��ֻ�����һ��free_ xmlconfigfile_memory
  *         �ͷŵ�����ռ�õ��ڴ漴�ɣ������������setAttributtionItem����Ӧ�õ�
  *         ��save_content_to_configfile��������(�ڲ��Ѿ��������ڴ��ͷź���)��
  *         <֧�ֶ��߳�ͬʱ����>
  *
  * <h2><center>&copy; COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ </center></h2>
  ******************************************************************************
  */

#include "configmanager.h"

#ifndef ENABLE_BACKEUP
#define ENABLE_BACKEUP
#undef  ENABLE_BACKEUP
#endif


/**
  * @brief		�ͷ�memory
  * @param		arg1:�����ļ������б�  arg2:�����ļ����ݳ���
  * @retval		none
  */
void free_configfile_memory(char **m_list, int *count)
{
    int i = 0;

	for (i=0; i<*count; i++)
	{
		free(m_list[i]);										//�ͷ������ļ�
		m_list[i] = NULL;
	}
	free(m_list);												//�ͷż���
	m_list = NULL;
	*count = 0;
}


/**
  * @brief      ��ȡ�����ļ��е���Ϣ��������
  * @param      arg1��·��  arg2:�����ļ������б�  arg3:�����ļ����ݳ���
  * @retval     �ɹ�����true��ʧ�ܷ���false
  * @attention  �������ļ�������ʱ���ȴ��������ļ�,Ȼ��Ĭ��ֵд�������ļ���
  *             �ٴ������ļ��ж�ȡֵ������(��Ҫstrtok�޷������ַ�������)
  */
BOOL read_content_from_configfile(const char *path, char ***m_list, int *count)
{
    FILE *fp = NULL;
#ifdef ENABLE_BACKEUP
	FILE *fp2 = NULL;
#endif
    char temp[CONFIG_MAXLEN ]={0};

	assert(path != NULL && m_list != NULL && count != NULL);	//·���Ƿ�Ϸ�									//·���Ƿ�Ϸ�
	*count = 0;

#ifdef ENABLE_BACKEUP
    strncpy(temp, path,strlen(path)-4);
    strcat(temp, "bak.conf");
#endif

    if ((fp = fopen(path, "rt")) == NULL)                    	//�ѿɶ���ʽ���ļ�
    	return FALSE;

#ifdef ENABLE_BACKEUP
    if ((fp2 = fopen(temp, "wt")) == NULL)
        return FALSE;
    memset(temp, 0, CONFIG_MAXLEN );
#endif

    while (fgets(temp, CONFIG_MAXLEN , fp) != NULL)				//���ļ���ȡ���ݵ������ļ���
    {
		*m_list = (char**)realloc(*m_list, sizeof(char*) * ((*count)+1));
        (*m_list)[*count] = (char*)calloc(strlen(temp)+1, 1);   //����ռ�
		strcpy((*m_list)[(*count)++], temp);                    //����ȡ�������ݱ��浽������
#ifdef ENABLE_BACKEUP
		fputs(temp, fp2);                                       //������д�������ļ�
		fputs("\n", fp2);
#endif
    }

	fclose(fp); 												//�ر��ļ�
#ifdef ENABLE_BACKEUP
	fclose(fp2);
#endif

    return TRUE;
}


/**
  * @brief		��ȡ�����ļ���ָ����������Ϣ
  * @param		arg1:���� arg2:������ arg3:��������С arg4:Ĭ��ֵ  arg5:�����ļ������б�  arg6:�����ļ����ݳ���
  * @retval		�ɹ���������ֵ��ʧ�ܷ���Ĭ��ֵ
  * @attention	���ջ������Ĵ�С������������ļ��е������г��ȣ��˴�δ���κμ��!!!(�����ļ�ÿ�в��˴���300���ֽ�)
  */
char *getAttributtionItem(const char *attribution, char *receiveValue, int size, char *defaultValue, char **m_list, const int count)
{
    int i = 0;
    char temp[CONFIG_MAXLEN]={0};

    for (i=0; i<count; i++)
    {
        if (contains(m_list[i], attribution) == 1)          	//��ȡָ������ֵ
        {
            strcpy(temp, m_list[i]);                            //���ݸ����Ժ�ֵ
            get_last_str_by_token(receiveValue, temp, "="); 	//��ȡ����ֵ
            memset(temp, 0, CONFIG_MAXLEN );                    //��ʼ������Ϊ0
            strcpy(temp, receiveValue);                     	//��������ֵ
            memset(receiveValue, 0, size);  	                //��ʼ������Ϊ0
            trim(receiveValue, size, temp);                     //ȥ������ֵ��β�ո�ͻس�
            return receiveValue;                            	//��������ֵ
        }
    }

    strcpy(receiveValue, defaultValue);
    return receiveValue;                                    	//����Ĭ��ֵ
}


/**
  * @brief   ���������ļ���ָ����������Ϣ
  * @param   arg1:����  arg2:ȱʡֵ  arg3:�����ļ������б�  arg4:�����ļ����ݳ���
  * @retval  �ɹ�����true��ʧ�ܷ���false
  */
BOOL setAttributtionItem(const char *attribution, const char *d_value, char **m_list, const int count)
{
    int i = 0;
    char temp[CONFIG_MAXLEN ]={0};

    for (i=0; i<count; i++)
    {
        if (contains(m_list[i], attribution) == 1)
        {
            strcpy(temp, attribution);                      	//�������Ժ�ֵ
            strcat(temp, " = ");
            strcat(temp, d_value);
            strcat(temp, "\n");

            free(m_list[i]);                                	//�ͷ�ԭ�������Ե�Ԫ��
            m_list[i] = (char*)calloc(strlen(temp)+1, 1);
            strcpy(m_list[i], temp);                        	//Ϊָ��Ԫ�ط���ռ䣬����ֵ
            return TRUE;
        }
    }

    return FALSE;
}


/**
  * @brief		���������ļ�
  * @param		arg:����㣻arg2:���ԣ�arg3:ȱʡֵ arg4:�����ļ������б�  arg4:�����ļ����ݳ���
  * @retval		�ɹ�����true��ʧ�ܷ���false
  */
BOOL save_content_to_configfile(const char *path, char **m_list, int *count)
{
    int i = 0;
    FILE *fp = NULL;

    if ((fp = fopen(path, "wt")) == NULL)                 		//��ֻд��ʽ���ļ�
        return FALSE;

	for (i=0; i< *count; i++)									//���漯���е�����
		fputs(m_list[i], fp);
	fclose(fp);													//�ر��ļ�
    free_configfile_memory(m_list, count);						//�ͷ��ڴ�

    return TRUE;
}


/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/
