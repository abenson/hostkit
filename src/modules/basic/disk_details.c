#include <windows.h>
#include "../../arguments.h"
#include "../modules.h"

static int volume_info(TCHAR *disk);
static int physical_drive_info(TCHAR *disk);

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
			physical_drive_info(szSingleDrive);

			close_dict(arguments.log);

			szSingleDrive += _tcslen(szSingleDrive) + 1;
		}

		close_list(arguments.log);
	}

}

static int physical_drive_info(TCHAR *disk)
{
	HANDLE h;
	VOLUME_DISK_EXTENTS diskExtents;
	DWORD size, sizeRet;
	TCHAR logDisk[100];
	TCHAR physicalDrive[100];

	_sntprintf(logDisk, 100, _T("\\\\.\\%.2s"), disk);

	h = CreateFile(logDisk, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	if(h == INVALID_HANDLE_VALUE) {
		return ERR_MODFAIL;
	}

	if(DeviceIoControl(h, IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS, NULL, 0, &diskExtents, sizeof(diskExtents), &size, NULL)) {
		_sntprintf(physicalDrive, 100, _T("\\\\.\\\\PhysicalDrive%u"), diskExtents.Extents[0].DiskNumber);
		add_value(arguments.log, _T("device"), physicalDrive);
	} else {
		CloseHandle(h);
		return ERR_MODFAIL;
	}

	CloseHandle(h);

	return ERR_NONE;
}

static int volume_info(TCHAR *disk)
{
	TCHAR name[100] = {0}, fs[100] = {0};
	TCHAR serialStr[100] = {0};
	DWORD serial, flags;

	GetVolumeInformation(disk, name, 100, &serial, NULL, &flags, fs, 100);

	add_value(arguments.log, _T("name"), name);
	add_value(arguments.log, _T("fs"), fs);

	_sntprintf(serialStr, 100, _T("%04X-%04X"), HIBYTE(serial), LOBYTE(serial));
	add_value(arguments.log, _T("serial"), serialStr);

	if(flags & FILE_READ_ONLY_VOLUME) {
		add_value(arguments.log, _T("readonly"), _T("true"));
	} else {
		add_value(arguments.log, _T("readonly"), _T("false"));
	}

	return ERR_NONE;
}