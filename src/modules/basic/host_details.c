#include "../../writer/writer.h"
#include "../../common.h"

static int hostname(void);

int host_details(void)
{
	open_section(scanLog, _T("host"));

	hostname();

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

	open_item(scanLog);
	add_value(scanLog, _T("hostname"), name);
	close_item(scanLog);

	free(name);
}
