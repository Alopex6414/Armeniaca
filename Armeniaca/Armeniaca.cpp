/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		Armeniaca.cpp
* @brief	This Program is Armeniaca C-Style Dynamic Link Library Project.
* @author	alopex
* @version	v0.01a
* @date		2018-4-20	v0.01a	alopex	Create Project.
*/
#include "Armeniaca.h"

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
// @Describe: �������Ƿ����(����)
//------------------------------------------------------------------
BOOL ARMENIACA_CALLMODE Armeniaca_IsProcessExistA(const char* strProcessName)
{
	BOOL bRet = FALSE;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	int nSize = 0;
	wchar_t* pstrProcessName = NULL;

	nSize = ::MultiByteToWideChar(CP_ACP, 0, strProcessName, -1, NULL, NULL);
	pstrProcessName = new wchar_t[nSize + 1];
	memset(pstrProcessName, 0, (nSize + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, strProcessName, -1, (LPWSTR)pstrProcessName, nSize);

	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcessSnap, &pe32))
	{
		do {
			if (_wcsicmp(pe32.szExeFile, pstrProcessName) == 0)
			{
				bRet = TRUE;
				break;
			}
		} while (Process32Next(hProcessSnap, &pe32));
	}
	else {
		bRet = FALSE;
	}
	CloseHandle(hProcessSnap);

	delete[] pstrProcessName;
	pstrProcessName = NULL;

	return bRet;
}

//------------------------------------------------------------------
// @Function:	 Armeniaca_IsProcessExistW()
// @Purpose: Armeniaca�������Ƿ����
// @Since: v0.01a
// @Para: const wchar_t* strProcessName<��������>(Unicode)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_IsProcessExistW(L"LiveCore.exe");
// @Describe: �������Ƿ����(����)(TRUE:���̴���, FALSE:���̲�����)
//------------------------------------------------------------------
BOOL ARMENIACA_CALLMODE Armeniaca_IsProcessExistW(const wchar_t* strProcessName)
{
	BOOL bRet = FALSE;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcessSnap, &pe32))
	{
		do {
			if (_wcsicmp(pe32.szExeFile, strProcessName) == 0)
			{
				bRet = TRUE;
				break;
			}
		} while (Process32Next(hProcessSnap, &pe32));
	}
	else {
		bRet = FALSE;
	}
	CloseHandle(hProcessSnap);

	return bRet;
}

