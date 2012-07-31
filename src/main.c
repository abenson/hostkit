#include "common.h"

#include "arguments.h"

TCHAR *get_version(void)
{
	return _T("HostKit Agent PREALPHA\nCompiled at ") __TIME__ _T(" on ") __DATE__ _T("\n");
}

int _tmain(int argc, TCHAR *argv[])
{
	initialize_arguments();

	if(parse_arguments(argv) != ARGS_OK || arguments.error) {
		_tprintf(_T("%s"), get_help());
		quit();
	}

	if(arguments.debug) {
		printf("Debug log is enabled.\n");
	}

	if(arguments.version == TRUE) {
		_tprintf(_T("%s"), get_version());
		quit();
	}

	

	return 0;
}
