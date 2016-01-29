/**
  ******************************************************************************
  * @file    xmlmanager.c
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    05-30-2013
  * @brief   ����xml�ļ�����Ҫ�����޸Ļ��ȡ��������Ժ�ֵ
  ******************************************************************************
  * @attention
  *         �ڵ���getAttributtionItem��setAttributtionItem����֮ǰ�����ȵ���һ��
  *         read_content_from_configfile��������Ҫ��Ԥ�Ȼ�ȡ�����ļ��е���Ϣ����
  *         ����������getAttributtionItem��ֻ�����һ��free_ xmlconfigfile_memory
  *         �ͷŵ�����ռ�õ��ڴ漴�ɣ������������setAttributtionItem����Ӧ�õ�
  *         ��save_content_to_configfile��������(�ڲ��Ѿ��������ڴ��ͷź���)��
  *			<��֧�ֶ��߳�ͬʱ����>
  *
  * <h2><center>&copy; COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ </center></h2>
  ******************************************************************************
  */

#include "xmlmanager.h"

int  count = 0;                             					//�����±�����
char **m_list = NULL;											//�����ļ�����


/**
  * @brief   �ͷ�memory
  * @param   none
  * @retval  none
  */
void free_xmlconfigfile_memory()
{
    int i = 0;

	for (i=0; i<count; i++)
	{
		free(m_list[i]);										//�ͷ������ļ�
		m_list[i] = NULL;
	}
	free(m_list);												//�ͷż���
	m_list = NULL;
	count = 0;													//��ֹ�ظ��ͷ�
}


/**
  * @brief      ��ȡ�����ļ��е���Ϣ��������
  * @param      arg1��·��
  * @retval     �ɹ�����true��ʧ�ܷ���false
  * @attention  �������ļ�������ʱ���ȴ��������ļ�,Ȼ��Ĭ��ֵд�������ļ���
  *             �ٴ������ļ��ж�ȡֵ������(��Ҫstrtok�޷������ַ�������)
  */
BOOL read_content_from_configfile(const char *path)
{
    FILE *fp = NULL;
    char temp[XML_MAXLEN]={0};

    assert(path != NULL);										//·���Ƿ�Ϸ�
    if ((fp = fopen(path, "rt")) == NULL)                    	//�ѿɶ���ʽ���ļ�
    	return FALSE;

    while (fgets(temp, XML_MAXLEN, fp) != NULL)            		//���ļ���ȡ���ݵ������ļ���
    {
		m_list = (char**)realloc(m_list, sizeof(*m_list) * (count+1));
        m_list[count] = (char*)calloc(strlen(temp)+1, 1);   	//����ռ�
		strcpy(m_list[count++], temp);                     		//����ȡ�������ݱ��浽������
    }
	fclose(fp); 												//�ر��ļ�

    return TRUE;
}


/**
  * @brief   ��ȡ�����ļ���ָ����������Ϣ
  * @param   arg:����㣻arg2:���ԣ�arg3:ȱʡֵ��arg4:����ֵ
  * @retval  �ɹ���������ֵ��ʧ�ܷ���Ĭ��ֵ
  */
