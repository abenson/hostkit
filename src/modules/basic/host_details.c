#include <windows.h>
#include <lm.h>
#include <dsrole.h>
#include <versionhelpers.h>
#include <intrin.h>


#include "../../arguments.h"
#include "../modules.h"

static int hostname(void);
static int domain(void);
static int ostype(void);
static int version(void);
static int check64(void);
static int architecture(void);
static int processors(void);
static int memory(void);
static int getenvironment(void);

int host_details(void)
{
	start_dict(arguments.log, _T("host"));

	hostname();
	domain();
	ostype();
	version();
	check64();
	architecture();
	processors();
	memory();
	getenvironment();

	close_dict(arguments.log);

	return ERR_NONE;
}

static int getenvironment(void)
{
	TCHAR *envb, *env, *key, *val;
	size_t len;

	envb = GetEnvironmentStrings();

	start_dict(arguments.log, _T("environment"));
	env = envb;
	while(*env) {
		key = dupestr(env);
		val = key + _tcscspn(key, _T("="));
		*val = 0;
		val++;
		add_value(arguments.log, key, val);
		free(key);
		env += _tcslen(env) + 1;
	}
	close_dict(arguments.log);
	FreeEnvironmentStrings(envb);
	return 0;
}

static int memory(void)
{
	TCHAR buf[1024];
	MEMORYSTATUSEX mem;

	mem.dwLength = sizeof(mem);
	GlobalMemoryStatusEx(&mem);

	start_dict(arguments.log, _T("memory"));
		_stprintf(buf, 1024, _T("%llu"), mem.ullTotalPhys);
		add_value(arguments.log, _T("total"), buf);
		_stprintf(buf, 1024, _T("%llu"), mem.ullAvailPhys);
		add_value(arguments.log, _T("free"), buf);
	close_dict(arguments.log);
}

static int processors(void)
{
	SYSTEM_INFO si;
	TCHAR buf[100];
	TCHAR *cpuStr;
	int cpuInfo[4] = {0};
	char CPUBrandString[0x40];



	GetNativeSystemInfo(&si);

	start_dict(arguments.log, _T("processors"));
		memset(CPUBrandString, 0, 0x40);
		__cpuid(cpuInfo, 0x80000002);
		memcpy(CPUBrandString, cpuInfo, sizeof(cpuInfo));
		__cpuid(cpuInfo, 0x80000003);
		memcpy(CPUBrandString + 16, cpuInfo, sizeof(cpuInfo));
		__cpuid(cpuInfo, 0x80000004);
		memcpy(CPUBrandString + 32, cpuInfo, sizeof(cpuInfo));
		cpuStr = lpstr2tchar(CPUBrandString);
		add_value(arguments.log, _T("name"), cpuStr);
		free(cpuStr);
		_stprintf(buf, 10, _T("%d"), si.dwNumberOfProcessors);
		add_value(arguments.log, _T("count"), buf);
		_stprintf(buf, 10, _T("%d"), HIBYTE(si.wProcessorRevision));
		add_value(arguments.log, _T("model"), buf);
		_stprintf(buf, 10, _T("%d"), LOBYTE(si.wProcessorRevision));
		add_value(arguments.log, _T("stepping"), buf);

	close_dict(arguments.log);
}

static int ostype(void)
{
	if(IsWindowsServer()) {
		add_value(arguments.log, _T("windows"), _T("server"));
	} else {
		add_value(arguments.log, _T("windows"), _T("client"));
	}
}

static int architecture(void)
{
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);
	switch(si.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_AMD64:
			add_value(arguments.log, _T("arch"), _T("amd64"));
			break;
		case PROCESSOR_ARCHITECTURE_ARM:
			add_value(arguments.log, _T("arch"), _T("arm"));
			break;
		case PROCESSOR_ARCHITECTURE_IA64:
			add_value(arguments.log, _T("arch"), _T("ia64"));
			break;
		case PROCESSOR_ARCHITECTURE_INTEL:
			add_value(arguments.log, _T("arch"), _T("i686"));
			break;
		case PROCESSOR_ARCHITECTURE_UNKNOWN:
		default:
			add_value(arguments.log, _T("arch"), _T("unknown"));
			break;
	}
}

static int check64(void)
{
	void *fnIsWow64;

	fnIsWow64 = GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "IsWow64Process");

	if(fnIsWow64 == NULL) {
		add_value(arguments.log, _T("wow64"), _T("false"));
	} else {
		BOOL isWow64;
		IsWow64Process(GetCurrentProcess(), &isWow64);
		if(isWow64) {
			add_value(arguments.log, _T("wow64"), _T("true"));
		} else {
			add_value(arguments.log, _T("wow64"), _T("false"));
		}
	}
	return ERR_NONE;
}

static int domain(void)
{
	DSROLE_PRIMARY_DOMAIN_INFO_BASIC *info;
	DWORD ret;

	ret = DsRoleGetPrimaryDomainInformation(NULL,  DsRolePrimaryDomainInfoBasic, (BYTE**)&info);

	/*
		I'd like to clean this section up a bit. I like the informaiton gathered, but I dont't like how
		it's being presented.
	*/

	if(ret == ERROR_SUCCESS) {
		switch(info->MachineRole) {
			case DsRole_RoleStandaloneWorkstation:
				add_value(arguments.log, _T("role"), _T("workstation"));
				add_value(arguments.log, _T("workgroup"), info->DomainNameFlat);
				break;
			case DsRole_RoleMemberWorkstation:
				add_value(arguments.log, _T("role"), _T("domain workstation"));
				add_value(arguments.log, _T("domain"), info->DomainNameDns);
				break;
			case DsRole_RoleStandaloneServer:
				add_value(arguments.log, _T("role"), _T("server"));
				add_value(arguments.log, _T("workgroup"), info->DomainNameFlat);
				break;
			case DsRole_RoleMemberServer:
				add_value(arguments.log, _T("role"), _T("domain server"));
				add_value(arguments.log, _T("domain"), info->DomainNameDns);
				break;
			case DsRole_RoleBackupDomainController:
			case DsRole_RolePrimaryDomainController:
				add_value(arguments.log, _T("role"), _T("domain controller"));
				add_value(arguments.log, _T("domain"), info->DomainNameDns);
				break;
		}
	}

	DsRoleFreeMemory(info);
	return ERR_MODFAIL;
}

static int hostname(void)
{
	TCHAR buffer[256];
	DWORD length = sizeof(buffer);
	int i = 0;

	if (GetComputerNameEx(ComputerNamePhysicalNetBIOS, buffer, &length)) {
		add_value(arguments.log, _T("hostname"), buffer);
		return ERR_NONE;
	}

	return ERR_MODFAIL;
}

static int version(void)
{
	WKSTA_INFO_101 *inf;
	TCHAR str[5];

	NetWkstaGetInfo(NULL, 101, (BYTE**)&inf);

	_stprintf(str, 5, _T("%d.%d"), inf->wki101_ver_major, inf->wki101_ver_minor);

	add_value(arguments.log, _T("version"), str);

	NetApiBufferFree((BYTE**)inf);

	return ERR_NONE;
}
