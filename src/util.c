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

_TCHAR *dupe2tchar(const char *str)
{
	_TCHAR *duped = NULL;
	int len, i;
	if(str) {
		len = strlen(str);
		duped = malloc(sizeof(*duped) * (len+1));
		for(i=0; i<len; i++) {
			duped[i] = (TCHAR)str[i];
		}
		duped[i] = '\0';
	}
	return duped;
}

void quit(void)
{
	exit(EXIT_SUCCESS);
}
