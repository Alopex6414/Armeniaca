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

//������������������Interface����������������������

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �������(Process)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//------------------------------------------------------------------
// @Function:	 Armeniaca_IsProcessExistA()
// @Purpose: Armeniaca�������Ƿ����
// @Since: v0.01a
// @Para: const char* strProcessName<��������>(ASCII)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_IsProcessExistA("LiveCore.exe");
// @Describe: �������Ƿ����(����)(TRUE:���̴���, FALSE:���̲�����)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMODE Armeniaca_IsProcessExistA(const char* strProcessName);

//------------------------------------------------------------------
// @Function:	 Armeniaca_IsProcessExistW()
// @Purpose: Armeniaca�������Ƿ����
// @Since: v0.01a
// @Para: const wchar_t* strProcessName<��������>(Unicode)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_IsProcessExistW(L"LiveCore.exe");
// @Describe: �������Ƿ����(����)(TRUE:���̴���, FALSE:���̲�����)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMODE Armeniaca_IsProcessExistW(const wchar_t* strProcessName);

//------------------------------------------------------------------
// @Function:	 Armeniaca_StartProcessA()
// @Purpose: Armeniaca��������(��·��Ŀ¼��)
// @Since: v0.01a
// @Para: const char* strProcessName<��������>(ASCII)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_StartProcessA("LiveCore.exe");
// @Describe: ��������(����)(TRUE:�������̳ɹ�, FALSE:��������ʧ��)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMODE Armeniaca_StartProcessA(const char* strProcessName);

//------------------------------------------------------------------
// @Function:	 Armeniaca_StartProcessW()
// @Purpose: Armeniaca��������(��·��Ŀ¼��)
// @Since: v0.01a
// @Para: const wchar_t* strProcessName<��������>(Unicode)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_StartProcessW(L"LiveCore.exe");
// @Describe: ��������(����)(TRUE:�������̳ɹ�, FALSE:��������ʧ��)
//------------------------------------------------------------------
ARMENIACA_API BOOL ARMENIACA_CALLMODE Armeniaca_StartProcessW(const wchar_t* strProcessName);

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
ARMENIACA_API BOOL ARMENIACA_CALLMODE Armeniaca_Convert_A2W_Safe(const char* szArr, const wchar_t* wszArr, int nSize);

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
ARMENIACA_API BOOL ARMENIACA_CALLMODE Armeniaca_Convert_W2A_Safe(const wchar_t* wszArr, const char* szArr, int nSize);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_A2W_UnSafe()(��Ҫ�ͷ�)
// @Purpose: Armeniaca�ַ�ת��(charתwchar_t)
// @Since: v0.01a
// @Para: const char* szArr			// Դ�ַ�����
// @Para: wchar_t* pwszArr			// Ŀ���ַ�����(ָ�봫��NULL)
// @Return: None
// @Sample: Armeniaca_Convert_A2W_UnSafe(A, W);
// @Describe: �ַ�ת��:ASCIIת��Unicode(����Ŀ������NULLָ��,��Ҫ�ͷ��ڴ�!)
//------------------------------------------------------------------
ARMENIACA_API void ARMENIACA_CALLMODE Armeniaca_Convert_A2W_UnSafe(const char* szArr, wchar_t* pwszArr);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_W2A_UnSafe()(��Ҫ�ͷ�)
// @Purpose: Armeniaca�ַ�ת��(wchar_tתchar)
// @Since: v0.01a
// @Para: const wchar_t* wszArr		// Դ�ַ�����
// @Para: char* pszArr				// Ŀ���ַ�����(���鴫��)
// @Return: None
// @Sample: Armeniaca_Convert_W2A_UnSafe(W, A);
// @Describe: �ַ�ת��:Unicodeת��ASCII(����Ŀ������NULLָ��,��Ҫ�ͷ��ڴ�!)
//------------------------------------------------------------------
ARMENIACA_API void ARMENIACA_CALLMODE Armeniaca_Convert_W2A_UnSafe(const wchar_t* wszArr, char* pszArr);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_A2W_UnSafe2()(��Ҫ�ͷ�)
// @Purpose: Armeniaca�ַ�ת��(charתwchar_t)
// @Since: v0.02a
// @Para: const char* szArr			// Դ�ַ�����
// @Return: wchar_t* wszArr			// Ŀ���ַ�����(ָ�뷵��)
// @Sample: W = Armeniaca_Convert_A2W_UnSafe2(A);
// @Describe: �ַ�ת��:ASCIIת��Unicode(����Ŀ������NULLָ��,��Ҫ�ͷ��ڴ�!)
//------------------------------------------------------------------
ARMENIACA_API wchar_t* ARMENIACA_CALLMODE Armeniaca_Convert_A2W_UnSafe2(const char* szArr);

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_W2A_UnSafe2()(��Ҫ�ͷ�)
// @Purpose: Armeniaca�ַ�ת��(wchar_tתchar)
// @Since: v0.02a
// @Para: const wchar_t* wszArr		// Դ�ַ�����
// @Return: char* szArr				// Ŀ���ַ�����(ָ�뷵��)
// @Sample: A = Armeniaca_Convert_W2A_UnSafe2(W);
//------------------------------------------------------------------
ARMENIACA_API char* ARMENIACA_CALLMODE Armeniaca_Convert_W2A_UnSafe2(const wchar_t* wszArr);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �ļ�·��(FilePath)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


#endif // !__ARMENIACA_H_

