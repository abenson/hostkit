#include "../../writer/writer.h"
#include "../../common.h"

static int hostname(void);
static int domainname(void);

int host_details(void)
{
	open_section(scanLog, _T("host"));

	hostname();
	domainname();

	close_section(scanLog);
	return 0;
}

static int hostname(void)
{
	_TCHAR *name = NULL;
	DWORD nameLen = 0;

	/* Get size of buffer. */
	GetComputerNameEx(ComputerNamePhysicalDnsHostname, name, &nameLen);

	/* Get name of host. */
	name = malloc(sizeof(*name) * nameLen);
	GetComputerNameEx(ComputerNamePhysicalDnsHostname, name, &nameLen);

	add_value(scanLog, _T("hostname"), name);

	free(name);
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
}