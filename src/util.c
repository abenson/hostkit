#include "util.h"

TCHAR *dupestr(const TCHAR *str)
{
	TCHAR *duped;
	duped = malloc(sizeof(*duped) * (_tcslen(str)+1));
	if(duped) {
		_tcsncpy_s(duped, _tcslen(str)+1, str, _tcslen(str));
	}
	return duped;
}

TCHAR *lpstr2tchar(const LPSTR str)
{
	TCHAR *duped;
	size_t i, len;

	len = strlen(str);
	duped = malloc(sizeof(*duped) * (len+1));

	if(duped) {
		for(i=0; i<len; i++) {
			duped[i] = (TCHAR)str[i];
		}
	}

	return duped;
}

TCHAR *lpwstr2tchar(const LPWSTR str)
{
	TCHAR *duped;
	size_t i, len;

	len = wcslen(str);
	duped = malloc(sizeof(*duped) * (len+1));

	if(duped) {
		for(i=0; i<len; i++) {
			duped[i] = (TCHAR)str[i];
		}
	}

	return duped;
}

void quit(void)
{
	exit(EXIT_SUCCESS);
}
