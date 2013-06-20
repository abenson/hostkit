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
#define ERR_GENFAIL 5
#define ERR_NOTIMPL 6

TCHAR *dupestr(const TCHAR *str);

void quit(void);

#endif
