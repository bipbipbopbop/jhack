#include "source/process/process.hpp"
#include <cassert>
#include <errhandlingapi.h>

int		main(void)
{
	//Hook a lambda on abort to avoid Windows debug dialog
	_CrtSetReportHook([](int reportType, char *message, int *returnValue){
		std::cerr << "[HOOK] Assert failed: " << message << std::endl;
		exit(1);
		return 0;
	});

	assert((jhack::getProcessHandleByName(PROCESS_VM_READ, "invalidProcess Name69420") == INVALID_HANDLE_VALUE));
	assert((jhack::getProcessHandleByName(PROCESS_VM_READ, "TestProcess.exe") != INVALID_HANDLE_VALUE));//This process

	return 0;
}