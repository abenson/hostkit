#include "common.h"

#include "arguments.h"

#include "persist.h"

int persist(void)
{
	_ftprintf(arguments.log, _T("Persistent mode not implemented!\n"));
	return -1;
}