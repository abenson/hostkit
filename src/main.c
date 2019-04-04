
#include "common.h"
#include "util.h"
#include "arguments.h"

#include "service.h"
#include "persist.h"

#include "writer/writers.h"

_TCHAR *get_version(void)
{
	return _T("HostKit Agent PREALPHA\nCompiled at ") __TIME__ _T(" on ") __DATE__ _T("\n");
}

_TCHAR *get_copyright(void)
{
	return _T("(C) 2019 HostKit Team\n");
}

int main(int argc, char *argv[])
{
	int result;

	int i = 1;

	initialize_arguments();

	if(parse_arguments(argv) != ARGS_OK || arguments.error) {
		_tprintf(_T("%s"), get_help());
		quit();
	}

	if(arguments.debug) {
		_ftprintf(arguments.log, _T("Debug log is enabled.\n"));
	}

	if(arguments.version == TRUE) {
		_tprintf(_T("%s"), get_version());
		_tprintf(_T("%s"), get_copyright());
		quit();
	}

	if(arguments.service == TRUE) {
		result = servicize();
		if(result != 0) {
			_ftprintf(arguments.log, _T("Unable to install as service.\n"));
		}
		quit();
	}

	if(arguments.persistent == TRUE) {
		result = persist();
		if(result != 0) {
			_ftprintf(arguments.log, _T("An occurred when running persistent.\n"));
		}
		quit();
	}

	if(find_format(arguments.writer) < 0) {
		if(_tcscmp(arguments.writer, _T("list")) == 0) {
			print_formats(arguments.log);
		} else {
			_ftprintf(arguments.log, _T("Invalid writer: %s\n"), arguments.writer);
		}
		quit();
	}

	if(arguments.filename == NULL) {
		scanLog = open_log(_T("-"), arguments.writer);
	} else {
		scanLog = open_log(arguments.filename, arguments.writer);
	}

	if(scanLog == NULL) {
		_ftprintf(arguments.log, _T("Failed to open log.\n"));
		quit();
	}

	if(arguments.mode == RM_BASIC) {
		result = run_basic_scan();
	} else if(arguments.mode == RM_STANDARD) {
		result = run_standard_scan();
	} else if(arguments.mode == RM_FULL) {
		result = run_full_scan();
	}

	close_log(scanLog);

	if(result != 0) {
		_ftprintf(arguments.log, _T("An occurred while running the scans.\n"));
		return result;
	}

	return 0;
}
