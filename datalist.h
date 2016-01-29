/**
  ******************************************************************************
  * @file    datalist.h
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    12-12-2013
  * @brief   登录用户链表
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#ifndef __DATALIST__H__
#define __DATALIST__H__

#include "includes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  创建节点
  * @param  NULL
  * @retval 成功返回节点，否则返回NULL
  */
CLIENT_INFO *ci_create_node();


/**
  * @brief  头节点是否为空
  * @param  arg1:头节点
  * @retval 空返回0,否则返回1
  */
int ci_head_is_empty(CLIENT_INFO *head);


/**
  * @brief  尾部插入
  * @param  arg1:头结点  arg2:待插入数据
  * @retval 返回尾结点
  */
void ci_insert_tail(CLIENT_INFO *head, CLIENT_INFO *new_node);


/**
  * @brief  头部插入
  * @param  arg1:头结点  arg2:待插入数据
  * @retval 返回尾结点
  */
void ci_insert_head(CLIENT_INFO *head, CLIENT_INFO *new_node);


/**
  * @brief  获取链表长度(不包含头)
  * @param  arg1:头结点
  * @retval 返回尾结点
  */
int ci_get_list_size(CLIENT_INFO *head);


/**
  * @brief  查找结点
  * @param  arg1:头结点  arg2:查找条件
  * @retval 成功返回结点，否则返回NULL
  */
CLIENT_INFO *ci_query_node(CLIENT_INFO *head, ev_io *w);


/**
  * @brief  删除指定结点
  * @param  arg1:头结点  arg2:查找条件
  * @retval 1删除成功
  */
int ci_remove_node(CLIENT_INFO* head, ev_io *w);


/**
  * @brief  销毁所有的结点
  * @param  arg1:头结点
  * @retval NULL
  */
void ci_destroy_node(CLIENT_INFO *head);


#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/


