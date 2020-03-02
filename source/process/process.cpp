#include <windows.h>
#include <tlhelp32.h>

#include "utils/tchar/tstring.hpp"

namespace jhack
{
	HANDLE	getProcessHandleByName(DWORD dwDesiredAccess, Tstring<> name)
	{
		PROCESSENTRY32	pInfo;
		HANDLE			pHandle;
		HANDLE			hSnap;

		hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnap == INVALID_HANDLE_VALUE)
		{
//			std::cerr << "Error on calling CreateToolhelp32Snapshot().\n";
			return hSnap;
		}

		pInfo.dwSize = sizeof(PROCESSENTRY32);
		pHandle = INVALID_HANDLE_VALUE;
		for (BOOL next = Process32First(hSnap, &pInfo); next; next = Process32Next(hSnap, &pInfo))
		{
			if (_tcsstr(pInfo.szExeFile, name.data()) != NULL)
			{
				pHandle = OpenProcess(dwDesiredAccess, FALSE, pInfo.th32ProcessID);
				if (pHandle != NULL)
					break ;
			}
		}
		CloseHandle(hSnap);
		return pHandle;
	}
}