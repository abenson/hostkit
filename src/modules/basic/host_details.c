#include <intrin.h>

#include "../../writer/writer.h"
#include "../../common.h"

#undef BUFSIZE
#define BUFSIZE 256

static int hostname(void);
static int domainname(void);
static int currentversion(void);
static int architecture(void);
static int memory(void);
static int checkvm(void);

int host_details(void)
{
	open_section(scanLog, _T("host"));

	hostname();
	domainname();
	currentversion();
	architecture();
	memory();
	checkvm();

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
	_TCHAR value[BUFSIZE];
	DWORD keyType = REG_SZ;
	DWORD valueLen;

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_CURRENTVERSION, 0L, KEY_ALL_ACCESS, &key);

	/* Product name */
	valueLen = BUFSIZE;
	RegQueryValueEx(key, _T("ProductName"), NULL, &keyType, (LPBYTE)&value, &valueLen);
	add_value(scanLog, _T("product"), value);

	/* Current version */
	valueLen = BUFSIZE;
	RegQueryValueEx(key, _T("CurrentVersion"), NULL, &keyType, (LPBYTE)&value, &valueLen);
	add_value(scanLog, _T("version"), value);

	/* Service pack */
	valueLen = BUFSIZE;
	RegQueryValueEx(key, _T("CSDVersion"), NULL, &keyType, (LPBYTE)&value, &valueLen);
	add_value(scanLog, _T("splevel"), value);

	/* Build number */
	valueLen = BUFSIZE;
	RegQueryValueEx(key, _T("CurrentBuildNumber"), NULL, &keyType, (LPBYTE)&value, &valueLen);
	add_value(scanLog, _T("build"), value);

	RegCloseKey(key);
	return 0;
}

static int architecture(void)
{
	SYSTEM_INFO sysinfo;
	TCHAR value[BUFSIZE];
	GetSystemInfo(&sysinfo);

	switch(sysinfo.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_AMD64:
			add_value(scanLog, _T("arch"), _T("x86_64"));
			break;
		case PROCESSOR_ARCHITECTURE_IA64:
			add_value(scanLog, _T("arch"), _T("ia64"));
			break;
		case PROCESSOR_ARCHITECTURE_INTEL:
			add_value(scanLog, _T("arch"), _T("x86"));
			break;
#ifdef PROCESSOR_ARCHITECTURE_ARM
		case PROCESSOR_ARCHITECTURE_ARM:
			add_value(scanLog, _T("arch"), _T("arm"));
			break;
#endif
#ifdef PROCESSOR_ARCHITECTURE_ARM64
		case PROCESSOR_ARCHITECTURE_ARM64:
			add_value(scanLog, _T("arch"), _T("arm64"));
			break;
#endif
		default:
			add_value(scanLog, _T("arch"), _T("unknown"));
			break;
	}

	_stprintf(value, BUFSIZE, _T("%d"), sysinfo.dwNumberOfProcessors);
	add_value(scanLog, _T("processors"), value);

	return 0;
}

static int memory(void)
{
	MEMORYSTATUSEX mse;
	TCHAR value[BUFSIZE];

	mse.dwLength = sizeof mse;

	GlobalMemoryStatusEx(&mse);

	_stprintf(value, BUFSIZE, _T("%llu"), mse.ullTotalPhys / (1024*1024));
	add_value(scanLog, _T("memtotal"), value);

	_stprintf(value, BUFSIZE, _T("%llu"), mse.ullAvailPhys / (1024*1024));
	add_value(scanLog, _T("memavail"), value);

	return 0;
}

static int checkvm(void)
{
	unsigned int cpuInfo[4];
	__cpuid((int*)cpuInfo, 1);
	if (((cpuInfo[2] >> 31) & 1) == 1) {
		add_value(scanLog, _T("virtualized"), _T("yes"));
	} else {
		add_value(scanLog, _T("virtualized"), _T("no"));
	}
	return 0;
}
