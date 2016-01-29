/**
  ******************************************************************************
  * @file    prototypes.h
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    01-15-2013
  * @brief   操作系统相关定义,及相关日志软件宏定义
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#ifndef __PLATFORM__H__
#define __PLATFORM__H__

#define     USE_LINUX

/*************** 操作系统平台差异头文件 */
#ifdef	USE_WIN32
#include <tchar.h>
#include <windows.h>
#ifdef  USE_WIN32_SAFE
#define strcasecmp			_stricmp
#else
#define strcasecmp			stricmp
#endif
#define Delay(n)			Sleep((n) * 1000)
#elif defined (USE_LINUX)
#include <unistd.h>
#define  closesocket        close
#define  ZeroMemory(a, b)	memset((a), 0, (b))
#define  Delay(n)			sleep(n)
/****** BOOL类型 */
typedef enum
{
    FALSE = 0,
    TRUE = !FALSE
} BOOL;
#endif

#if defined (__GNUC__)
#define likely(x)       __builtin_expect((x), 1)
#define unlikely(x)     __builtin_expect((x), 0)
#else
#define likely(x)       (x)
#define unlikely(x)     (x)
#endif

/******************************* 软件相关控制 *************************/
// 是否允许调试
#define ENABLE_DEBUG

//#undef  ENABLE_DEBUG
//#define ROOT_PRIORITY_LEVEL

#endif

/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/














