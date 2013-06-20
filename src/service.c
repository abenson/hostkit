#include <Windows.h>
#include <tchar.h>

#include <stdio.h>

#include "arguments.h"
#include "service.h"

int servicize(void)
{
	_ftprintf(arguments.logFile, _T("Service mode not implemented!\n"));
	return -1;
}
