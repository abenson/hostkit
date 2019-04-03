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

	add_value(scanLog, _T("drive"), guid);

	while(FindNextVolume(handle, guid, BUFLEN)) {
		add_value(scanLog, _T("drive"), guid);
	}

	FindVolumeClose(handle);

	close_section(scanLog);
}
