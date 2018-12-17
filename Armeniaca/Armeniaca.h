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

//������������������Interface����������������������

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �������(Process)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//------------------------------------------------------------------
// @Function:	 Armeniaca_Process_IsProcessExistA()
// @Purpose: Armeniaca�������Ƿ����
// @Since: v0.01a
// @Para: const char* strProcessName<��������>(ASCII)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_IsProcessExistA("LiveCore.exe");
// @Describe: �������Ƿ����(����)(TRUE:���̴���, FALSE:���̲�����)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Process_IsProcessExistA(const char* strProcessName);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Process_IsProcessExistW()
// @Purpose: Armeniaca�������Ƿ����
// @Since: v0.01a
// @Para: const wchar_t* strProcessName<��������>(Unicode)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_IsProcessExistW(L"LiveCore.exe");
// @Describe: �������Ƿ����(����)(TRUE:���̴���, FALSE:���̲�����)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Process_IsProcessExistW(const wchar_t* strProcessName);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Process_StartProcessA()
// @Purpose: Armeniaca��������(��·��Ŀ¼��)
// @Since: v0.01a
// @Para: const char* strProcessName<��������>(ASCII)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_StartProcessA("LiveCore.exe");
// @Describe: ��������(����)(TRUE:�������̳ɹ�, FALSE:��������ʧ��)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Process_StartProcessA(const char* strProcessName);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Process_StartProcessW()
// @Purpose: Armeniaca��������(��·��Ŀ¼��)
// @Since: v0.01a
// @Para: const wchar_t* strProcessName<��������>(Unicode)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_StartProcessW(L"LiveCore.exe");
// @Describe: ��������(����)(TRUE:�������̳ɹ�, FALSE:��������ʧ��)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Process_StartProcessW(const wchar_t* strProcessName);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �ַ�ת��(Convert)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_A2W_Safe()(����Ҫ�ͷ�)
// @Purpose: Armeniaca�ַ�ת��(charתwchar_t)
// @Since: v0.01a
// @Para: const char* szArr			// Դ�ַ�����
// @Para: const wchar_t* wszArr		// Ŀ���ַ�����(���鴫��)
// @Para: int nSize					// Ŀ�����鳤��
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: Armeniaca_Convert_A2W_Safe(A, W, sizeof(W));
// @Describe: �ַ�ת��:ASCIIת��Unicode(TRUE:ת���ɹ�, FALSE:Ŀ�������ڴ治��)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Convert_A2W_Safe(const char* szArr, const wchar_t* wszArr, int nSize);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_W2A_Safe()(����Ҫ�ͷ�)
// @Purpose: Armeniaca�ַ�ת��(wchar_tתchar)
// @Since: v0.01a
// @Para: const wchar_t* wszArr		// Դ�ַ�����
// @Para: const char* szArr			// Ŀ���ַ�����(���鴫��)
// @Para: int nSize					// Ŀ�����鳤��
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: Armeniaca_Convert_W2A_Safe(W, A, sizeof(A));
// @Describe: �ַ�ת��:Unicodeת��ASCII(TRUE:ת���ɹ�, FALSE:Ŀ�������ڴ治��)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Convert_W2A_Safe(const wchar_t* wszArr, const char* szArr, int nSize);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_A2W_UnSafe()(��Ҫ�ͷ�)(������Ҫ��)
// @Purpose: Armeniaca�ַ�ת��(charתwchar_t)
// @Since: v0.01a
// @Para: const char* szArr			// Դ�ַ�����
// @Para: wchar_t** ppwszArr		// Ŀ���ַ�����(ָ�봫��NULL)
// @Return: None
// @Sample: Armeniaca_Convert_A2W_UnSafe(A, W);
// @Describe: �ַ�ת��:ASCIIת��Unicode(����Ŀ������NULLָ��,��Ҫ�ͷ��ڴ�!)
//------------------------------------------------------------------
ARMENIACA_API void ARMENIACA_CALLMETHOD Armeniaca_Convert_A2W_UnSafe(const char* szArr, wchar_t** ppwszArr);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_W2A_UnSafe()(��Ҫ�ͷ�)(������Ҫ��)
// @Purpose: Armeniaca�ַ�ת��(wchar_tתchar)
// @Since: v0.01a
// @Para: const wchar_t* wszArr		// Դ�ַ�����
// @Para: char** ppszArr			// Ŀ���ַ�����(���鴫��)
// @Return: None
// @Sample: Armeniaca_Convert_W2A_UnSafe(W, A);
// @Describe: �ַ�ת��:Unicodeת��ASCII(����Ŀ������NULLָ��,��Ҫ�ͷ��ڴ�!)
//------------------------------------------------------------------
ARMENIACA_API void ARMENIACA_CALLMETHOD Armeniaca_Convert_W2A_UnSafe(const wchar_t* wszArr, char** ppszArr);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_A2W_UnSafe2()(��Ҫ�ͷ�)
// @Purpose: Armeniaca�ַ�ת��(charתwchar_t)
// @Since: v0.02a
// @Para: const char* szArr			// Դ�ַ�����
// @Return: wchar_t* wszArr			// Ŀ���ַ�����(ָ�뷵��)
// @Sample: W = Armeniaca_Convert_A2W_UnSafe2(A);
// @Describe: �ַ�ת��:ASCIIת��Unicode(����Ŀ������NULLָ��,��Ҫ�ͷ��ڴ�!)
//------------------------------------------------------------------
ARMENIACA_API wchar_t* ARMENIACA_CALLMETHOD Armeniaca_Convert_A2W_UnSafe2(const char* szArr);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_W2A_UnSafe2()(��Ҫ�ͷ�)
// @Purpose: Armeniaca�ַ�ת��(wchar_tתchar)
// @Since: v0.02a
// @Para: const wchar_t* wszArr		// Դ�ַ�����
// @Return: char* szArr				// Ŀ���ַ�����(ָ�뷵��)
// @Sample: A = Armeniaca_Convert_W2A_UnSafe2(W);
//------------------------------------------------------------------
ARMENIACA_API char* ARMENIACA_CALLMETHOD Armeniaca_Convert_W2A_UnSafe2(const wchar_t* wszArr);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �ļ�·��(FilePath)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//------------------------------------------------------------------
// @Function:	 Armeniaca_FilePath_GetModulePathA()
// @Purpose: Armeniaca��ȡģ�鵱ǰ·��
// @Since: v0.04a
// @Para: const char* szArr			// �ַ�����
// @Para: int nSize					// ���鳤��(һ�����MAX_PATH)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: Armeniaca_FilePath_GetModulePathA(szArr, nSize);
// @Describe: �ļ�·��:��ȡģ�鵱ǰ�ļ�·��(TRUE:�ɹ�, FALSE:ʧ��)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetModulePathA(const char* szArr, int nSize);

