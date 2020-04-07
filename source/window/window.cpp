#include <Windows.h>
#include <iostream>

namespace jhack
{
	namespace
	{
		struct _callbackData
		{
			void	*data;
			HWND	windowHandle;
		};

		BOOL CALLBACK	_getWinCallback(_In_ HWND hwnd, _In_ LPARAM lParam)
		{
			char			winName[512];
			_callbackData	*param = (_callbackData*)lParam;

			GetWindowTextA(hwnd, winName, sizeof(winName));
			if (strcmp(winName, (const char*)(param->data)) == 0)
			{
				param->windowHandle = hwnd;
				return false;
			}
			return true;
		}

		BOOL CALLBACK	_findWinCallback(_In_ HWND hwnd, _In_ LPARAM lParam)
		{
			char		winName[512];
			_callbackData	*param = (_callbackData*)lParam;

			GetWindowTextA(hwnd, winName, sizeof(winName));
			if (strstr(winName, (const char*)(param->data)) != NULL)
			{
				param->windowHandle = hwnd;
				return false;
			}
			return true;
		}
	}

	HWND		getWindowHandleByName(const char *name)
	{
		_callbackData	data{(void*)name, NULL};
		EnumWindows(_getWinCallback, (LPARAM)&data);
		return data.windowHandle;
	}

	HWND		findWindowhandleByName(const char *hint)
	{
		_callbackData	data{(void*)hint, NULL};
		EnumWindows(_findWinCallback, (LPARAM)&data);
		return data.windowHandle;
	}
}