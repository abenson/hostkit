#include "../../common.h"

int host_details(void)
{

	return 0;
}

static int hostname(void)
{
	TCHAR *name = NULL;
	DWORD nameLen = 0;

	/* Get size of buffer. */
	GetComputerNameEx(ComputerNameDnsHostname, name, &nameLen);
	
	/* Get name of host. */
	name = malloc(sizeof(*name) * nameLen);
	GetComputerNameEx(ComputerNameDnsHostname, name, &nameLen);

	

	free(name);
}

