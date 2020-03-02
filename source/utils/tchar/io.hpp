#ifndef UTILS_TCHAR_IO_HPP
#define UTILS_TCHAR_IO_HPP

#include <tchar.h>
#include <iostream>
#include <type_traits>

namespace jhack
{
	constexpr auto &Tcout()
	{
		if constexpr (std::is_same_v<TCHAR, wchar_t>)
			return std::wcout;
		else
			return std::cout;
	}

	constexpr auto &Tcerr()
	{
		if constexpr (std::is_same_v<TCHAR, wchar_t>)
			return std::wcerr;
		else
			return std::cerr;
	}

	constexpr auto &Tcin()
	{
		if constexpr (std::is_same_v<TCHAR, wchar_t>)
			return std::wcin;
		else
			return std::cin;
	}
}

#endif //UTILS_TCHAR_IO_HPP