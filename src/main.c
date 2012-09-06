#include "common.h"

#include "arguments.h"

TCHAR *get_version(void)
{
	return _T("HostKit Agent PREALPHA\nCompiled at ") __TIME__ _T(" on ") __DATE__ _T("\n");
}

int _tmain(int argc, TCHAR *argv[])
{
	int result;

	initialize_arguments();

	if(parse_arguments(argv) != ARGS_OK || arguments.error) {
		_tprintf(_T("%s"), get_help());
		quit();
	}

	if(arguments.debug) {
		_ftprintf(stderr, _T("Debug log is enabled.\n"));
	}

	if(arguments.version == TRUE) {
		_tprintf(_T("%s"), get_version());
		quit();
	}

	if(arguments.service == TRUE) {
		result = servicize();
		if(result != 0) {
			_ftprintf(stderr, _T("Unable to install as service.\n"));
		}
		quit();
	}

	if(arguments.persistent == TRUE) {
		result = persist();
		if(result != 0) {
			_ftprintf(stderr, _T("An occurred when running persistent.\n"));
		}
		quit();
	}

	

	return 0;
}
