#include "common.h"

#include "arguments.h"
#include "service.h"
#include "persist.h"

_TCHAR *get_version(void)
{
	return _T("HostKit Agent PREALPHA\nCompiled at ") _T(__TIME__) _T(" on ") _T(__DATE__) _T("\n");
}

_TCHAR *get_copyright(void)
{
	return _T("");
}

int _tmain(int argc, _TCHAR *argv[])
{
	int result;

	initialize_arguments();

	if(parse_arguments(argv) != ARGS_OK || arguments.error)
	{
		_tprintf(_T("%s"), get_help());
		quit();
	}

	if(arguments.debug)
	{
		_ftprintf(arguments.logFile, _T("Debug log is enabled.\n"));
	}

	if(arguments.version == TRUE)
	{
		_tprintf(_T("%s"), get_version());
		_tprintf(_T("%s"), get_copyright());
		quit();
	}

	if(arguments.service == TRUE)
	{
		result = servicize();
		if(result != 0)
		{
			_ftprintf(arguments.logFile, _T("Unable to install as service.\n"));
		}
		quit();
	}

	if(arguments.persistent == TRUE)
	{
		result = persist();
		if(result != 0)
		{
			_ftprintf(arguments.logFile, _T("An occurred when running persistent.\n"));
		}
		quit();
	}

	arguments.log = open_log(arguments.filename, arguments.writer);

	if(arguments.mode == RM_BASIC)
	{
		run_basic_scan();
	}
	else if(arguments.mode == RM_STANDARD)
	{
		run_standard_scan();
	}
	else if(arguments.mode == RM_FULL)
	{
		run_full_scan();
	}

	close_log(arguments.log);

	return 0;
}
