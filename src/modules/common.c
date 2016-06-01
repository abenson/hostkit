#include <windows.h>
#include <tchar.h>

#include "../arguments.h"
#include "modules.h"

static int file_info(const TCHAR *rootpath, const WIN32_FIND_DATA *ffd);

int lsdir(const TCHAR *rootpath)
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH], subDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError=0;

	_stprintf(szDir, MAX_PATH, _T("\\\\?\\%s\\*"), rootpath);
	hFind = FindFirstFile(szDir, &ffd);
	if(hFind != INVALID_HANDLE_VALUE) {
		do {
			if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if(_tcscmp(ffd.cFileName, _T(".")) != 0 || _tcscmp(ffd.cFileName, _T("..")) != 0) {
					_stprintf(subDir, MAX_PATH, _T("%s\\%s"), rootpath, ffd.cFileName);
					lsdir(subDir);
				}
			}
			file_info(rootpath, &ffd);
		} while(FindNextFile(hFind, &ffd));
		FindClose(hFind);
	}
	return 0;
}

static int file_info(const TCHAR *rootpath, const WIN32_FIND_DATA *ffd)
{
	TCHAR sizeStr[0x10] = {0};

	_stprintf(sizeStr, 0x10, _T("%llu"), (ffd->nFileSizeHigh * (MAXDWORD+1)) + ffd->nFileSizeLow);

	start_dict(arguments.log, _T("file"));
	add_value(arguments.log, _T("path"), rootpath);
	add_value(arguments.log, _T("name"), ffd->cFileName);
	add_value(arguments.log, _T("size"), sizeStr);
	close_dict(arguments.log);
}
