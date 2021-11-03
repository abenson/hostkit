#include "../../writer/writer.h"
#include "../../common.h"

#undef BUFSIZE
#define BUFSIZE 256

static int hostname(void);
static int domainname(void);
static int workgroup(BOOL);
static int currentversion(void);
static int architecture(void);
static int memory(void);
static int checkvm(void);

int host_details(void)
{
	open_section(scanLog, L"host");

	hostname();
	if(domainname() != 0) {
		workgroup(FALSE);
	}
	currentversion();
	architecture();
	memory();
	checkvm();

	close_section(scanLog);

	return 0;
}

static int hostname(void)
{
	wchar_t *name = NULL;
	DWORD nameLen = 0;

	/* Get size of buffer. */
	GetComputerNameEx(ComputerNamePhysicalDnsHostname, name, &nameLen);

	/* Get name of host. */
	name = malloc(sizeof(*name) * nameLen);
	GetComputerNameEx(ComputerNamePhysicalDnsHostname, name, &nameLen);

	add_value(scanLog, L"hostname", name);

	free(name);

	return 0;
}

static int domainname(void)
{
	wchar_t *name = NULL;
	DWORD nameLen = 0;
	int ret = 0;

	/* Get size of buffer. */
	GetComputerNameEx(ComputerNamePhysicalDnsDomain, name, &nameLen);
	
	/* Get name of host. */
	name = malloc(sizeof(*name) * nameLen);
	if(GetComputerNameEx(ComputerNamePhysicalDnsDomain, name, &nameLen) == 0) {
		add_value(scanLog, L"addomain", name);
		workgroup(TRUE);
	} else {
		ret = -1;
	}

	free(name);

	return ret;
}

static int workgroup(BOOL onDomain)
{
	WKSTA_INFO_100 *wks;

	NetWkstaGetInfo(NULL, 100, (BYTE**)&wks);

	if(onDomain) {
		add_value(scanLog, L"domain", wks->wki100_langroup);
	} else {
		add_value(scanLog, L"workgroup", wks->wki100_langroup);
	}
	NetApiBufferFree(wks);
	return 0;
}

static int currentversion(void)
{
	wchar_t *REG_CURRENTVERSION = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	HKEY key;
	wchar_t value[BUFSIZE];
	DWORD keyType = REG_SZ;
	DWORD valueLen;

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_CURRENTVERSION, 0L, KEY_ALL_ACCESS, &key);

	/* Product name */
	valueLen = BUFSIZE;
	RegQueryValueEx(key, L"ProductName", NULL, &keyType, (LPBYTE)&value, &valueLen);
	add_value(scanLog, L"product", value);

	/* Current version */
	valueLen = BUFSIZE;
	RegQueryValueEx(key, L"CurrentVersion", NULL, &keyType, (LPBYTE)&value, &valueLen);
	add_value(scanLog, L"version", value);

	/* Service pack */
	valueLen = BUFSIZE;
	RegQueryValueEx(key, L"CSDVersion", NULL, &keyType, (LPBYTE)&value, &valueLen);
	add_value(scanLog, L"splevel", value);

	/* Build number */
	valueLen = BUFSIZE;
	RegQueryValueEx(key, L"CurrentBuildNumber", NULL, &keyType, (LPBYTE)&value, &valueLen);
	add_value(scanLog, L"build", value);

	RegCloseKey(key);
	return 0;
}

static int architecture(void)
{
	SYSTEM_INFO sysinfo;
	wchar_t value[BUFSIZE];
	GetSystemInfo(&sysinfo);

	switch(sysinfo.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_AMD64:
			add_value(scanLog, L"arch", L"x86_64");
			break;
		case PROCESSOR_ARCHITECTURE_IA64:
			add_value(scanLog, L"arch", L"ia64");
			break;
		case PROCESSOR_ARCHITECTURE_INTEL:
			add_value(scanLog, L"arch", L"x86");
			break;
#ifdef PROCESSOR_ARCHITECTURE_ARM
		case PROCESSOR_ARCHITECTURE_ARM:
			add_value(scanLog, L"arch", L"arm");
			break;
#endif
#ifdef PROCESSOR_ARCHITECTURE_ARM64
		case PROCESSOR_ARCHITECTURE_ARM64:
			add_value(scanLog, L"arch", L"arm64");
			break;
#endif
		default:
			add_value(scanLog, L"arch", L"unknown");
			break;
	}

	swprintf(value, BUFSIZE, L"%d", sysinfo.dwNumberOfProcessors);
	add_value(scanLog, L"processors", value);

	return 0;
}

static int memory(void)
{
	MEMORYSTATUSEX mse;
	wchar_t value[BUFSIZE];

	mse.dwLength = sizeof mse;

	GlobalMemoryStatusEx(&mse);

	swprintf(value, BUFSIZE, L"%llu", mse.ullTotalPhys / (1024*1024));
	add_value(scanLog, L"memtotal", value);

	swprintf(value, BUFSIZE, L"%llu", mse.ullAvailPhys / (1024*1024));
	add_value(scanLog, L"memavail", value);

	return 0;
}

static int checkvm(void)
{
	unsigned int cpuInfo[4];
	__cpuid((int*)cpuInfo, 1);
	if (((cpuInfo[2] >> 31) & 1) == 1) {
		add_value(scanLog, L"virtualized", L"yes");
	} else {
		add_value(scanLog, L"virtualized", L"no");
	}
	return 0;
}
