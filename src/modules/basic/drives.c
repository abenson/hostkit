#include "../../writer/writer.h"
#include "../../common.h"

#undef BUFLEN
#define BUFLEN 256

int enum_drives(void)
{
	TCHAR guid[BUFLEN];
	HANDLE handle;
	open_section(scanLog, _T("drives"));

	handle = FindFirstVolume(guid, BUFLEN);

	start_itemlist(scanLog, _T("drive"));

	start_itemlist_item(scanLog);
	add_value(scanLog, _T("guid"), guid);
	end_itemlist_item(scanLog);

	while(FindNextVolume(handle, guid, BUFLEN)) {
		start_itemlist_item(scanLog);
		add_value(scanLog, _T("guid"), guid);
		end_itemlist_item(scanLog);
	}

	end_itemlist(scanLog);
	FindVolumeClose(handle);

	close_section(scanLog);
}
