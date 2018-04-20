/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		Armeniaca.h
* @brief	This Program is Armeniaca C-Style Dynamic Link Library Project.
* @author	alopex
* @version	v0.01a
* @date		2018-4-20	v0.01a	alopex	Create Project.
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

//Macro Definition
#ifdef ARMENIACA_EXPORTS
#define ARMENIACA_API extern "C" __declspec(dllexport)
#else
#define ARMENIACA_API extern "C" __declspec(dllimport)
#endif

#define	ARMENIACA_CALLMODE __stdcall

//Interface(C-Style)

//★★★★★★★★★★★★★★★★★Interface★★★★★★★★★★★★★★★★★★★★★

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 进程相关(Process)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//------------------------------------------------------------------
// @Function:	 Armeniaca_IsProcessExistA()
// @Purpose: Armeniaca检测进程是否存在
// @Since: v0.01a
// @Para: const char* strProcessName<进程名称>(ASCII)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: bRet = Armeniaca_IsProcessExistA("LiveCore.exe");
// @Describe: 检测进程是否存在(名称)(TRUE:进程存在, FALSE:进程不存在)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMODE Armeniaca_IsProcessExistA(const char* strProcessName);

//------------------------------------------------------------------
// @Function:	 Armeniaca_IsProcessExistW()
// @Purpose: Armeniaca检测进程是否存在
// @Since: v0.01a
// @Para: const wchar_t* strProcessName<进程名称>(Unicode)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: bRet = Armeniaca_IsProcessExistW(L"LiveCore.exe");
// @Describe: 检测进程是否存在(名称)(TRUE:进程存在, FALSE:进程不存在)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMODE Armeniaca_IsProcessExistW(const wchar_t* strProcessName);

//------------------------------------------------------------------
// @Function:	 Armeniaca_StartProcessA()
// @Purpose: Armeniaca启动进程(在路径目录下)
// @Since: v0.01a
// @Para: const char* strProcessName<进程名称>(ASCII)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: bRet = Armeniaca_StartProcessA("LiveCore.exe");
// @Describe: 启动进程(名称)(TRUE:启动进程成功, FALSE:启动进程失败)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMODE Armeniaca_StartProcessA(const char* strProcessName);

//------------------------------------------------------------------
// @Function:	 Armeniaca_StartProcessW()
// @Purpose: Armeniaca启动进程(在路径目录下)
// @Since: v0.01a
// @Para: const wchar_t* strProcessName<进程名称>(Unicode)
// @Return: TRUE: 成功 FALSE: 失败
// @Sample: bRet = Armeniaca_StartProcessW(L"LiveCore.exe");
// @Describe: 启动进程(名称)(TRUE:启动进程成功, FALSE:启动进程失败)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMODE Armeniaca_StartProcessW(const wchar_t* strProcessName);

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
ARMENIACA_API BOOL ARMENIACA_CALLMODE Armeniaca_Convert_A2W_Safe(const char* szArr, const wchar_t* wszArr, int nSize);

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
ARMENIACA_API BOOL ARMENIACA_CALLMODE Armeniaca_Convert_W2A_Safe(const wchar_t* wszArr, const char* szArr, int nSize);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_A2W_UnSafe()(需要释放)
// @Purpose: Armeniaca字符转换(char转wchar_t)
// @Since: v0.01a
// @Para: const char* szArr			// 源字符数组
// @Para: wchar_t* pwszArr			// 目标字符数组(指针传入NULL)
// @Return: None
// @Sample: Armeniaca_Convert_A2W_UnSafe(A, W);
// @Describe: 字符转换:ASCII转换Unicode(传入目标数组NULL指针,需要释放内存!)
//------------------------------------------------------------------
ARMENIACA_API void ARMENIACA_CALLMODE Armeniaca_Convert_A2W_UnSafe(const char* szArr, wchar_t* pwszArr);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_W2A_UnSafe()(需要释放)
// @Purpose: Armeniaca字符转换(wchar_t转char)
// @Since: v0.01a
// @Para: const wchar_t* wszArr		// 源字符数组
// @Para: char* pszArr				// 目标字符数组(数组传入)
// @Return: None
// @Sample: Armeniaca_Convert_W2A_UnSafe(W, A);
// @Describe: 字符转换:Unicode转换ASCII(传入目标数组NULL指针,需要释放内存!)
//------------------------------------------------------------------
ARMENIACA_API void ARMENIACA_CALLMODE Armeniaca_Convert_W2A_UnSafe(const wchar_t* wszArr, char* pszArr);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_A2W_UnSafe2()(需要释放)
// @Purpose: Armeniaca字符转换(char转wchar_t)
// @Since: v0.02a
// @Para: const char* szArr			// 源字符数组
// @Return: wchar_t* wszArr			// 目标字符数组(指针返回)
// @Sample: W = Armeniaca_Convert_A2W_UnSafe2(A);
// @Describe: 字符转换:ASCII转换Unicode(传入目标数组NULL指针,需要释放内存!)
//------------------------------------------------------------------
ARMENIACA_API wchar_t* ARMENIACA_CALLMODE Armeniaca_Convert_A2W_UnSafe2(const char* szArr);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_W2A_UnSafe2()(需要释放)
// @Purpose: Armeniaca字符转换(wchar_t转char)
// @Since: v0.02a
// @Para: const wchar_t* wszArr		// 源字符数组
// @Return: char* szArr				// 目标字符数组(指针返回)
// @Sample: A = Armeniaca_Convert_W2A_UnSafe2(W);
//------------------------------------------------------------------
ARMENIACA_API char* ARMENIACA_CALLMODE Armeniaca_Convert_W2A_UnSafe2(const wchar_t* wszArr);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 文件路径(FilePath)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


#endif // !__ARMENIACA_H_

