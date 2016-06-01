#include <windows.h>
#include "../../arguments.h"
#include "../modules.h"

int enum_windir(void)
{
	TCHAR *pathenv, *path;
	DWORD size;

	size = GetEnvironmentVariable(_T("windir"), NULL, 0);

	if(size == 0) {
		return ERR_MODFAIL;
	}

	pathenv = malloc(sizeof(*pathenv) * size+1);
	memset(pathenv, 0, sizeof(*pathenv) * size+1);
	if(pathenv == NULL) {
		return ERR_MODFAIL;
	}

	size = GetEnvironmentVariable(_T("windir"), pathenv, size);

	if(size == 0) {
		free(pathenv);
		return ERR_MODFAIL;
	}

	start_list(arguments.log, _T("files"));

	lsdir(path);

	close_list(arguments.log);

	free(pathenv);

	return ERR_NONE;
}