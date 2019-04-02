#include "../../writer/writer.h"
#include "../../common.h"


static int hostname(void);
static int domainname(void);
static int currentversion(void);

int host_details(void)
{
	open_section(scanLog, _T("host"));

	hostname();
	domainname();
	currentversion();

	close_section(scanLog);
	return 0;
}

static int hostname(void)
{
	_TCHAR *name = NULL;
	DWORD nameLen = 0;
	LONG status;

	/* Get size of buffer. */
	GetComputerNameEx(ComputerNamePhysicalDnsHostname, name, &nameLen);

	/* Get name of host. */
	name = malloc(sizeof(*name) * nameLen);
	GetComputerNameEx(ComputerNamePhysicalDnsHostname, name, &nameLen);

	add_value(scanLog, _T("hostname"), name);

	free(name);

	return 0;
}

static int domainname(void)
{
	_TCHAR *name = NULL;
	DWORD nameLen = 0;

	/* Get size of buffer. */
	GetComputerNameEx(ComputerNamePhysicalDnsDomain, name, &nameLen);
	
	/* Get name of host. */
	name = malloc(sizeof(*name) * nameLen);
	GetComputerNameEx(ComputerNamePhysicalDnsDomain, name, &nameLen);

	add_value(scanLog, _T("domainname"), name);

	free(name);

	return 0;
}

static int currentversion(void)
{
	_TCHAR *REG_CURRENTVERSION = _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");
	HKEY key;
	_TCHAR value[256];
	DWORD keyType = REG_SZ;
	DWORD valueLen;

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_CURRENTVERSION, 0L, KEY_ALL_ACCESS, &key);

	/* Product name */
	valueLen = 256;
	RegQueryValueEx(key, _T("ProductName"), NULL, &keyType, (LPBYTE)&value, &valueLen);
	add_value(scanLog, _T("product"), value);

	/* Current version */
	valueLen = 256;
	RegQueryValueEx(key, _T("CurrentVersion"), NULL, &keyType, (LPBYTE)&value, &valueLen);
	add_value(scanLog, _T("version"), value);

	/* Service pack */
	valueLen = 256;
	RegQueryValueEx(key, _T("CSDVersion"), NULL, &keyType, (LPBYTE)&value, &valueLen);
	add_value(scanLog, _T("splevel"), value);

	/* Build number */
	valueLen = 256;
	RegQueryValueEx(key, _T("CurrentBuildNumber"), NULL, &keyType, (LPBYTE)&value, &valueLen);
	add_value(scanLog, _T("build"), value);

	RegCloseKey(key);
	return 0;
}
