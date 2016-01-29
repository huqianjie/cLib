/**
  ******************************************************************************
  * @file    sqlite.h
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    04-24-2013
  * @brief   ΪC���Բ���sqlite3���ݿ⣬�ṩһЩ��ɾ�Ĳ�ĺ����ӿ�
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ </center></h2>
  ******************************************************************************
  */

#ifndef __SQLITEX__H__
#define __SQLITEX__H__

#include <sqlite3.h>
#include "includes.h"

/**
  * @brief  �������ݿ�
  * @param  1�����ݿ����Ӷ���2�����ݿ���
  * @retval -1������ʧ�ܣ�0�����ӳɹ�
  */
int connectToDatabse(sqlite3 **db, const char *database_name);

/**
  * @brief  ��������
  * @param  1�����ݿ����Ӷ���2��ִ����䡢3��������Ϣ
  * @retval -1������ʧ�ܣ�0������ɹ�
  */
int insertDataIntoDatabase(sqlite3 *db, char *sql, char **errmsg);

/**
  * @brief  ɾ������
  * @param  1�����ݿ����Ӷ���2��ִ����䡢3��������Ϣ
  * @retval -1��ɾ��ʧ�ܣ�0��ɾ���ɹ�
  */
int deleteDataFromDatabase(sqlite3 *db, char *sql, char **errmsg);

/**
  * @brief  ��������
  * @param  1�����ݿ����Ӷ���2��ִ����䡢3��������Ϣ
  * @retval -1������ʧ�ܣ�0�����³ɹ�
  */
int updateDataFromDatabase(sqlite3 *db, char *sql, char **errmsg);

/**
  * @brief  ��ѯ����
  * @param  1�����ݿ����Ӷ���2��ִ����䡢3��������Ϣ
  * @retval -1����ѯʧ�ܣ�0����ѯ�ɹ�
  * @attention ��ѯ����������������ͷ�
  */
int queryDataFromDatabase(sqlite3 *db, char *sql, char ***result, int *rows, int *cols, char **errmsg);

/**
  * @brief  �ر����ݿ�
  * @param  1�����ݿ����Ӷ���
  * @retval -1������ʧ�ܣ�0�����ӳɹ�
  */
int closeDatabase(sqlite3 *db);

#endif

/******************* (C) COPYRIGHT 2013 �Ϻ���������Ƽ����޹�˾ *****END OF FILE****/
