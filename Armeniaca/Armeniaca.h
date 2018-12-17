/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		Armeniaca.h
* @brief	This Program is Armeniaca C-Style Dynamic Link Library Project.
* @author	alopex
* @version	v0.05a
* @date		2018-4-20	v0.01a	alopex	Create Project.
* @date		2018-4-21	v0.02a	alopex	Add Process Function.
* @date		2018-4-26	v0.03a	alopex	Change Call Style From __stdcall to __cdecl.
* @date		2018-4-26	v0.04a	alopex	Add FilePath&Time Function.
* @date		2018-5-16	v0.05a	alopex	Add Read&Write INI File Function.
*/
#pragma once

#ifndef __ARMENIACA_H_
#define __ARMENIACA_H_

//Include Windows Header File
#include <Windows.h>
#include <TlHelp32.h>

//Include C/C++ Running Header File
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <mmreg.h>
#include <wchar.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>
#include <assert.h>

//Include Prunus Dynamic Link Library
#include "PlumCommon.h"
#include "PlumCipherA.h"
#include "PlumConsole.h"
#include "PlumCrypt.h"
#include "PlumFile.h"
#include "PlumGraphics.h"
#include "PlumIni.h"
#include "PlumLog.h"
#include "PlumLogEx.h"
#include "PlumPack.h"
#include "PlumPath.h"
#include "PlumProcess.h"
#include "PlumThread.h"

//Include Prunus Library
#pragma comment(lib, "Prunus.lib")

//Macro Definition
#ifdef ARMENIACA_EXPORTS
#define ARMENIACA_API extern "C" __declspec(dllexport)
#else
#define ARMENIACA_API extern "C" __declspec(dllimport)
#endif

#define	ARMENIACA_CALLMETHOD	__cdecl

//Interface(C-Style)

