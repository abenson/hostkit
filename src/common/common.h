#ifndef COMMON_H
#define COMMON_H

#include <windows.h>
#include <tchar.h>

#include <stdio.h>

#define ERR_NONE 0
#define ERR_SYSFAIL 1
#define ERR_MODFAIL 2
#define ERR_NOTFOUND 3
#define ERR_LOGFAIL 4

_TCHAR *dupestr(const _TCHAR *str);

void quit(void);

#endif
