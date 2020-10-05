#include <Windows.h>
#include "getLastError.hpp"
#include <iostream>
namespace jhack
{
	std::string		getLastError(void)
	{
		char		ErrorBuf[512];
		std::string	ErrorStr;

		if (!FormatMessageA(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				GetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				ErrorBuf,
				sizeof(ErrorBuf),
				NULL))
			return ErrorStr;

		ErrorStr = ErrorBuf;
		if (ErrorStr.back() == '\n')
			ErrorStr.pop_back();
		return ErrorStr;
	}
}