/**
  ******************************************************************************
  * @file    mysqlite.c
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    02-28-2013
  * @brief   为C语言操作MySQL数据库，提供一些增删改查的函数接口
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */


#ifndef __MYSQLX__H__
#define __MYSQLX__H__

#include <mysql/mysql.h>
#include "includes.h"


/**
  * @brief  链接数据库
  * @param  MySQL数据结构、数据库用户名、密码、数据库名
  * @retval -1：链接失败，0：链接成功
  */
int connectToDatabse(MYSQL** conn_ptr, char* name, char* password, char* database_name);


/**
  * @brief  插入数据
  * @param  MySQL数据结构、执行语句
  * @retval -1：链接成功，0：链接失败
  */
int insertDataIntoDatabase(MYSQL* conn_ptr, char* sql);


/**
  * @brief  删除数据
  * @param  MySQL数据结构、执行语句
  * @retval -1：链接成功，0：链接失败
  */
int deleteDataFromDatabase(MYSQL* conn_ptr, char* sql);


/**
  * @brief  修改数据
  * @param  MySQL数据结构、执行语句
  * @retval -1：链接成功，0：链接失败
  */
int updateDataFromDatabase(MYSQL* conn_ptr, char* sql);


/**
  * @brief  查询数据
  * @param  MySQL数据结构、执行语句
  * @retval 查询失败返回NULL，反之返回查询的数据
  */
MYSQL_RES* queryDataFromDatabase(MYSQL* conn_ptr, char* sql);


/**
  * @brief  关闭数据库
  * @param  MySQL数据结构、查询结果
  * @retval 无
  */
void closeDatabase(MYSQL* conn_ptr, MYSQL_RES* result);

#endif
