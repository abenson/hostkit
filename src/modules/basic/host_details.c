#include "modules\modules.h"

#define _WIN32_WINNT 0x0500

static log_t *log;

static int hostname(void);
static int os_info(void);

int host_details(void)
{
	//log = open_log(_T("-"), _T("json"));

	//if (log == NULL)
	//{
	//	return ERR_MODFAIL;
	//}
	
	//open_section(log, _T("host_details"));

	hostname();
	os_info();

	//close_section(log);
	//close_log(log);
	
	return ERR_NONE;
}

//Based on
//http://msdn.microsoft.com/en-us/library/windows/desktop/ms724301%28v=vs.85%29.aspx
static int hostname(void)
{
	TCHAR buffer[256] = _T("");
	TCHAR fields[8][32] = 
	{
		_T("netbios"),
		_T("dns_hostname"),
		_T("dns_domain"),
		_T("dns_fqdn"),
		_T("pyhsical_netbios"),
		_T("physical_dns_hostname"),
		_T("physical_dns_domain"),
		_T("physical_dns_fqdn")
	};

	DWORD length = sizeof(buffer);
	int i = 0;
		
	for(i = 0; i < ComputerNameMax; i++)
	{
		if (!GetComputerNameEx((COMPUTER_NAME_FORMAT) i, buffer, &length))
		{
			return ERR_MODFAIL;
		}
		else
		{
			_tprintf_s(_T("Field: %s : %s\n"), fields[i], buffer);
			//open_item(log);
			//add_value(log, fields[i], buffer);
			//close_item(log);
		}

		length = _countof(buffer);
		ZeroMemory(buffer, length);
	}

	return ERR_NONE;
}

//Based on
//http://msdn.microsoft.com/en-us/library/windows/desktop/ms724429%28v=vs.85%29.aspx
static int os_info(void)
{


	return ERR_NONE;
}