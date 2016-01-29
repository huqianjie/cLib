/**
  ******************************************************************************
  * @file    datalist.c
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    12-12-2013
  * @brief   登录用户链表
  ******************************************************************************
  * @attention
  *2
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#include "datalist.h"

/**
  * @brief  创建节点
  * @param  NULL
  * @retval 成功返回节点，否则返回NULL
  */
CLIENT_INFO *ci_create_node()
{
    CLIENT_INFO *temp;

    if ( (temp = (CLIENT_INFO*)calloc(1, sizeof(CLIENT_INFO))) == NULL)
        return NULL;
    return temp;
}


/**
  * @brief  头节点是否为空
  * @param  arg1:头节点
  * @retval 空返回0,否则返回1
  */
int ci_head_is_empty(CLIENT_INFO *head)
{
	if(head->next == NULL)
		return 0;
	else
	  	return 1;
}


/**
  * @brief  收索尾结点
  * @param  arg1:头节点
  * @retval 返回尾结点
  */
static CLIENT_INFO *ci_search_tail(CLIENT_INFO *head)
{
    CLIENT_INFO *curr_node;

    curr_node = head;
    while (curr_node->next != NULL)
        curr_node = curr_node->next;
    return curr_node;
}


/**
  * @brief  尾部插入
  * @param  arg1:头结点  arg2:待插入数据
  * @retval 返回尾结点
  */
void ci_insert_tail(CLIENT_INFO *head, CLIENT_INFO *new_node)
{
    CLIENT_INFO *tail_node;

    tail_node = ci_search_tail(head);
    tail_node->next = new_node;
}


/**
  * @brief  头部插入
  * @param  arg1:头结点  arg2:待插入数据
  * @retval 返回尾结点
  */
void ci_insert_head(CLIENT_INFO *head, CLIENT_INFO *new_node)
{
    new_node->next = head->next;
    head->next = new_node;
}


/**
  * @brief  获取链表长度(不包含头)
  * @param  arg1:头结点
  * @retval 返回尾结点
  */
int ci_get_list_size(CLIENT_INFO *head)
{
    int cnt = 0;
    CLIENT_INFO *curr_node = head->next;

    while (curr_node != NULL)
    {
        cnt++;
        curr_node = curr_node->next;
    }

    return cnt;
}


/**
  * @brief  查找结点
  * @param  arg1:头结点  arg2:查找条件
  * @retval 成功返回结点，否则返回NULL
  */
CLIENT_INFO *ci_query_node(CLIENT_INFO *head, ev_io *w)
{
    CLIENT_INFO *curr_node;
    CLIENT_INFO *prev_node;

    prev_node = head;
    curr_node = head->next;
    while (curr_node != NULL)
    {
        if (curr_node->w->fd == w->fd)
        {
            (void)prev_node;
            return curr_node;
        }

        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    return NULL;
}


/**
  * @brief  删除指定结点
  * @param  arg1:头结点  arg2:查找条件
  * @retval 1删除成功
  */
int ci_remove_node(CLIENT_INFO* head, ev_io *w)
{
    CLIENT_INFO *curr_node;
    CLIENT_INFO *prev_node;
    prev_node = head;
    curr_node = head->next;
    while (curr_node != NULL)
    {
        if (curr_node->w->fd == w->fd)
        {
            prev_node->next = curr_node->next;
            free(curr_node);
            return 1;
        }

        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    return 0;
}


/**
  * @brief  销毁所有的结点
  * @param  arg1:头结点
  * @retval NULL
  */
void ci_destroy_node(CLIENT_INFO *head)
{
    CLIENT_INFO *curr_node;
    CLIENT_INFO *next_node;

    curr_node = head->next;
    while(curr_node != NULL)
    {
        next_node = curr_node->next;
        free(curr_node);
        curr_node = next_node;
    }

    free(head);
    head = NULL;
}

/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/



