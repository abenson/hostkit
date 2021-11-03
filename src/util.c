#include "common.h"
#include "arguments.h"
#include "util.h"

wchar_t *dupestr(const wchar_t *str)
{
	wchar_t *duped = NULL;
	int len;
	if(str) {
		len = wcslen(str);
		duped = malloc(sizeof(*duped) * (len+1));
		if(duped) {
			wcsncpy(duped, str, len);
			duped[len] = 0;
		}
	}
	return duped;
}

void quit(void)
{
	exit(EXIT_SUCCESS);
}
