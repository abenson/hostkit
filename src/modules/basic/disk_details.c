#include <windows.h>
#include "../../arguments.h"
#include "../modules.h"

static int volume_info(TCHAR *disk);

int disk_details(void)
{
	DWORD dwSize = MAX_PATH;
	TCHAR szLogicalDrives[MAX_PATH] = {0};
	DWORD dwResult = GetLogicalDriveStrings(dwSize,szLogicalDrives);

	if (dwResult > 0 && dwResult <= MAX_PATH)
	{
		TCHAR* szSingleDrive = szLogicalDrives;

		start_list(arguments.log, _T("drives"));

		while(*szSingleDrive)
		{
			start_dict(arguments.log, _T("drive"));

			add_value(arguments.log, _T("assignment"), szSingleDrive);

			volume_info(szSingleDrive);

			close_dict(arguments.log);

			szSingleDrive += _tcslen(szSingleDrive) + 1;
		}

		close_list(arguments.log);
	}

}

static int volume_info(TCHAR *disk)
{
	TCHAR name[100], fs[100];
	TCHAR serialStr[100];
	DWORD serial, flags;

	GetVolumeInformation(disk, name, 100, &serial, NULL, &flags, fs, 100);

	add_value(arguments.log, _T("name"), name);
	add_value(arguments.log, _T("fs"), fs);

	_sntprintf(serialStr, 100, _T("%x"), serial);
	add_value(arguments.log, _T("serial"), serialStr);

	if(flags & FILE_READ_ONLY_VOLUME) {
		add_value(arguments.log, _T("readonly"), _T("true"));
	} else {
		add_value(arguments.log, _T("readonly"), _T("false"));
	}

	return ERR_NONE;
}