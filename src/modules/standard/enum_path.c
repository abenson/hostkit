#include <windows.h>
#include "../../arguments.h"
#include "../modules.h"

int enum_path(void)
{
	TCHAR *pathenv, *path;
	DWORD size;

	size = GetEnvironmentVariable(_T("PATH"), NULL, 0);

	if(size == 0) {
		return ERR_MODFAIL;
	}

	pathenv = malloc(sizeof(*pathenv) * size+1);
	memset(pathenv, 0, sizeof(*pathenv) * size+1);
	if(pathenv == NULL) {
		return ERR_MODFAIL;
	}

	size = GetEnvironmentVariable(_T("PATH"), pathenv, size);

	if(size == 0) {
		free(pathenv);
		return ERR_MODFAIL;
	}

	start_list(arguments.log, _T("files"));

	path=pathenv;
	while(*path) {
		if(*path == _T(';')) {
			*path = _T('\0');
		}
		path++;
	}

	path=pathenv;

	while(*path) {
		lsdir(path);
		path += _tcslen(path)+1;
	}

	close_list(arguments.log);

	free(pathenv);

	return ERR_NONE;
}