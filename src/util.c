#include "common.h"

#include "util.h"

TCHAR *dupestr(const TCHAR *str)
{
	TCHAR *duped;
	duped = malloc(sizeof(*duped) * (_tcslen(str)+1));
	if(duped) {
		_tcsncpy(duped, str, _tcslen(str));
	}
	return NULL;
}

void quit(void)
{
	exit(EXIT_SUCCESS);
}