//★★★★★★★★★★★★★★★★★Interface★★★★★★★★★★★★★★★★★★★★★

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 进程相关(Process)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//------------------------------------------------------------------
// @Function:	 Armeniaca_Process_IsProcessExistA()
// @Purpose: Armeniaca检测进程是否存在
// @Since: v0.01a
// @Para: const char* strProcessName<进程名称>(ASCII)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: bRet = Armeniaca_IsProcessExistA("LiveCore.exe");
// @Describe: 检测进程是否存在(名称)(TRUE:进程存在, FALSE:进程不存在)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Process_IsProcessExistA(const char* strProcessName);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Process_IsProcessExistW()
// @Purpose: Armeniaca检测进程是否存在
// @Since: v0.01a
// @Para: const wchar_t* strProcessName<进程名称>(Unicode)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: bRet = Armeniaca_IsProcessExistW(L"LiveCore.exe");
// @Describe: 检测进程是否存在(名称)(TRUE:进程存在, FALSE:进程不存在)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Process_IsProcessExistW(const wchar_t* strProcessName);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Process_StartProcessA()
// @Purpose: Armeniaca启动进程(在路径目录下)
// @Since: v0.01a
// @Para: const char* strProcessName<进程名称>(ASCII)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: bRet = Armeniaca_StartProcessA("LiveCore.exe");
// @Describe: 启动进程(名称)(TRUE:启动进程成功, FALSE:启动进程失败)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Process_StartProcessA(const char* strProcessName);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Process_StartProcessW()
// @Purpose: Armeniaca启动进程(在路径目录下)
// @Since: v0.01a
// @Para: const wchar_t* strProcessName<进程名称>(Unicode)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: bRet = Armeniaca_StartProcessW(L"LiveCore.exe");
// @Describe: 启动进程(名称)(TRUE:启动进程成功, FALSE:启动进程失败)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Process_StartProcessW(const wchar_t* strProcessName);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 字符转换(Convert)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_A2W_Safe()(不需要释放)
// @Purpose: Armeniaca字符转换(char转wchar_t)
// @Since: v0.01a
// @Para: const char* szArr			// 源字符数组
// @Para: const wchar_t* wszArr		// 目标字符数组(数组传入)
// @Para: int nSize					// 目标数组长度
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: Armeniaca_Convert_A2W_Safe(A, W, sizeof(W));
// @Describe: 字符转换:ASCII转换Unicode(TRUE:转换成功, FALSE:目标数字内存不足)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Convert_A2W_Safe(const char* szArr, const wchar_t* wszArr, int nSize);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_W2A_Safe()(不需要释放)
// @Purpose: Armeniaca字符转换(wchar_t转char)
// @Since: v0.01a
// @Para: const wchar_t* wszArr		// 源字符数组
// @Para: const char* szArr			// 目标字符数组(数组传入)
// @Para: int nSize					// 目标数组长度
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: Armeniaca_Convert_W2A_Safe(W, A, sizeof(A));
// @Describe: 字符转换:Unicode转换ASCII(TRUE:转换成功, FALSE:目标数字内存不足)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Convert_W2A_Safe(const wchar_t* wszArr, const char* szArr, int nSize);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_A2W_UnSafe()(需要释放)(尽量不要用)
// @Purpose: Armeniaca字符转换(char转wchar_t)
// @Since: v0.01a
// @Para: const char* szArr			// 源字符数组
// @Para: wchar_t** ppwszArr		// 目标字符数组(指针传入NULL)
// @Return: None
// @Sample: Armeniaca_Convert_A2W_UnSafe(A, W);
// @Describe: 字符转换:ASCII转换Unicode(传入目标数组NULL指针,需要释放内存!)
//------------------------------------------------------------------
ARMENIACA_API void ARMENIACA_CALLMETHOD Armeniaca_Convert_A2W_UnSafe(const char* szArr, wchar_t** ppwszArr);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_W2A_UnSafe()(需要释放)(尽量不要用)
// @Purpose: Armeniaca字符转换(wchar_t转char)
// @Since: v0.01a
// @Para: const wchar_t* wszArr		// 源字符数组
// @Para: char** ppszArr			// 目标字符数组(数组传入)
// @Return: None
// @Sample: Armeniaca_Convert_W2A_UnSafe(W, A);
// @Describe: 字符转换:Unicode转换ASCII(传入目标数组NULL指针,需要释放内存!)
//------------------------------------------------------------------
ARMENIACA_API void ARMENIACA_CALLMETHOD Armeniaca_Convert_W2A_UnSafe(const wchar_t* wszArr, char** ppszArr);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_A2W_UnSafe2()(需要释放)
// @Purpose: Armeniaca字符转换(char转wchar_t)
// @Since: v0.02a
// @Para: const char* szArr			// 源字符数组
// @Return: wchar_t* wszArr			// 目标字符数组(指针返回)
// @Sample: W = Armeniaca_Convert_A2W_UnSafe2(A);
// @Describe: 字符转换:ASCII转换Unicode(传入目标数组NULL指针,需要释放内存!)
//------------------------------------------------------------------
ARMENIACA_API wchar_t* ARMENIACA_CALLMETHOD Armeniaca_Convert_A2W_UnSafe2(const char* szArr);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_W2A_UnSafe2()(需要释放)
// @Purpose: Armeniaca字符转换(wchar_t转char)
// @Since: v0.02a
// @Para: const wchar_t* wszArr		// 源字符数组
// @Return: char* szArr				// 目标字符数组(指针返回)
// @Sample: A = Armeniaca_Convert_W2A_UnSafe2(W);
//------------------------------------------------------------------
ARMENIACA_API char* ARMENIACA_CALLMETHOD Armeniaca_Convert_W2A_UnSafe2(const wchar_t* wszArr);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 文件路径(FilePath)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//------------------------------------------------------------------
// @Function:	 Armeniaca_FilePath_GetModulePathA()
// @Purpose: Armeniaca获取模块当前路径
// @Since: v0.04a
// @Para: const char* szArr			// 字符数组
// @Para: int nSize					// 数组长度(一般可以MAX_PATH)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: Armeniaca_FilePath_GetModulePathA(szArr, nSize);
// @Describe: 文件路径:获取模块当前文件路径(TRUE:成功, FALSE:失败)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetModulePathA(const char* szArr, int nSize);

//------------------------------------------------------------------
// @Function:	 Armeniaca_FilePath_GetModulePathW()
// @Purpose: Armeniaca获取模块当前路径
// @Since: v0.04a
// @Para: const wchar_t* wszArr		// 字符数组
// @Para: int nSize					// 数组长度(一般可以MAX_PATH)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: Armeniaca_FilePath_GetModulePathW(wszArr, nSize);
// @Describe: 文件路径:获取模块当前文件路径(TRUE:成功, FALSE:失败)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetModulePathW(const wchar_t* wszArr, int nSize);

