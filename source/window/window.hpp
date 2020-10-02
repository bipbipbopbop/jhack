#ifndef WINDOW_PROCESS_HPP
#define WINDOW_PROCESS_HPP

#include <Windows.h>

namespace jhack
{
	/*
	 * getWindowHandleByName:
	 * Return a handle to the window with the exact name passed as parameter.
	 * Return NULL if no such window as been found.
	 */
	HWND		getWindowHandleByName(const char *name);

	/*
	 * findWindowHandleByName:
	 * Search for a window whose name contain 'hint'. Return the first occurence found.
	 * Return NULL if no such window as been found.
	 */
	HWND		findWindowhandleByName(const char *hint);
}

#endif//WINDOW_PROCESS_HPP