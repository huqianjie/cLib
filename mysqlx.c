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


#include "mysql.h"


/**
  * @brief  链接数据库
  * @param  MySQL数据结构、数据库用户名、密码、数据库名
  * @retval -1：链接失败，0：链接成功
  */
int connectToDatabse(MYSQL** conn_ptr, char* name, char* password, char* database_name)
{
    if ( !(*conn_ptr = mysql_init(NULL)) )                   // 初始化一个类型为MYSQL的数据结构
        return 0;
    if ( (*conn_ptr = mysql_real_connect(*conn_ptr, "localhost", name, password, database_name, 0, NULL, 0)) )
        return -1;
    return 0;
}


/**
  * @brief  插入数据
  * @param  MySQL数据结构、执行语句
  * @retval -1：链接成功，0：链接失败
  */
int insertDataIntoDatabase(MYSQL* conn_ptr, char* sql)
{
    if(mysql_query(conn_ptr, sql) == 0)                        // 执行插入语句
        return -1;
    return 0;
}


/**
  * @brief  删除数据
  * @param  MySQL数据结构、执行语句
  * @retval -1：链接成功，0：链接失败
  */
int deleteDataFromDatabase(MYSQL* conn_ptr, char* sql)
{
    if(mysql_query(conn_ptr, sql) == 0)                        // 执行插入语句
        return -1;
    return 0;
}


/**
  * @brief  修改数据
  * @param  MySQL数据结构、执行语句
  * @retval -1：链接成功，0：链接失败
  */
int updateDataFromDatabase(MYSQL* conn_ptr, char* sql)
{
    if(mysql_query(conn_ptr, sql) == 0)                        // 执行插入语句
        return -1;
    return 0;
}


/**
  * @brief  查询数据
  * @param  MySQL数据结构、执行语句
  * @retval 查询失败返回NULL，反之返回查询的数据
  */
MYSQL_RES* queryDataFromDatabase(MYSQL* conn_ptr, char* sql)
{
    if (mysql_query(conn_ptr, sql))                             // 执行查询语句
        return NULL;
    else
        return mysql_store_result(conn_ptr);
}


/**
  * @brief  关闭数据库
  * @param  MySQL数据结构、查询结果
  * @retval 无
  */
void closeDatabase(MYSQL* conn_ptr, MYSQL_RES* result)
{
    if (result != NULL)
        mysql_free_result(result);                              // 释放结果资源
    mysql_close(conn_ptr);                                      // 关闭数据库
}


/**********************************END OF FILE*****************************************/

//#include <stdio.h>
//#include <stdlib.h>
//
//#include "mysql.h"
//
//#define USER_NAME       "root"
//#define USER_PSWD       "1083428917"
//#define DATABASENAME    "mydatabase"
//
//char*       sql;
//MYSQL*      conn_ptr;                                           // 获取MYSQL数据结构
//MYSQL_RES*  result;                                             // 查询结果
//MYSQL_ROW   mysql_row;                                          // 获取列
//
//int main()
//{
//    int             index=0;                                    // 索引号
//    int             column=0;                                   // 列数
//    int             row=0;                                      // 行数
//
//    /*链接数据库*/
//    if( connectToDatabse(&conn_ptr, USER_NAME, USER_PSWD, DATABASENAME) == -1 )
//        printf("连接数据库成功！\n");
//    else
//        printf("连接数据库失败！\n");
//
//    /*插入数据*/
//    sql = "insert into student(id, stuName, stuAge, stuSex  ,stuScore) values(5,'王欢', 25,'女', 93)";
//    if( insertDataIntoDatabase(conn_ptr, sql) == -1 )
//        printf("插入数据成功！\n");
//    else
//        printf("插入数据失败！\n");
//
//    /*删除数据*/
//    sql = "delete from student where stuAge=25";
//    if( deleteDataFromDatabase(conn_ptr, sql) == -1 )
//        printf("删除数据成功！\n");
//    else
//        printf("删除数据失败！\n");
//
//    /*修改数据*/
//    sql = "update student set stuName='张林' where stuName='张领'";
//    if( updateDataFromDatabase(conn_ptr, sql) == -1 )
//        printf("修改数据成功！\n");
//    else
//        printf("修改数据失败！\n");
//
//    /*查询数据*/
//    sql = "select * from student";
//    if ((result = queryDataFromDatabase(conn_ptr, sql)) != NULL)
//    {
//        row = (unsigned long)mysql_num_rows(result);                // 表示有几行
//        column = mysql_num_fields(result);                          // 表示有几列
//        printf("行数为:%lu\n", row);
//        printf("列数为:%lu\n", column);
//        while (mysql_row =  mysql_fetch_row(result))
//        {
//            for(index=0; index<column; index++)
//                printf("%s\t\t", mysql_row[index]);
//            printf("\n");
//        }
//    }
//    else
//        printf("查询数据失败！\n");
//
//    /*关闭数据库*/
//    closeDatabase(conn_ptr, result);
//
//    return 0;
//}























