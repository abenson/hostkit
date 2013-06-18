#include "common.h"

TCHAR *dupestr(const TCHAR *str)
{
	TCHAR *duped;
	duped = malloc(sizeof(*duped) * (_tcslen(str)+1));
	if(duped) {
		_tcsncpy_s(duped, _tcslen(str)+1, str, _tcslen(str));
	}
	return duped;
}

void quit(void)
{
	exit(EXIT_SUCCESS);
}
