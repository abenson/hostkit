#include <windows.h>
#include <lm.h>

#include "../../common/common.h"
#include "../../arguments.h"
#include "../modules.h"

static int hostname(void);
static int workgroup(void);
static int domain(void);
static int os_info(void);

int host_details(void)
{
	open_section(arguments.log, _T("Host"));
	open_item(arguments.log);

	hostname();
	domain();
	workgroup();
	
	os_info();

	close_item(arguments.log);
	close_section(arguments.log);
	
	return ERR_NONE;
}

static int workgroup(void)
{
	WKSTA_INFO_102 *wks;
	
	NetWkstaGetInfo(NULL, 102, (LPBYTE*)&wks);
	add_value(arguments.log, _T("NetBIOSName"), wks->wki102_computername);
	add_value(arguments.log, _T("Workgroup"), wks->wki102_langroup);
	NetApiBufferFree(wks);

	return ERR_NONE;
}

static int domain(void)
{
	TCHAR buffer[256];
	DWORD length = sizeof(buffer);
	int i = 0;
		
	if (!GetComputerNameEx(ComputerNameDnsDomain, buffer, &length))
	{
		return ERR_MODFAIL;
	}
	else
	{
		add_value(arguments.log, _T("Domain"), buffer);
	}

	return ERR_NONE;
}

//Based on
//http://msdn.microsoft.com/en-us/library/windows/desktop/ms724301%28v=vs.85%29.aspx
static int hostname(void)
{
	TCHAR buffer[256];
	DWORD length = sizeof(buffer);
	int i = 0;
		
	if (!GetComputerNameEx(ComputerNameDnsHostname, buffer, &length))
	{
		return ERR_MODFAIL;
	}
	else
	{
		add_value(arguments.log, _T("Hostname"), buffer);
	}

	return ERR_NONE;
}

//Based on
//http://msdn.microsoft.com/en-us/library/windows/desktop/ms724429%28v=vs.85%29.aspx
static int os_info(void)
{


	return ERR_NONE;
}