//------------------------------------------------------------------
// @Function:	 Armeniaca_FilePath_GetLocalPathA()
// @Purpose: Armeniaca获取模块当前路径
// @Since: v0.04a
// @Para: const char* szArr			// 字符数组
// @Para: int nSize					// 数组长度(一般可以MAX_PATH)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: Armeniaca_FilePath_GetLocalPathA(szArr, nSize);
// @Describe: 文件路径:获取模块当前文件夹路径(TRUE:成功, FALSE:失败)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetLocalPathA(const char* szArr, int nSize);

//------------------------------------------------------------------
// @Function:	 Armeniaca_FilePath_GetLocalPathW()
// @Purpose: Armeniaca获取模块当前路径
// @Since: v0.04a
// @Para: const wchar_t* wszArr		// 字符数组
// @Para: int nSize					// 数组长度(一般可以MAX_PATH)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: Armeniaca_FilePath_GetLocalPathW(wszArr, nSize);
// @Describe: 文件路径:获取模块当前文件夹路径(TRUE:成功, FALSE:失败)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetLocalPathW(const wchar_t* wszArr, int nSize);

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_FilePath_GetParentPathA()
// @Purpose: Armeniaca获取模块父级路径
// @Since: v0.04a
// @Para: const char* szArr			// 字符数组
// @Para: int nSize					// 数组长度(一般可以MAX_PATH)
// @Para: int nDeep					// 路径层次(1:前一级路径;2:前两级路径...)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: Armeniaca_FilePath_GetParentPathA(szArr, nSize, 2);
// @Describe: 文件路径:获取模块当前文件夹父级路径(TRUE:成功, FALSE:失败)
//--------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetParentPathA(const char* szArr, int nSize, int nDeep);

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_FilePath_GetParentPathW()
// @Purpose: Armeniaca获取模块父级路径
// @Since: v0.04a
// @Para: const wchar_t* wszArr		// 字符数组
// @Para: int nSize					// 数组长度(一般可以MAX_PATH)
// @Para: int nDeep					// 路径层次(1:前一级路径;2:前两级路径...)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: Armeniaca_FilePath_GetParentPathW(wszArr, nSize, 2);
// @Describe: 文件路径:获取模块当前文件夹父级路径(TRUE:成功, FALSE:失败)
//--------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetParentPathW(const wchar_t* wszArr, int nSize, int nDeep);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 时间相关(Time)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime()
// @Purpose: Armeniaca获取系统时间
// @Since: v0.04a
// @Para: SYSTEMTIME* pLocalTime	//时间结构体指针
// @Return: None
// @Sample: Armeniaca_Time_GetLocalTime(&LocalTime);
// @Describe: 时间:获取当前系统时间
//--------------------------------------------------------------------------
ARMENIACA_API void ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime(SYSTEMTIME* pLocalTime);

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Year()
// @Purpose: Armeniaca获取系统时间(年份)
// @Since: v0.04a
// @Para: None
// @Return: WORD wYear	//时间:年份
// @Sample: wYear = Armeniaca_Time_GetLocalTime_Year();
// @Describe: 时间:获取当前系统时间(年份)
//--------------------------------------------------------------------------
ARMENIACA_API WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Year();

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Month()
// @Purpose: Armeniaca获取系统时间(月份)
// @Since: v0.04a
// @Para: None
// @Return: WORD wMonth	//时间:月份
// @Sample: wMonth = Armeniaca_Time_GetLocalTime_Month();
// @Describe: 时间:获取当前系统时间(月份)
//--------------------------------------------------------------------------
ARMENIACA_API WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Month();

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Day()
// @Purpose: Armeniaca获取系统时间(天数)
// @Since: v0.04a
// @Para: None
// @Return: WORD wDay	//时间:天数
// @Sample: wDay = Armeniaca_Time_GetLocalTime_Day();
// @Describe: 时间:获取当前系统时间(天数)
//--------------------------------------------------------------------------
ARMENIACA_API WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Day();

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Hour()
// @Purpose: Armeniaca获取系统时间(小时)
// @Since: v0.04a
// @Para: None
// @Return: WORD wHour	//时间:小时
// @Sample: wHour = Armeniaca_Time_GetLocalTime_Hour();
// @Describe: 时间:获取当前系统时间(小时)
//--------------------------------------------------------------------------
ARMENIACA_API WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Hour();

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Minute()
// @Purpose: Armeniaca获取系统时间(分钟)
// @Since: v0.04a
// @Para: None
// @Return: WORD wMinute	//时间:分钟
// @Sample: wMinute = Armeniaca_Time_GetLocalTime_Minute();
// @Describe: 时间:获取当前系统时间(分钟)
//--------------------------------------------------------------------------
ARMENIACA_API WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Minute();

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Second()
// @Purpose: Armeniaca获取系统时间(秒)
// @Since: v0.04a
// @Para: None
// @Return: WORD wSecond	//时间:秒
// @Sample: wSecond = Armeniaca_Time_GetLocalTime_Second();
// @Describe: 时间:获取当前系统时间(秒)
//--------------------------------------------------------------------------
ARMENIACA_API WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Second();

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 配置文件相关(Config File)<ini>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_GetKeyValue_String()
// @Purpose: Armeniaca获取配置文件关键字值(字符类型)
// @Since: v0.05a
// @Para: const char* szArrFile			// 配置文件文件路径<in>(eg: D:\\LiveConfig.ini)
// @Para: const char* szArrSection		// 配置文件关键段名称<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// 配置文件关键字名称<in>(eg: LiveCoreMode=0)
// @Para: const char* szArrDefault		// 配置文件缺省值<in>(eg: 0)
// @Para: char* szArrValue				// 配置文件关键字值数组地址<out>
// @Para: DWORD dwSize					// 配置文件关键字值数组长度<in>
// @Return: BOOL bRet					// 返回值: (TRUE: 成功 FALSE: 失败)
// @Sample: bRet = Armeniaca_Config_GetKeyValue_String("D:\\LiveConfig.ini", "LIVECOREMODE", "LiveCoreMode", "0", chArr, MAX_PATH);
// @Describe: 获取配置文件(INI)关键字值(字符类型)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_GetKeyValue_String(const char* szArrFile, const char* szArrSection, const char* szArrKey, const char* szArrDefault, char* szArrValue, DWORD dwSize);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_GetKeyValue_Int()
// @Purpose: Armeniaca获取配置文件关键字值(值类型)
// @Since: v0.05a
// @Para: const char* szArrFile			// 配置文件文件路径<in>(eg: D:\\LiveConfig.ini)
// @Para: const char* szArrSection		// 配置文件关键段名称<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// 配置文件关键字名称<in>(eg: LiveCoreMode=0)
// @Para: const char* szArrDefault		// 配置文件缺省值<in>(eg: 0)
// @Para: int* pValue					// 配置文件关键字值<out>
// @Return: BOOL bRet					// 返回值: (TRUE: 成功 FALSE: 失败)
// @Sample: bRet = Armeniaca_Config_GetKeyValue_Int("D:\\LiveConfig.ini", "LIVECOREMODE", "LiveCoreMode", "0", &dwValue);
// @Describe: 获取配置文件(INI)关键字值(值类型)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_GetKeyValue_Int(const char* szArrFile, const char* szArrSection, const char* szArrKey, const char* szArrDefault, int* pValue);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_SetKeyValue_String()
// @Purpose: Armeniaca设置配置文件关键字值(字符类型)
// @Since: v0.05a
// @Para: const char* szArrFile			// 配置文件文件路径<in>(eg: D:\\LiveConfig.ini)
// @Para: const char* szArrSection		// 配置文件关键段名称<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// 配置文件关键字名称<in>(eg: LiveCoreMode=0)
// @Para: const char* szArrValue		// 配置文件关键字值<in>
// @Return: BOOL bRet					// 返回值: (TRUE: 成功 FALSE: 失败)
// @Sample: bRet = Armeniaca_Config_SetKeyValue_String("D:\\LiveConfig.ini", "LIVECOREMODE", "LiveCoreMode", "0");
// @Describe: 设置配置文件(INI)关键字值(字符类型)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_SetKeyValue_String(const char* szArrFile, const char* szArrSection, const char* szArrKey, const char* szArrValue);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_SetKeyValue_Int()
// @Purpose: Armeniaca设置配置文件关键字值(值类型)
// @Since: v0.05a
// @Para: const char* szArrFile			// 配置文件文件路径<in>(eg: D:\\LiveConfig.ini)
// @Para: const char* szArrSection		// 配置文件关键段名称<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// 配置文件关键字名称<in>(eg: LiveCoreMode=0)
// @Para: int nValue					// 配置文件关键字值<in>
// @Return: BOOL bRet					// 返回值: (TRUE: 成功 FALSE: 失败)
// @Sample: bRet = Armeniaca_Config_SetKeyValue_String("D:\\LiveConfig.ini", "LIVECORESHOWMODE", "LiveCoreShowFontSize", 20);
// @Describe: 设置配置文件(INI)关键字值(值类型)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_SetKeyValue_Int(const char* szArrFile, const char* szArrSection, const char* szArrKey, int nValue);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_GetKeyValue_Local_String()
// @Purpose: Armeniaca获取配置文件关键字值(字符类型)
// @Since: v0.05a
// @Para: const char* szArrFileName		// 配置文件文件路径<in>(eg: LiveConfig.ini)		//<<<这里只需要写短文件名(相对于exe目录)
// @Para: const char* szArrSection		// 配置文件关键段名称<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// 配置文件关键字名称<in>(eg: LiveCoreMode=0)
// @Para: const char* szArrDefault		// 配置文件缺省值<in>(eg: 0)
// @Para: char* szArrValue				// 配置文件关键字值数组地址<out>
// @Para: DWORD dwSize					// 配置文件关键字值数组长度<in>
// @Return: BOOL bRet					// 返回值: (TRUE: 成功 FALSE: 失败)
// @Sample: bRet = Armeniaca_Config_GetKeyValue_Local_String("LiveConfig.ini", "LIVECOREMODE", "LiveCoreMode", "0", chArr, MAX_PATH);
// @Describe: 获取配置文件(INI)关键字值(字符类型)(相对文件名称)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_GetKeyValue_Local_String(const char* szArrFileName, const char* szArrSection, const char* szArrKey, const char* szArrDefault, char* szArrValue, DWORD dwSize);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_GetKeyValue_Local_Int()
// @Purpose: Armeniaca获取配置文件关键字值(值类型)
// @Since: v0.05a
// @Para: const char* szArrFileName		// 配置文件文件路径<in>(eg: LiveConfig.ini)		//<<<这里只需要写短文件名(相对于exe目录)
// @Para: const char* szArrSection		// 配置文件关键段名称<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// 配置文件关键字名称<in>(eg: LiveCoreMode=0)
// @Para: const char* szArrDefault		// 配置文件缺省值<in>(eg: 0)
// @Para: int* pValue					// 配置文件关键字值<out>
// @Return: BOOL bRet					// 返回值: (TRUE: 成功 FALSE: 失败)
// @Sample: bRet = Armeniaca_Config_GetKeyValue_Local_Int("LiveConfig.ini", "LIVECOREMODE", "LiveCoreMode", "0", &dwValue);
// @Describe: 获取配置文件(INI)关键字值(值类型)(相对文件名称)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_GetKeyValue_Local_Int(const char* szArrFileName, const char* szArrSection, const char* szArrKey, const char* szArrDefault, int* pValue);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_SetKeyValue_Local_String()
// @Purpose: Armeniaca设置配置文件关键字值(字符类型)
// @Since: v0.05a
// @Para: const char* szArrFileName		// 配置文件文件路径<in>(eg: LiveConfig.ini)		//<<<这里只需要写短文件名(相对于exe目录)
// @Para: const char* szArrSection		// 配置文件关键段名称<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// 配置文件关键字名称<in>(eg: LiveCoreMode=0)
// @Para: const char* szArrValue		// 配置文件关键字值<in>
// @Return: BOOL bRet					// 返回值: (TRUE: 成功 FALSE: 失败)
// @Sample: bRet = Armeniaca_Config_SetKeyValue_Local_String("LiveConfig.ini", "LIVECOREMODE", "LiveCoreMode", "0");
// @Describe: 设置配置文件(INI)关键字值(字符类型)(相对文件名称)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_SetKeyValue_Local_String(const char* szArrFileName, const char* szArrSection, const char* szArrKey, const char* szArrValue);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_SetKeyValue_Local_Int()
// @Purpose: Armeniaca设置配置文件关键字值(值类型)
// @Since: v0.05a
// @Para: const char* szArrFileName		// 配置文件文件路径<in>(eg: LiveConfig.ini)		//<<<这里只需要写短文件名(相对于exe目录)
// @Para: const char* szArrSection		// 配置文件关键段名称<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// 配置文件关键字名称<in>(eg: LiveCoreMode=0)
// @Para: int nValue					// 配置文件关键字值<in>
// @Return: BOOL bRet					// 返回值: (TRUE: 成功 FALSE: 失败)
// @Sample: bRet = Armeniaca_Config_SetKeyValue_String("LiveConfig.ini", "LIVECORESHOWMODE", "LiveCoreShowFontSize", 20);
// @Describe: 设置配置文件(INI)关键字值(值类型)(相对文件名称)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_SetKeyValue_Local_Int(const char* szArrFileName, const char* szArrSection, const char* szArrKey, int nValue);


#endif // !__ARMENIACA_H_

