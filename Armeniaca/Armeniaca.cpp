/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		Armeniaca.cpp
* @brief	This Program is Armeniaca C-Style Dynamic Link Library Project.
* @author	alopex
* @version	v0.05a
* @date		2018-4-20	v0.01a	alopex	Create Project.
* @date		2018-4-21	v0.02a	alopex	Add Process Function.
* @date		2018-4-26	v0.03a	alopex	Change Call Style From __stdcall to __cdecl.
* @date		2018-4-26	v0.04a	alopex	Add FilePath&Time Function.
* @date		2018-5-16	v0.05a	alopex	Add Read&Write INI File Function.
*/
#include "Armeniaca.h"

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
// @Sample: bRet = Armeniaca_Process_IsProcessExistA("LiveCore.exe");
// @Describe: �������Ƿ����(����)
//------------------------------------------------------------------
BOOL ARMENIACA_CALLMETHOD Armeniaca_Process_IsProcessExistA(const char* strProcessName)
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
// @Function:	 Armeniaca_Process_IsProcessExistW()
// @Purpose: Armeniaca�������Ƿ����
// @Since: v0.01a
// @Para: const wchar_t* strProcessName<��������>(Unicode)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_Process_IsProcessExistW(L"LiveCore.exe");
// @Describe: �������Ƿ����(����)(TRUE:���̴���, FALSE:���̲�����)
//------------------------------------------------------------------
BOOL ARMENIACA_CALLMETHOD Armeniaca_Process_IsProcessExistW(const wchar_t* strProcessName)
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
// @Function:	 Armeniaca_Process_StartProcessA()
// @Purpose: Armeniaca��������(��·��Ŀ¼��)
// @Since: v0.01a
// @Para: const char* strProcessName<��������>(ASCII)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_Process_StartProcessA("LiveCore.exe");
// @Describe: ��������(����)(TRUE:�������̳ɹ�, FALSE:��������ʧ��)
//------------------------------------------------------------------
BOOL ARMENIACA_CALLMETHOD Armeniaca_Process_StartProcessA(const char* strProcessName)
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
// @Function:	 Armeniaca_Process_StartProcessW()
// @Purpose: Armeniaca��������(��·��Ŀ¼��)
// @Since: v0.01a
// @Para: const wchar_t* strProcessName<��������>(Unicode)
// @Return: TRUE: �ɹ� FALSE: ʧ��
// @Sample: bRet = Armeniaca_Process_StartProcessW(L"LiveCore.exe");
// @Describe: ��������(����)(TRUE:�������̳ɹ�, FALSE:��������ʧ��)
//------------------------------------------------------------------
BOOL ARMENIACA_CALLMETHOD Armeniaca_Process_StartProcessW(const wchar_t* strProcessName)
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
BOOL ARMENIACA_CALLMETHOD Armeniaca_Convert_A2W_Safe(const char* szArr, const wchar_t* wszArr, int nSize)
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
	memcpy_s((void*)wszArr, nSize * sizeof(wchar_t), pwszArr, (nSrcSize + 1) * sizeof(wchar_t));

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_Convert_W2A_Safe(const wchar_t* wszArr, const char* szArr, int nSize)
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
	memcpy_s((void*)szArr, nSize * sizeof(char), pszArr, (nSrcSize + 1) * sizeof(char));

	delete[] pszArr;
	pszArr = NULL;

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_A2W_UnSafe()(��Ҫ�ͷ�)
// @Purpose: Armeniaca�ַ�ת��(charתwchar_t)
// @Since: v0.01a
// @Para: const char* szArr			// Դ�ַ�����
// @Para: wchar_t** ppwszArr		// Ŀ���ַ�����(ָ�봫��NULL)
// @Return: None
// @Sample: Armeniaca_Convert_A2W_UnSafe(A, W);
// @Describe: �ַ�ת��:ASCIIת��Unicode(����Ŀ������NULLָ��,��Ҫ�ͷ��ڴ�!)
//------------------------------------------------------------------
void ARMENIACA_CALLMETHOD Armeniaca_Convert_A2W_UnSafe(const char* szArr, wchar_t** ppwszArr)
{
	int nSize = 0;

	nSize = ::MultiByteToWideChar(CP_ACP, 0, szArr, -1, NULL, NULL);
	*ppwszArr = new wchar_t[nSize + 1];
	memset(*ppwszArr, 0, (nSize + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, szArr, -1, (LPWSTR)(*ppwszArr), nSize);

	return;
}

//------------------------------------------------------------------
// @Function:	 Armeniaca_Convert_W2A_UnSafe()(��Ҫ�ͷ�)
// @Purpose: Armeniaca�ַ�ת��(wchar_tתchar)
// @Since: v0.01a
// @Para: const wchar_t* wszArr		// Դ�ַ�����
// @Para: char** ppszArr			// Ŀ���ַ�����(���鴫��)
// @Return: None
// @Sample: Armeniaca_Convert_W2A_UnSafe(W, A);
// @Describe: �ַ�ת��:Unicodeת��ASCII(����Ŀ������NULLָ��,��Ҫ�ͷ��ڴ�!)
//------------------------------------------------------------------
void ARMENIACA_CALLMETHOD Armeniaca_Convert_W2A_UnSafe(const wchar_t* wszArr, char** ppszArr)
{
	int nSize = 0;

	nSize = ::WideCharToMultiByte(CP_ACP, 0, wszArr, -1, NULL, 0, NULL, NULL);
	*ppszArr = new char[nSize + 1];
	memset(*ppszArr, 0, (nSize + 1) * sizeof(char));
	::WideCharToMultiByte(CP_ACP, 0, wszArr, -1, *ppszArr, nSize, NULL, NULL);

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
wchar_t* ARMENIACA_CALLMETHOD Armeniaca_Convert_A2W_UnSafe2(const char* szArr)
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
char* ARMENIACA_CALLMETHOD Armeniaca_Convert_W2A_UnSafe2(const wchar_t* wszArr)
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
BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetModulePathA(const char* szArr, int nSize)
{
	char chArr[MAX_PATH] = { 0 };
	char* pTemp = NULL;
	int nArrSize = 0;

	GetModuleFileNameA(NULL, chArr, MAX_PATH);
	nArrSize = strlen(chArr);
	if (nSize < nArrSize + 1)
	{
		return FALSE;
	}

	memset((void*)szArr, 0, nSize * sizeof(char));
	memcpy_s((void*)szArr, nSize * sizeof(char), chArr, (nArrSize + 1) * sizeof(char));

	return TRUE;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetModulePathW(const wchar_t* wszArr, int nSize)
{
	char chArr[MAX_PATH] = { 0 };
	char* pTemp = NULL;
	int nArrSize = 0;

	GetModuleFileNameA(NULL, chArr, MAX_PATH);

	BOOL bReturn = FALSE;
	bReturn = Armeniaca_Convert_A2W_Safe(chArr, wszArr, nSize);
	if (!bReturn)
	{
		return FALSE;
	}

	return TRUE;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetLocalPathA(const char* szArr, int nSize)
{
	char chArr[MAX_PATH] = { 0 };
	char* pTemp = NULL;
	int nArrSize = 0;

	GetModuleFileNameA(NULL, chArr, MAX_PATH);
	pTemp = strrchr(chArr, '\\');
	if (pTemp != NULL)
	{
		*pTemp = '\0';
	}

	nArrSize = strlen(chArr);
	if (nSize < nArrSize + 1)
	{
		return FALSE;
	}

	memset((void*)szArr, 0, nSize * sizeof(char));
	memcpy_s((void*)szArr, nSize * sizeof(char), chArr, (nArrSize + 1) * sizeof(char));

	return TRUE;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetLocalPathW(const wchar_t* wszArr, int nSize)
{
	char chArr[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	GetModuleFileNameA(NULL, chArr, MAX_PATH);
	pTemp = strrchr(chArr, '\\');
	if (pTemp != NULL)
	{
		*pTemp = '\0';
	}

	BOOL bReturn = FALSE;
	bReturn = Armeniaca_Convert_A2W_Safe(chArr, wszArr, nSize);
	if (!bReturn)
	{
		return FALSE;
	}

	return TRUE;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetParentPathA(const char* szArr, int nSize, int nDeep)
{
	char chArr[MAX_PATH] = { 0 };
	int nArrSize = 0;

	if (nDeep <= 0)
	{
		return FALSE;
	}

	GetModuleFileNameA(NULL, chArr, MAX_PATH);
	for (int i = 0; i < nDeep; ++i)
	{
		char* pTemp = NULL;
		pTemp = strrchr(chArr, '\\');
		if (pTemp != NULL)
		{
			*pTemp = '\0';
		}
	}

	nArrSize = strlen(chArr);
	if (nSize < nArrSize + 1)
	{
		return FALSE;
	}

	memset((void*)szArr, 0, nSize * sizeof(char));
	memcpy_s((void*)szArr, nSize * sizeof(char), chArr, (nArrSize + 1) * sizeof(char));

	return TRUE;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_FilePath_GetParentPathW(const wchar_t* wszArr, int nSize, int nDeep)
{
	char chArr[MAX_PATH] = { 0 };

	if (nDeep <= 0)
	{
		return FALSE;
	}

	GetModuleFileNameA(NULL, chArr, MAX_PATH);
	for (int i = 0; i < nDeep; ++i)
	{
		char* pTemp = NULL;
		pTemp = strrchr(chArr, '\\');
		if (pTemp != NULL)
		{
			*pTemp = '\0';
		}
	}

	BOOL bReturn = FALSE;
	bReturn = Armeniaca_Convert_A2W_Safe(chArr, wszArr, nSize);
	if (!bReturn)
	{
		return FALSE;
	}

	return TRUE;
}

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
void ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime(SYSTEMTIME* pLocalTime)
{
	GetLocalTime(pLocalTime);
}

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Year()
// @Purpose: Armeniaca��ȡϵͳʱ��(���)
// @Since: v0.04a
// @Para: None
// @Return: WORD wYear	//ʱ��:���
// @Sample: wYear = Armeniaca_Time_GetLocalTime_Year();
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��(���)
//--------------------------------------------------------------------------
WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Year()
{
	SYSTEMTIME syTime;

	GetLocalTime(&syTime);

	return syTime.wYear;
}

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Month()
// @Purpose: Armeniaca��ȡϵͳʱ��(�·�)
// @Since: v0.04a
// @Para: None
// @Return: WORD wMonth	//ʱ��:�·�
// @Sample: wMonth = Armeniaca_Time_GetLocalTime_Month();
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��(�·�)
//--------------------------------------------------------------------------
WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Month()
{
	SYSTEMTIME syTime;

	GetLocalTime(&syTime);

	return syTime.wMonth;
}

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Day()
// @Purpose: Armeniaca��ȡϵͳʱ��(����)
// @Since: v0.04a
// @Para: None
// @Return: WORD wDay	//ʱ��:����
// @Sample: wDay = Armeniaca_Time_GetLocalTime_Day();
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��(����)
//--------------------------------------------------------------------------
WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Day()
{
	SYSTEMTIME syTime;

	GetLocalTime(&syTime);

	return syTime.wDay;
}

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Hour()
// @Purpose: Armeniaca��ȡϵͳʱ��(Сʱ)
// @Since: v0.04a
// @Para: None
// @Return: WORD wHour	//ʱ��:Сʱ
// @Sample: wHour = Armeniaca_Time_GetLocalTime_Hour();
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��(Сʱ)
//--------------------------------------------------------------------------
WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Hour()
{
	SYSTEMTIME syTime;

	GetLocalTime(&syTime);

	return syTime.wHour;
}

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Minute()
// @Purpose: Armeniaca��ȡϵͳʱ��(����)
// @Since: v0.04a
// @Para: None
// @Return: WORD wMinute	//ʱ��:����
// @Sample: wMinute = Armeniaca_Time_GetLocalTime_Minute();
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��(����)
//--------------------------------------------------------------------------
WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Minute()
{
	SYSTEMTIME syTime;

	GetLocalTime(&syTime);

	return syTime.wMinute;
}

//--------------------------------------------------------------------------
// @Function:	 Armeniaca_Time_GetLocalTime_Second()
// @Purpose: Armeniaca��ȡϵͳʱ��(��)
// @Since: v0.04a
// @Para: None
// @Return: WORD wSecond	//ʱ��:��
// @Sample: wSecond = Armeniaca_Time_GetLocalTime_Second();
// @Describe: ʱ��:��ȡ��ǰϵͳʱ��(��)
//--------------------------------------------------------------------------
WORD ARMENIACA_CALLMETHOD Armeniaca_Time_GetLocalTime_Second()
{
	SYSTEMTIME syTime;

	GetLocalTime(&syTime);

	return syTime.wSecond;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_GetKeyValue_String(const char* szArrFile, const char* szArrSection, const char* szArrKey, const char* szArrDefault, char* szArrValue, DWORD dwSize)
{
	DWORD dwCount = 0;
	char chArrValue[MAX_PATH] = { 0 };

	memset(chArrValue, 0, MAX_PATH);
	dwCount = GetPrivateProfileStringA(szArrSection, szArrKey, szArrDefault, szArrValue, dwSize, szArrFile);
	if (dwCount <= 0 || dwCount > dwSize)
	{
		return FALSE;
	}

	memcpy_s(szArrValue, dwSize, chArrValue, dwCount);

	return TRUE;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_GetKeyValue_Int(const char* szArrFile, const char* szArrSection, const char* szArrKey, const char* szArrDefault, int* pValue)
{
	DWORD dwCount = 0;
	char chArrValue[MAX_PATH] = { 0 };

	memset(chArrValue, 0, MAX_PATH);
	dwCount = GetPrivateProfileStringA(szArrSection, szArrKey, szArrDefault, chArrValue, MAX_PATH, szArrFile);
	if (dwCount <= 0)
	{
		return FALSE;
	}

	*pValue = atoi(chArrValue);

	return TRUE;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_SetKeyValue_String(const char* szArrFile, const char* szArrSection, const char* szArrKey, const char* szArrValue)
{
	BOOL bRet = FALSE;

	bRet = WritePrivateProfileStringA(szArrSection, szArrKey, szArrValue, szArrFile);

	return bRet;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_SetKeyValue_Int(const char* szArrFile, const char* szArrSection, const char* szArrKey, int nValue)
{
	BOOL bRet = FALSE;
	char chArrValue[MAX_PATH] = { 0 };

	memset(chArrValue, 0, MAX_PATH);
	sprintf_s(chArrValue, MAX_PATH, "%d", nValue);

	bRet = WritePrivateProfileStringA(szArrSection, szArrKey, chArrValue, szArrFile);

	return bRet;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_GetKeyValue_Local_String(const char* szArrFileName, const char* szArrSection, const char* szArrKey, const char* szArrDefault, char* szArrValue, DWORD dwSize)
{
	BOOL bRet = FALSE;
	DWORD dwCount = 0;
	char chArrFile[MAX_PATH] = { 0 };
	char chArrValue[MAX_PATH] = { 0 };

	memset(chArrFile, 0, MAX_PATH);
	bRet = Armeniaca_FilePath_GetLocalPathA(chArrFile, MAX_PATH);
	if (!bRet)
	{
		return FALSE;
	}

	strcat_s(chArrFile, "\\");
	strcat_s(chArrFile, szArrFileName);

	memset(chArrValue, 0, MAX_PATH);
	dwCount = GetPrivateProfileStringA(szArrSection, szArrKey, szArrDefault, szArrValue, dwSize, chArrFile);
	if (dwCount <= 0 || dwCount > dwSize)
	{
		return FALSE;
	}

	memcpy_s(szArrValue, dwSize, chArrValue, dwCount);

	return TRUE;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_GetKeyValue_Local_Int(const char* szArrFileName, const char* szArrSection, const char* szArrKey, const char* szArrDefault, int* pValue)
{
	BOOL bRet = FALSE;
	DWORD dwCount = 0;
	char chArrFile[MAX_PATH] = { 0 };
	char chArrValue[MAX_PATH] = { 0 };

	memset(chArrFile, 0, MAX_PATH);
	bRet = Armeniaca_FilePath_GetLocalPathA(chArrFile, MAX_PATH);
	if (!bRet)
	{
		return FALSE;
	}

	strcat_s(chArrFile, "\\");
	strcat_s(chArrFile, szArrFileName);

	memset(chArrValue, 0, MAX_PATH);
	dwCount = GetPrivateProfileStringA(szArrSection, szArrKey, szArrDefault, chArrValue, MAX_PATH, chArrFile);
	if (dwCount <= 0)
	{
		return FALSE;
	}

	*pValue = atoi(chArrValue);

	return TRUE;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_SetKeyValue_Local_String(const char* szArrFileName, const char* szArrSection, const char* szArrKey, const char* szArrValue)
{
	BOOL bRet = FALSE;
	char chArrFile[MAX_PATH] = { 0 };

	memset(chArrFile, 0, MAX_PATH);
	bRet = Armeniaca_FilePath_GetLocalPathA(chArrFile, MAX_PATH);
	if (!bRet)
	{
		return FALSE;
	}

	strcat_s(chArrFile, "\\");
	strcat_s(chArrFile, szArrFileName);

	bRet = WritePrivateProfileStringA(szArrSection, szArrKey, szArrValue, chArrFile);

	return bRet;
}

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
BOOL ARMENIACA_CALLMETHOD Armeniaca_Config_SetKeyValue_Local_Int(const char* szArrFileName, const char* szArrSection, const char* szArrKey, int nValue)
{
	BOOL bRet = FALSE;
	char chArrFile[MAX_PATH] = { 0 };
	char chArrValue[MAX_PATH] = { 0 };

	memset(chArrFile, 0, MAX_PATH);
	bRet = Armeniaca_FilePath_GetLocalPathA(chArrFile, MAX_PATH);
	if (!bRet)
	{
		return FALSE;
	}

	strcat_s(chArrFile, "\\");
	strcat_s(chArrFile, szArrFileName);

	memset(chArrValue, 0, MAX_PATH);
	sprintf_s(chArrValue, MAX_PATH, "%d", nValue);

	bRet = WritePrivateProfileStringA(szArrSection, szArrKey, chArrValue, chArrFile);

	return bRet;
}