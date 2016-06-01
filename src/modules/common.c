#include <windows.h>

#include "../arguments.h"
#include "modules.h"

int lsdir(const TCHAR *rootpath)
{
	start_dict(arguments.log, _T("file"));
	add_value(arguments.log, _T("path"), rootpath);
	close_dict(arguments.log);
}