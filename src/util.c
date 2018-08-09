#include "common.h"
#include "arguments.h"
#include "util.h"

_TCHAR *dupestr(const _TCHAR *str)
{
	_TCHAR *duped = NULL;
	int len;
	if(str) {
		len = _tcslen(str);
		duped = malloc(sizeof(*duped) * (len+1));
		if(duped) {
			_tcsncpy(duped, str, len);
			duped[len] = 0;
		}
	}
	return duped;
}

void quit(void)
{
	exit(EXIT_SUCCESS);
}