//------------------------------------------------------------------
// @Function:	 Armeniaca_FilePath_GetModulePathW()
// @Purpose: Armeniaca��ȡģ�鵱ǰ·��
// @Since: v0.04a
// @Para: const wchar_t* wszArr		// �ַ�����
// @Para: int nSize					// ���鳤��(һ�����MAX_PATH)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: Armeniaca_FilePath_GetModulePathW(wszArr, nSize);
// @Describe: �ļ�·��:��ȡģ�鵱ǰ�ļ�·��(TRUE:�ɹ�, FALSE:ʧ��)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetModulePathW(const wchar_t* wszArr, int nSize);

//------------------------------------------------------------------
// @Function:	 Armeniaca_FilePath_GetLocalPathA()
// @Purpose: Armeniaca��ȡģ�鵱ǰ·��
// @Since: v0.04a
// @Para: const char* szArr			// �ַ�����
// @Para: int nSize					// ���鳤��(һ�����MAX_PATH)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: Armeniaca_FilePath_GetLocalPathA(szArr, nSize);
// @Describe: �ļ�·��:��ȡģ�鵱ǰ�ļ���·��(TRUE:�ɹ�, FALSE:ʧ��)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetLocalPathA(const char* szArr, int nSize);

//------------------------------------------------------------------
// @Function:	 Armeniaca_FilePath_GetLocalPathW()
// @Purpose: Armeniaca��ȡģ�鵱ǰ·��
// @Since: v0.04a
// @Para: const wchar_t* wszArr		// �ַ�����
// @Para: int nSize					// ���鳤��(һ�����MAX_PATH)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: Armeniaca_FilePath_GetLocalPathW(wszArr, nSize);
// @Describe: �ļ�·��:��ȡģ�鵱ǰ�ļ���·��(TRUE:�ɹ�, FALSE:ʧ��)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetLocalPathW(const wchar_t* wszArr, int nSize);

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_FilePath_GetParentPathA()
// @Purpose: Armeniaca��ȡģ�鸸��·��
// @Since: v0.04a
// @Para: const char* szArr			// �ַ�����
// @Para: int nSize					// ���鳤��(һ�����MAX_PATH)
// @Para: int nDeep					// ·�����(1:ǰһ��·��;2:ǰ����·��...)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: Armeniaca_FilePath_GetParentPathA(szArr, nSize, 2);
// @Describe: �ļ�·��:��ȡģ�鵱ǰ�ļ��и���·��(TRUE:�ɹ�, FALSE:ʧ��)
//--------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetParentPathA(const char* szArr, int nSize, int nDeep);

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_FilePath_GetParentPathW()
// @Purpose: Armeniaca��ȡģ�鸸��·��
// @Since: v0.04a
// @Para: const wchar_t* wszArr		// �ַ�����
// @Para: int nSize					// ���鳤��(һ�����MAX_PATH)
// @Para: int nDeep					// ·�����(1:ǰһ��·��;2:ǰ����·��...)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: Armeniaca_FilePath_GetParentPathW(wszArr, nSize, 2);
// @Describe: �ļ�·��:��ȡģ�鵱ǰ�ļ��и���·��(TRUE:�ɹ�, FALSE:ʧ��)
//--------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetParentPathW(const wchar_t* wszArr, int nSize, int nDeep);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ʱ�����(Time)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime()
// @Purpose: Armeniaca��ȡϵͳʱ��
// @Since: v0.04a
// @Para: SYSTEMTIME* pLocalTime	//ʱ��ṹ��ָ��
// @Return: None
// @Sample: Armeniaca_Time_GetLocalTime(&LocalTime);
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��
//--------------------------------------------------------------------------
ARMENIACA_API void ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime(SYSTEMTIME* pLocalTime);

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Year()
// @Purpose: Armeniaca��ȡϵͳʱ��(���)
// @Since: v0.04a
// @Para: None
// @Return: WORD wYear	//ʱ��:���
// @Sample: wYear = Armeniaca_Time_GetLocalTime_Year();
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��(���)
//--------------------------------------------------------------------------
ARMENIACA_API WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Year();

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Month()
// @Purpose: Armeniaca��ȡϵͳʱ��(�·�)
// @Since: v0.04a
// @Para: None
// @Return: WORD wMonth	//ʱ��:�·�
// @Sample: wMonth = Armeniaca_Time_GetLocalTime_Month();
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��(�·�)
//--------------------------------------------------------------------------
ARMENIACA_API WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Month();

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Day()
// @Purpose: Armeniaca��ȡϵͳʱ��(����)
// @Since: v0.04a
// @Para: None
// @Return: WORD wDay	//ʱ��:����
// @Sample: wDay = Armeniaca_Time_GetLocalTime_Day();
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��(����)
//--------------------------------------------------------------------------
ARMENIACA_API WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Day();

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Hour()
// @Purpose: Armeniaca��ȡϵͳʱ��(Сʱ)
// @Since: v0.04a
// @Para: None
// @Return: WORD wHour	//ʱ��:Сʱ
// @Sample: wHour = Armeniaca_Time_GetLocalTime_Hour();
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��(Сʱ)
//--------------------------------------------------------------------------
ARMENIACA_API WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Hour();

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Minute()
// @Purpose: Armeniaca��ȡϵͳʱ��(����)
// @Since: v0.04a
// @Para: None
// @Return: WORD wMinute	//ʱ��:����
// @Sample: wMinute = Armeniaca_Time_GetLocalTime_Minute();
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��(����)
//--------------------------------------------------------------------------
ARMENIACA_API WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Minute();

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Second()
// @Purpose: Armeniaca��ȡϵͳʱ��(��)
// @Since: v0.04a
// @Para: None
// @Return: WORD wSecond	//ʱ��:��
// @Sample: wSecond = Armeniaca_Time_GetLocalTime_Second();
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��(��)
//--------------------------------------------------------------------------
ARMENIACA_API WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Second();

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �����ļ����(Config File)<ini>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_GetKeyValue_String()
// @Purpose: Armeniaca��ȡ�����ļ��ؼ���ֵ(�ַ�����)
// @Since: v0.05a
// @Para: const char* szArrFile			// �����ļ��ļ�·��<in>(eg: D:\\LiveConfig.ini)
// @Para: const char* szArrSection		// �����ļ��ؼ�������<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// �����ļ��ؼ�������<in>(eg: LiveCoreMode=0)
// @Para: const char* szArrDefault		// �����ļ�ȱʡֵ<in>(eg: 0)
// @Para: char* szArrValue				// �����ļ��ؼ���ֵ�����ַ<out>
// @Para: DWORD dwSize					// �����ļ��ؼ���ֵ���鳤��<in>
// @Return: BOOL bRet					// ����ֵ: (TRUE: �ɹ� FALSE: ʧ��)
// @Sample: bRet = Armeniaca_Config_GetKeyValue_String("D:\\LiveConfig.ini", "LIVECOREMODE", "LiveCoreMode", "0", chArr, MAX_PATH);
// @Describe: ��ȡ�����ļ�(INI)�ؼ���ֵ(�ַ�����)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_GetKeyValue_String(const char* szArrFile, const char* szArrSection, const char* szArrKey, const char* szArrDefault, char* szArrValue, DWORD dwSize);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_GetKeyValue_Int()
// @Purpose: Armeniaca��ȡ�����ļ��ؼ���ֵ(ֵ����)
// @Since: v0.05a
// @Para: const char* szArrFile			// �����ļ��ļ�·��<in>(eg: D:\\LiveConfig.ini)
// @Para: const char* szArrSection		// �����ļ��ؼ�������<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// �����ļ��ؼ�������<in>(eg: LiveCoreMode=0)
// @Para: const char* szArrDefault		// �����ļ�ȱʡֵ<in>(eg: 0)
// @Para: int* pValue					// �����ļ��ؼ���ֵ<out>
// @Return: BOOL bRet					// ����ֵ: (TRUE: �ɹ� FALSE: ʧ��)
// @Sample: bRet = Armeniaca_Config_GetKeyValue_Int("D:\\LiveConfig.ini", "LIVECOREMODE", "LiveCoreMode", "0", &dwValue);
// @Describe: ��ȡ�����ļ�(INI)�ؼ���ֵ(ֵ����)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_GetKeyValue_Int(const char* szArrFile, const char* szArrSection, const char* szArrKey, const char* szArrDefault, int* pValue);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_SetKeyValue_String()
// @Purpose: Armeniaca���������ļ��ؼ���ֵ(�ַ�����)
// @Since: v0.05a
// @Para: const char* szArrFile			// �����ļ��ļ�·��<in>(eg: D:\\LiveConfig.ini)
// @Para: const char* szArrSection		// �����ļ��ؼ�������<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// �����ļ��ؼ�������<in>(eg: LiveCoreMode=0)
// @Para: const char* szArrValue		// �����ļ��ؼ���ֵ<in>
// @Return: BOOL bRet					// ����ֵ: (TRUE: �ɹ� FALSE: ʧ��)
// @Sample: bRet = Armeniaca_Config_SetKeyValue_String("D:\\LiveConfig.ini", "LIVECOREMODE", "LiveCoreMode", "0");
// @Describe: ���������ļ�(INI)�ؼ���ֵ(�ַ�����)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_SetKeyValue_String(const char* szArrFile, const char* szArrSection, const char* szArrKey, const char* szArrValue);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_SetKeyValue_Int()
// @Purpose: Armeniaca���������ļ��ؼ���ֵ(ֵ����)
// @Since: v0.05a
// @Para: const char* szArrFile			// �����ļ��ļ�·��<in>(eg: D:\\LiveConfig.ini)
// @Para: const char* szArrSection		// �����ļ��ؼ�������<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// �����ļ��ؼ�������<in>(eg: LiveCoreMode=0)
// @Para: int nValue					// �����ļ��ؼ���ֵ<in>
// @Return: BOOL bRet					// ����ֵ: (TRUE: �ɹ� FALSE: ʧ��)
// @Sample: bRet = Armeniaca_Config_SetKeyValue_String("D:\\LiveConfig.ini", "LIVECORESHOWMODE", "LiveCoreShowFontSize", 20);
// @Describe: ���������ļ�(INI)�ؼ���ֵ(ֵ����)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_SetKeyValue_Int(const char* szArrFile, const char* szArrSection, const char* szArrKey, int nValue);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_GetKeyValue_Local_String()
// @Purpose: Armeniaca��ȡ�����ļ��ؼ���ֵ(�ַ�����)
// @Since: v0.05a
// @Para: const char* szArrFileName		// �����ļ��ļ�·��<in>(eg: LiveConfig.ini)		//<<<����ֻ��Ҫд���ļ���(�����exeĿ¼)
// @Para: const char* szArrSection		// �����ļ��ؼ�������<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// �����ļ��ؼ�������<in>(eg: LiveCoreMode=0)
// @Para: const char* szArrDefault		// �����ļ�ȱʡֵ<in>(eg: 0)
// @Para: char* szArrValue				// �����ļ��ؼ���ֵ�����ַ<out>
// @Para: DWORD dwSize					// �����ļ��ؼ���ֵ���鳤��<in>
// @Return: BOOL bRet					// ����ֵ: (TRUE: �ɹ� FALSE: ʧ��)
// @Sample: bRet = Armeniaca_Config_GetKeyValue_Local_String("LiveConfig.ini", "LIVECOREMODE", "LiveCoreMode", "0", chArr, MAX_PATH);
// @Describe: ��ȡ�����ļ�(INI)�ؼ���ֵ(�ַ�����)(����ļ�����)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_GetKeyValue_Local_String(const char* szArrFileName, const char* szArrSection, const char* szArrKey, const char* szArrDefault, char* szArrValue, DWORD dwSize);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_GetKeyValue_Local_Int()
// @Purpose: Armeniaca��ȡ�����ļ��ؼ���ֵ(ֵ����)
// @Since: v0.05a
// @Para: const char* szArrFileName		// �����ļ��ļ�·��<in>(eg: LiveConfig.ini)		//<<<����ֻ��Ҫд���ļ���(�����exeĿ¼)
// @Para: const char* szArrSection		// �����ļ��ؼ�������<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// �����ļ��ؼ�������<in>(eg: LiveCoreMode=0)
// @Para: const char* szArrDefault		// �����ļ�ȱʡֵ<in>(eg: 0)
// @Para: int* pValue					// �����ļ��ؼ���ֵ<out>
// @Return: BOOL bRet					// ����ֵ: (TRUE: �ɹ� FALSE: ʧ��)
// @Sample: bRet = Armeniaca_Config_GetKeyValue_Local_Int("LiveConfig.ini", "LIVECOREMODE", "LiveCoreMode", "0", &dwValue);
// @Describe: ��ȡ�����ļ�(INI)�ؼ���ֵ(ֵ����)(����ļ�����)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_GetKeyValue_Local_Int(const char* szArrFileName, const char* szArrSection, const char* szArrKey, const char* szArrDefault, int* pValue);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_SetKeyValue_Local_String()
// @Purpose: Armeniaca���������ļ��ؼ���ֵ(�ַ�����)
// @Since: v0.05a
// @Para: const char* szArrFileName		// �����ļ��ļ�·��<in>(eg: LiveConfig.ini)		//<<<����ֻ��Ҫд���ļ���(�����exeĿ¼)
// @Para: const char* szArrSection		// �����ļ��ؼ�������<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// �����ļ��ؼ�������<in>(eg: LiveCoreMode=0)
// @Para: const char* szArrValue		// �����ļ��ؼ���ֵ<in>
// @Return: BOOL bRet					// ����ֵ: (TRUE: �ɹ� FALSE: ʧ��)
// @Sample: bRet = Armeniaca_Config_SetKeyValue_Local_String("LiveConfig.ini", "LIVECOREMODE", "LiveCoreMode", "0");
// @Describe: ���������ļ�(INI)�ؼ���ֵ(�ַ�����)(����ļ�����)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_SetKeyValue_Local_String(const char* szArrFileName, const char* szArrSection, const char* szArrKey, const char* szArrValue);

