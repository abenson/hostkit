#include "common.h"

TCHAR *dupestr(const TCHAR *str)
{
	TCHAR *duped;
	duped = malloc(sizeof(*duped) * (_tcslen(str)+1));
	if(duped) {
		//_tcsncpy(duped, str, _tcslen(str));
		_tcsncpy_s(duped, sizeof(*duped) * (_tcslen(str) + 1), str, _tcslen(str));
	}
	return NULL;
}

void quit(void)
{
	exit(EXIT_SUCCESS);
}
