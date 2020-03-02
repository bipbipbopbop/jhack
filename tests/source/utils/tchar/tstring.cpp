#include "source/utils/tchar/tstring.hpp"
#include "source/utils/tchar/io.hpp"
#include <tchar.h>

using namespace jhack;

int		main(void)
{
	Tstring	a("test1");
	Tstring	b(L"test2");
	Tstring_view	bview(b);

	Tcout() << std::endl << a + _T("  ") << bview << _TEXT("\t\t");

	Tstring	buf;

	buf += _T("stuff");
	Tstring aa(std::move(buf));
	Tcout() << aa;
	return 0;
}