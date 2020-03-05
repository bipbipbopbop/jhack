//This file is a simple program that will be use for testing the library.
//Please Compile me! : cl.exe deadbeef.cpp /link /DYNAMICBASE:NO
// NB: I do not master the Windows behavior about fixed base address.
// With Cheat engine, i found out that the base address I based y tests upon was 0x14F000
#include <iostream>
#include <Windows.h>
#include <synchapi.h>

int		main(void)
{
	unsigned int	a = 0xDEADBEEF;
	char			pad[69] = "AAAABBBB";
	char			*ptr1 = pad;
	char			**ptr2 = &ptr1;

	Sleep(60000);
//	std::cout << std::hex << a;
	return 0;
}