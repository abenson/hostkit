#include "../../writer/writer.h"
#include "../../common.h"

#undef BUFLEN
#define BUFLEN 256

int enum_drives(void)
{
	TCHAR drives[BUFLEN];
	int i = 0;
	DWORD type;

	GetLogicalDriveStrings(BUFLEN, drives);

	start_itemlist(scanLog, _T("drives"));

	while(drives[i]) {
		start_itemlist_item(scanLog);

		add_value(scanLog, _T("id"), drives+i);

		type = GetDriveType(drives+i);

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

		end_itemlist_item(scanLog);

		i += _tcslen(drives+i) + 1;
	}
	end_itemlist(scanLog);

	return 0;
}
