#include <windows.h>
#include <tchar.h>

#include <stdio.h>

#include "util.h"
#include "arguments.h"

#include "persist.h"

int persist(void)
{
	_ftprintf(arguments.logFile, _T("Persistent mode not implemented!\n"));
	return ERR_NOTIMPL;
}
