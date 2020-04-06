#ifndef PROCESS_PROCESS_HPP
#define PROCESS_PROCESS_HPP

#include <Windows.h>
#include "utils/tchar.hpp"

namespace jhack
{
	/*
	 * getProcessHandleByName:
	 * Retrieve a handle of an existing process.
	 * Handle must be closed after use with the function CloseHandle().
	 *
	 * Return value:
	 * INVALID_HANDLE_VALUE: the requested process cannot be found.
	 * NULL: an error happened while calling OpenProcess(). Call GetLastError() for more information.
	 * Other value: a correct Handle to the corresponding process.
	 * 
	 * To retrieve a Process Handle by PID, use OpenProcess(), from <Windows.h>.
	 */
	HANDLE		getProcessHandleByName(DWORD dwDesiredAccess, Tstring<> name);

	/*
	 * getProcessPath:
	 * retrieve the path of the executable behind the 'process' handle.
	 *
	 * Return value:
	 * a Tstring. If the string is empty, then an error occured.
	 */
	Tstring<>	getProcessPath(HANDLE process);
}

#endif//PROCESS_PROCESS_HPP