//---------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Armeniaca_Config_SetKeyValue_Local_Int()
// @Purpose: Armeniaca���������ļ��ؼ���ֵ(ֵ����)
// @Since: v0.05a
// @Para: const char* szArrFileName		// �����ļ��ļ�·��<in>(eg: LiveConfig.ini)		//<<<����ֻ��Ҫд���ļ���(�����exeĿ¼)
// @Para: const char* szArrSection		// �����ļ��ؼ�������<in>(eg: [LIVECOREMODE])
// @Para: const char* szArrKey			// �����ļ��ؼ�������<in>(eg: LiveCoreMode=0)
// @Para: int nValue					// �����ļ��ؼ���ֵ<in>
// @Return: BOOL bRet					// ����ֵ: (TRUE: �ɹ� FALSE: ʧ��)
// @Sample: bRet = Armeniaca_Config_SetKeyValue_String("LiveConfig.ini", "LIVECORESHOWMODE", "LiveCoreShowFontSize", 20);
// @Describe: ���������ļ�(INI)�ؼ���ֵ(ֵ����)(����ļ�����)
//----------------------------------------------------------------------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_SetKeyValue_Local_Int(const char* szArrFileName, const char* szArrSection, const char* szArrKey, int nValue);


#endif // !__ARMENIACA_H_