char *getAttributtionItem(const char *lastNode, const char *attribution, char *defaultValue, char *receiveValue)
{
    int i = 0;
    char *spliteList[4];                                    //��ŷָ���ַ���
    BOOL nodeFlag = FALSE;                                  //���ҵ�ǰ�����λ
    char headNode[30] = {0};                                //ǰ���ͷ���
    char tailNode[30] = {0};                                //ǰ���β���
    char temp[XML_MAXLEN] = {0};
    strcpy(headNode, "<");
    strcat(headNode, lastNode);
    strcpy(tailNode, "</");
    strcat(tailNode, lastNode);

    for (i = 0; i < count; i++)
    {
        if (nodeFlag || (contains(m_list[i], headNode) == 1))//�����ǰ���ͷ��㽫nodeflag��λ��ֱ��β���
        {
            nodeFlag = TRUE;                                //�Ѿ����뵱ǰ�����
            if (contains(m_list[i], tailNode) == 1)         //ɨ�赽β����˳�
                break;
            else
            {
                if (contains(m_list[i], attribution) == 1)  //��Ҫ��ȡ���ֶ�
                {
                    strcpy(temp, m_list[i]);                //�˴����뽫ָ��ֵ��ֵ��temp�з��򽫻Ὣ�����������޸ĵ�
                    spliteList[0] = strtok(temp, "\"");
                    spliteList[1] = strtok(NULL, "\"");
                    spliteList[2] = strtok(NULL, "\"");
                    spliteList[3] = strtok(NULL, "\"");     //���ز�ѯ��������ֵ
                    trim(receiveValue, spliteList[3]);      //ȥ���ո�
                    return receiveValue;
                }
            }
        }
    }

	strcpy(receiveValue, defaultValue);
    return receiveValue;                                    //��ѯʧ�ܷ���Ĭ��ֵ
}


/**
  * @brief   ���������ļ���ָ����������Ϣ
  * @param   arg:����㣻arg2:���ԣ�arg3:ȱʡֵ
  * @retval  �ɹ�����true��ʧ�ܷ���false
  */
BOOL setAttributtionItem(const char *lastNode, const char *attribution, const char *d_value)
{
    int i = 0;
    char *spliteList[5];                                    //��ȡ���ϳ���
    BOOL nodeFlag = FALSE;                                  //���ҵ�ǰ�����λ
    char headNode[30] = {0};                                //ǰ���ͷ���
    char tailNode[30] = {0};                                //ǰ���β���
    char temp[XML_MAXLEN] = {0};
    char temp2[XML_MAXLEN] = {0};
    strcpy(headNode, "<");
    strcat(headNode, lastNode);
    strcpy(tailNode, "</");
    strcat(tailNode, lastNode);

    for (i = 0; i < count; i++)
    {
        if (nodeFlag || (contains(m_list[i], headNode) == 1))//�����ǰ���ͷ��㽫nodeflag��λ��ֱ��β���
        {
            nodeFlag = TRUE;                                //�Ѿ����뵱ǰ�����
            if (contains(m_list[i], tailNode) == 1)         //ɨ�赽β����˳�
                break;
            else
            {
                if (contains(m_list[i], attribution) == 1)
                {
					strcpy(temp, m_list[i]);
                    spliteList[0] = strtok(temp, "\"");
                    spliteList[1] = strtok(NULL, "\"");     //����ַ�������ȡ�ֶ�
                    spliteList[2] = strtok(NULL, "\"");

                    strcpy(temp2, spliteList[0]);            //��ϳ�xml�ļ���ʽ
                    strcat(temp2, "\"");
                    strcat(temp2, spliteList[1]);
                    strcat(temp2, "\"");
                    strcat(temp2, spliteList[2]);
                    strcat(temp2, "\"");
					strcat(temp2, d_value);
                    strcat(temp2, "\"/>\n");

                    free(m_list[i]);                        //�ͷŸ����Ե�Ԫ��
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
  * @brief   ���������ļ�
  * @param   arg:����㣻arg2:���ԣ�arg3:ȱʡֵ
  * @retval  �ɹ�����true��ʧ�ܷ���false
  */
BOOL save_content_to_configfile(const char *path)
{
    int i = 0;
    FILE *fp = NULL;

    if ((fp = fopen(path, "wt")) == NULL)                 	//��ֻд��ʽ���ļ�
        return FALSE;

	for (i=0; i< count; i++)								//���漯���е�����
		fputs(m_list[i], fp);
	fclose(fp);												//�ر��ļ�
    free_xmlconfigfile_memory();				      		//�ͷ��ڴ�

    return TRUE;
}


/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/
