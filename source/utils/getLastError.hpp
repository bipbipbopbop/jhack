#ifndef UTILS_GETLASTERROR_HPP
#define UTILS_GETLASTERROR_HPP

#include <string>
#include "tchar/tstring.hpp"

namespace jhack
{
	/*
	 * getLastError:
	 * wrapper for the GetLastError() function from the Windows API.
	 * Call GetLastError() and return the string corresponding to the received error code.
	 */
	std::string		getLastError(void);
}

#endif//UTILS_GETLASTERROR_HPP