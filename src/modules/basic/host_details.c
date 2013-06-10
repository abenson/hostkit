#include "../../common.h"

int host_details(void)
{

	return 0;
}

static int hostname(void)
{
	_TCHAR *name = NULL;
	DWORD nameLen = 0;

	/* Get size of buffer. */
	GetComputerNameExW(ComputerNameDnsHostname, name, &nameLen);
	
	/* Get name of host. */
	name = malloc(sizeof(*name) * nameLen);
	GetComputerNameExW(ComputerNameDnsHostname, name, &nameLen);

	

	free(name);
}