//------------------------------------------------------------------
// @Function:	 Armeniaca_StartProcessA()
// @Purpose: Armeniaca��������(��·��Ŀ¼��)
// @Since: v0.01a
// @Para: const char* strProcessName<��������>(ASCII)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_StartProcessA("LiveCore.exe");
// @Describe: ��������(����)(TRUE:�������̳ɹ�, FALSE:��������ʧ��)
//------------------------------------------------------------------
BOOL ARMENIACA_CALLMODE Armeniaca_StartProcessA(const char* strProcessName)
{
	BOOL bRet = FALSE;

	STARTUPINFOA si = { 0 };
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(STARTUPINFOA);
	GetStartupInfoA(&si);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi = { 0 };
	ZeroMemory(&pi, sizeof(pi));

	char chProcessPath[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	GetModuleFileNameA(NULL, chProcessPath, MAX_PATH);
	pTemp = strrchr(chProcessPath, '\\');
	if (pTemp) *pTemp = '\0';
	strcat_s(chProcessPath, "\\");
	strcat_s(chProcessPath, strProcessName);

	bRet = CreateProcessA(chProcessPath, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	if (bRet)
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	return bRet;
}

//------------------------------------------------------------------
// @Function:	 Armeniaca_StartProcessW()
// @Purpose: Armeniaca��������(��·��Ŀ¼��)
// @Since: v0.01a
// @Para: const wchar_t* strProcessName<��������>(Unicode)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_StartProcessW(L"LiveCore.exe");
// @Describe: ��������(����)(TRUE:�������̳ɹ�, FALSE:��������ʧ��)
//------------------------------------------------------------------
BOOL ARMENIACA_CALLMODE Armeniaca_StartProcessW(const wchar_t* strProcessName)
{
	BOOL bRet = FALSE;

	int nSize = 0;
	char* pstrProcessName = NULL;

	nSize = ::WideCharToMultiByte(CP_ACP, 0, strProcessName, -1, NULL, 0, NULL, NULL);
	pstrProcessName = new char[nSize + 1];
	memset(pstrProcessName, 0, (nSize + 1) * sizeof(char));
	::WideCharToMultiByte(CP_ACP, 0, strProcessName, -1, pstrProcessName, nSize, NULL, NULL);


	STARTUPINFOA si = { 0 };
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(STARTUPINFOA);
	GetStartupInfoA(&si);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi = { 0 };
	ZeroMemory(&pi, sizeof(pi));

	char chProcessPath[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	GetModuleFileNameA(NULL, chProcessPath, MAX_PATH);
	pTemp = strrchr(chProcessPath, '\\');
	if (pTemp) *pTemp = '\0';
	strcat_s(chProcessPath, "\\");
	strcat_s(chProcessPath, pstrProcessName);

	bRet = CreateProcessA(chProcessPath, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	if (bRet)
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	delete[] pstrProcessName;
	pstrProcessName = NULL;

	return bRet;
}

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
BOOL ARMENIACA_CALLMODE Armeniaca_Convert_A2W_Safe(const char* szArr, const wchar_t* wszArr, int nSize)
{
	int nSrcSize = 0;
	wchar_t* pwszArr = NULL;

	nSrcSize = ::MultiByteToWideChar(CP_ACP, 0, szArr, -1, NULL, NULL);
	if (nSize < nSrcSize + 1)
	{
		return FALSE;
	}

	pwszArr = new wchar_t[nSrcSize + 1];
	memset(pwszArr, 0, (nSrcSize + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, szArr, -1, (LPWSTR)pwszArr, nSrcSize);

	memset((void*)wszArr, 0, nSize * sizeof(wchar_t));
	memcpy_s((void*)wszArr, nSize * sizeof(wchar_t), pwszArr, (nSrcSize + 1) * sizeof(char));

	delete[] pwszArr;
	pwszArr = NULL;

	return TRUE;
}

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
BOOL ARMENIACA_CALLMODE Armeniaca_Convert_W2A_Safe(const wchar_t* wszArr, const char* szArr, int nSize)
{
	int nSrcSize = 0;
	char* pszArr = NULL;

	nSrcSize = ::WideCharToMultiByte(CP_ACP, 0, wszArr, -1, NULL, 0, NULL, NULL);
	if (nSize < nSrcSize + 1)
	{
		return FALSE;
	}

	pszArr = new char[nSrcSize + 1];
	memset(pszArr, 0, (nSrcSize + 1) * sizeof(char));
	::WideCharToMultiByte(CP_ACP, 0, wszArr, -1, pszArr, nSrcSize, NULL, NULL);

	memset((void*)szArr, 0, nSize * sizeof(char));
	memcpy_s((void*)szArr, nSize * sizeof(char), pszArr, (nSrcSize + 1) * sizeof(wchar_t));

	delete[] pszArr;
	pszArr = NULL;

	return TRUE;
}

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
void ARMENIACA_CALLMODE Armeniaca_Convert_A2W_UnSafe(const char* szArr, wchar_t* pwszArr)
{
	int nSize = 0;

	nSize = ::MultiByteToWideChar(CP_ACP, 0, szArr, -1, NULL, NULL);
	pwszArr = new wchar_t[nSize + 1];
	memset(pwszArr, 0, (nSize + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, szArr, -1, (LPWSTR)pwszArr, nSize);

	return;
}

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
void ARMENIACA_CALLMODE Armeniaca_Convert_W2A_UnSafe(const wchar_t* wszArr, char* pszArr)
{
	int nSize = 0;

	nSize = ::WideCharToMultiByte(CP_ACP, 0, wszArr, -1, NULL, 0, NULL, NULL);
	pszArr = new char[nSize + 1];
	memset(pszArr, 0, (nSize + 1) * sizeof(char));
	::WideCharToMultiByte(CP_ACP, 0, wszArr, -1, pszArr, nSize, NULL, NULL);

	return;
}

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_A2W_UnSafe2()(��Ҫ�ͷ�)
// @Purpose: Armeniaca�ַ�ת��(charתwchar_t)
// @Since: v0.02a
// @Para: const char* szArr			// Դ�ַ�����
// @Return: wchar_t* wszArr			// Ŀ���ַ�����(ָ�뷵��)
// @Sample: W = Armeniaca_Convert_A2W_UnSafe2(A);
// @Describe: �ַ�ת��:ASCIIת��Unicode(����Ŀ������NULLָ��,��Ҫ�ͷ��ڴ�!)
//------------------------------------------------------------------
wchar_t* ARMENIACA_CALLMODE Armeniaca_Convert_A2W_UnSafe2(const char* szArr)
{
	int nSize = 0;
	wchar_t* pwszArr = NULL;

	nSize = ::MultiByteToWideChar(CP_ACP, 0, szArr, -1, NULL, NULL);
	pwszArr = new wchar_t[nSize + 1];
	memset(pwszArr, 0, (nSize + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, szArr, -1, (LPWSTR)pwszArr, nSize);

	return pwszArr;
}

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_W2A_UnSafe2()(��Ҫ�ͷ�)
// @Purpose: Armeniaca�ַ�ת��(wchar_tתchar)
// @Since: v0.02a
// @Para: const wchar_t* wszArr		// Դ�ַ�����
// @Return: char* szArr				// Ŀ���ַ�����(ָ�뷵��)
// @Sample: A = Armeniaca_Convert_W2A_UnSafe2(W);
//------------------------------------------------------------------
char* ARMENIACA_CALLMODE Armeniaca_Convert_W2A_UnSafe2(const wchar_t* wszArr)
{
	int nSize = 0;
	char* pszArr = NULL;

	nSize = ::WideCharToMultiByte(CP_ACP, 0, wszArr, -1, NULL, 0, NULL, NULL);
	pszArr = new char[nSize + 1];
	memset(pszArr, 0, (nSize + 1) * sizeof(char));
	::WideCharToMultiByte(CP_ACP, 0, wszArr, -1, pszArr, nSize, NULL, NULL);

	return pszArr;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �ļ�·��(FilePath)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

