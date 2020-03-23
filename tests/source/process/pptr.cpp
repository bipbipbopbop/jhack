#include "source/process/pptr.hpp"
#include "jhackTestsConfig.h"
#include <iostream>
#include <cassert>
#include <Windows.h>
#include <errhandlingapi.h>
#include <tchar.h>

using jhack::Pptr;

int		main()
{
	//Hook a lambda on abort to avoid Windows debug dialog
	_CrtSetReportHook([](int reportType, char *message, int *returnValue){
		std::cerr << "[HOOK] Assert failed: " << message << std::endl;
		exit(1);
		return 0;
	});

	{
		HANDLE	aaa = (HANDLE)17;
		Pptr	a{(LPVOID)0x42, aaa};
		Pptr	b = a;
		Pptr	b2 = std::move(b);
		assert(/*b2.processHandle != b.processHandle &&//scalar type -> move is a copy*/ b2.address == a.address);
	}


	//shameless copy of https://docs.microsoft.com/en-us/windows/win32/procthread/creating-processes
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
	std::basic_string<TCHAR>	processPath(DataPath);
	processPath += _T("/deadbeef.exe");

	if (!CreateProcess(NULL, processPath.data(), NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &si, &pi))
	{
		std::cerr << "Error: failed to spawn new process.\n";
		return -1;
	}
	Sleep(200);//By testing, I guess the process is not fully created so we need to wait a bit

	const unsigned int base = 0x14F000;
	Pptr	ptr{(LPVOID)(base + 0xE50), pi.hProcess};
	assert(ptr.read<unsigned int>() == 0xDEADBEEF);


	unsigned int		kek = 0x0;
	ptr.write(&kek, sizeof(kek) / 2);
	assert(ptr.read<unsigned int>() == 0xDEAD0000);


	Pptr	ptr2{(LPVOID)(base + 0xE60), pi.hProcess};
	char	value[5] = "BBBB";
	assert(ptr2[0][0].read<uint32_t>(4) == *reinterpret_cast<uint32_t*>(value));

	return 0;
}