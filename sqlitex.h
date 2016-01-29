/**
  ******************************************************************************
  * @file    sqlite.h
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    04-24-2013
  * @brief   为C语言操作sqlite3数据库，提供一些增删改查的函数接口
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#ifndef __SQLITEX__H__
#define __SQLITEX__H__

#include <sqlite3.h>
#include "includes.h"

/**
  * @brief  链接数据库
  * @param  1、数据库连接对象、2、数据库名
  * @retval -1：链接失败，0：链接成功
  */
int connectToDatabse(sqlite3 **db, const char *database_name);

/**
  * @brief  插入数据
  * @param  1、数据库连接对象、2、执行语句、3、错误信息
  * @retval -1：插入失败，0：插入成功
  */
int insertDataIntoDatabase(sqlite3 *db, char *sql, char **errmsg);

/**
  * @brief  删除数据
  * @param  1、数据库连接对象、2、执行语句、3、错误信息
  * @retval -1：删除失败，0：删除成功
  */
int deleteDataFromDatabase(sqlite3 *db, char *sql, char **errmsg);

/**
  * @brief  更新数据
  * @param  1、数据库连接对象、2、执行语句、3、错误信息
  * @retval -1：更新失败，0：更新成功
  */
int updateDataFromDatabase(sqlite3 *db, char *sql, char **errmsg);

/**
  * @brief  查询数据
  * @param  1、数据库连接对象、2、执行语句、3、错误信息
  * @retval -1：查询失败，0：查询成功
  * @attention 查询到的数据用完必须释放
  */
int queryDataFromDatabase(sqlite3 *db, char *sql, char ***result, int *rows, int *cols, char **errmsg);

/**
  * @brief  关闭数据库
  * @param  1、数据库连接对象
  * @retval -1：链接失败，0：链接成功
  */
int closeDatabase(sqlite3 *db);

#endif

/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
