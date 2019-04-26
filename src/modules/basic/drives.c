#include "../../writer/writer.h"
#include "../../common.h"

#undef BUFLEN
#define BUFLEN 32768

static int volume_info(TCHAR *disk);

int enum_drives(void)
{
	TCHAR guid[BUFLEN], name[BUFLEN];
	HANDLE handle;
	unsigned long i = 0, c, type;

	start_itemlist(scanLog, _T("drives"));

	handle = FindFirstVolume(guid, BUFLEN);

	do {
		start_itemlist_item(scanLog, _T("drive"));

		add_value(scanLog, _T("guid"), guid);

		if(GetVolumePathNamesForVolumeName(guid, name, BUFLEN, &c) != 0) {
			if(name[0]) {
				add_value(scanLog, _T("letter"), name);
				type = GetDriveType(name);
				switch(type) {
					case DRIVE_NO_ROOT_DIR:
						add_value(scanLog, _T("type"), _T("invalid"));
						break;
					case DRIVE_REMOVABLE:
						add_value(scanLog, _T("type"), _T("removable"));
						break;
					case DRIVE_FIXED:
						add_value(scanLog, _T("type"), _T("fixed"));
						break;
					case DRIVE_REMOTE:
						add_value(scanLog, _T("type"), _T("remote"));
						break;
					case DRIVE_CDROM:
						add_value(scanLog, _T("type"), _T("cdrom"));
						break;
					case DRIVE_RAMDISK:
						add_value(scanLog, _T("type"), _T("ramdisk"));
						break;
					case DRIVE_UNKNOWN:
					default:
						add_value(scanLog, _T("type"), _T("unknown"));
						break;
				}
				volume_info(_T("letter"));
			}
		}
		end_itemlist_item(scanLog);
	} while (FindNextVolume(handle, guid, BUFLEN));
	
	end_itemlist(scanLog);

	return 0;
}

static int volume_info(TCHAR *disk)
{
	TCHAR name[BUFLEN] = {0}, fs[BUFLEN] = {0};
	TCHAR serialStr[BUFLEN] = {0};
	DWORD serial, flags;
	DWORD ret;

	ret = GetVolumeInformation(disk, name, BUFLEN, &serial, NULL, &flags, fs, BUFLEN);

	if(ret == 0) {
		add_value(scanLog, _T(""), _T("")): 
		return 1;
	}

	add_value(scanLog, _T("name"), name);
	add_value(scanLog, _T("fs"), fs);

	_sntprintf(serialStr, BUFLEN, _T("%04X-%04X"), HIBYTE(serial), LOBYTE(serial));
	add_value(scanLog, _T("serial"), serialStr);

	if(flags & FILE_READ_ONLY_VOLUME) {
		add_value(scanLog, _T("readonly"), _T("true"));
	} else {
		add_value(scanLog, _T("readonly"), _T("false"));
	}

	return 0;
}
