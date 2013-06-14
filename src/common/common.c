#include "common.h"

_TCHAR *dupestr(const _TCHAR *str)
{
	_TCHAR *duped;
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
