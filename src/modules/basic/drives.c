#include "../../writer/writer.h"
#include "../../common.h"

#undef BUFLEN
#define BUFLEN 32768

static int volume_info(wchar_t *disk);

int enum_drives(void)
{
	wchar_t guid[BUFLEN], name[BUFLEN];
	HANDLE handle;
	unsigned long c, type;

	start_itemlist(scanLog, L"drives");

	handle = FindFirstVolume(guid, BUFLEN);

	do {
		start_itemlist_item(scanLog, L"drive");

		add_value(scanLog, L"guid", guid);

		if(GetVolumePathNamesForVolumeName(guid, name, BUFLEN, &c) != 0) {
			if(name[0]) {
				add_value(scanLog, L"letter", name);
				type = GetDriveType(name);
				switch(type) {
					case DRIVE_NO_ROOT_DIR:
						add_value(scanLog, L"type", L"invalid");
						break;
					case DRIVE_REMOVABLE:
						add_value(scanLog, L"type", L"removable");
						break;
					case DRIVE_FIXED:
						add_value(scanLog, L"type", L"fixed");
						break;
					case DRIVE_REMOTE:
						add_value(scanLog, L"type", L"remote");
						break;
					case DRIVE_CDROM:
						add_value(scanLog, L"type", L"cdrom");
						break;
					case DRIVE_RAMDISK:
						add_value(scanLog, L"type", L"ramdisk");
						break;
					case DRIVE_UNKNOWN:
					default:
						add_value(scanLog, L"type", L"unknown");
						break;
				}
				volume_info(L"letter");
			}
		}
		end_itemlist_item(scanLog);
	} while (FindNextVolume(handle, guid, BUFLEN));
	
	end_itemlist(scanLog);

	return 0;
}

static int volume_info(wchar_t *disk)
{
	wchar_t name[BUFLEN] = {0}, fs[BUFLEN] = {0};
	wchar_t serialStr[BUFLEN] = {0};
	DWORD serial, flags;
	DWORD ret;

	ret = GetVolumeInformation(disk, name, BUFLEN, &serial, NULL, &flags, fs, BUFLEN);

	if(ret == 0) {
		add_value(scanLog, L"", L"");
		return 1;
	}

	add_value(scanLog, L"name", name);
	add_value(scanLog, L"fs", fs);

	_snwprintf(serialStr, BUFLEN, L"%04X-%04X", HIBYTE(serial), LOBYTE(serial));
	add_value(scanLog, L"serial", serialStr);

	if(flags & FILE_READ_ONLY_VOLUME) {
		add_value(scanLog, L"readonly", L"true");
	} else {
		add_value(scanLog, L"readonly", L"false");
	}

	return 0;
}
