#include <windows.h>
#include <versionhelpers.h>

#include "../../arguments.h"
#include "../modules.h"

static int hostname(void);
static int domain(void);
static int os_info(void);

int host_details(void)
{
	start_dict(arguments.log, _T("host"));

	hostname();
	domain();

	os_info();

	close_dict(arguments.log);

	return ERR_NONE;
}

static int domain(void)
{
	TCHAR buffer[256];
	DWORD length = sizeof(buffer);
	int i = 0;

	if (GetComputerNameEx(ComputerNameDnsDomain, buffer, &length)) {
		add_value(arguments.log, _T("domain"), buffer);
		return ERR_NONE;
	}

	return ERR_MODFAIL;
}

static int hostname(void)
{
	TCHAR buffer[256];
	DWORD length = sizeof(buffer);
	int i = 0;

	if (GetComputerNameEx(ComputerNameDnsHostname, buffer, &length)) {
		add_value(arguments.log, _T("hostname"), buffer);
		return ERR_NONE;
	}

	return ERR_MODFAIL;
}

static int os_info(void)
{
	TCHAR *versionName = _T("Windows?");

	/* Version */

	/* Can we replace this with something that works after 8.x but doesn't suck? */
	if(IsWindowsServer()) {
		versionName = _T("Windows Server");
	} else {
		if(IsWindows8Point1OrGreater()) {
			versionName = _T("Windows 8.1");
	    } else if(IsWindows8OrGreater()) {
			versionName = _T("Windows 8");
	    } else if(IsWindows7SP1OrGreater()) {
			versionName = _T("Windows 7 SP1");
	    } else if(IsWindows7OrGreater()) {
			versionName = _T("Windows 7 SP0");
	    } else if(IsWindowsVistaSP2OrGreater()) {
			versionName = _T("Windows Vista SP2");
	    } else if(IsWindowsVistaSP1OrGreater()) {
	    	versionName = _T("Windows Vista SP1");
	    } else if(IsWindowsVistaOrGreater()) {
	    	versionName = _T("Windows Vista SP0");
	    } else if(IsWindowsXPSP3OrGreater()) {
	    	versionName = _T("Windows XP SP3");
	    } else if(IsWindowsXPSP2OrGreater()) {
	    	versionName = _T("Windows XP SP2");
	    } else if(IsWindowsXPSP1OrGreater()) {
	    	versionName = _T("Windows XP SP1");
	    } else if(IsWindowsXPOrGreater()) {
	    	versionName = _T("Windows XP SP0");
	    } else {
	    	versionName = _T("Windows Desktop");
	    }
	}

	add_value(arguments.log, _T("version"), versionName);

	/* Edition */

	return ERR_NONE;
}
