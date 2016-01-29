/**
  ******************************************************************************
  * @file    configfile.h
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    11-14-2013
  * @brief
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#ifndef __CONFIG__H__
#define __CONFIG__H__

#include "includes.h"
#include "configmanager.h"
#include <arpa/inet.h>
#include <sys/stat.h>   //mkdir

#define PARSE_STRING_LEN        300

#ifdef __cplusplus
extern "C" {
#endif


extern CONFIG_FILE_INFO cfi;

/**
  * @brief  读取配置文件信息
  * @param  NULL
  * @retval 成功返回0，否则-1
  */
int get_config_file_info();

#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
