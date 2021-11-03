
#include "common.h"
#include "util.h"
#include "arguments.h"

#include "service.h"
#include "persist.h"

#include "writer/writers.h"

wchar_t *get_version(void)
{
	return L"HostKit Agent PREALPHA\nCompiled at " __TIME__ L" on " __DATE__ L"\n";
}

wchar_t *get_copyright(void)
{
	return L"(C) 2019 HostKit Team\n";
}

int wmain(int argc, wchar_t *argv[])
{
	int result;

	initialize_arguments();

	if(parse_arguments(argv) != ARGS_OK || arguments.error) {
		wprintf(L"%ls", get_help());
		quit();
	}

	if(arguments.debug) {
		fwprintf(arguments.log, L"Debug log is enabled.\n");
	}

	if(arguments.version == TRUE) {
		wprintf(L"%ls", get_version());
		wprintf(L"%ls", get_copyright());
		quit();
	}

	if(arguments.service == TRUE) {
		result = servicize();
		if(result != 0) {
			fwprintf(arguments.log, L"Unable to install as service.\n");
		}
		quit();
	}

	if(arguments.persistent == TRUE) {
		result = persist();
		if(result != 0) {
			fwprintf(arguments.log, L"An occurred when running persistent.\n");
		}
		quit();
	}

	if(find_format(arguments.writer) < 0) {
		if(wcscmp(arguments.writer, L"list") == 0) {
			print_formats(arguments.log);
		} else {
			fwprintf(arguments.log, L"Invalid writer: %s\n", arguments.writer);
		}
		quit();
	}

	if(arguments.filename == NULL) {
		scanLog = open_log(L"-", arguments.writer);
	} else {
		scanLog = open_log(arguments.filename, arguments.writer);
	}

	if(scanLog == NULL) {
		fwprintf(arguments.log, L"Failed to open log.\n");
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
		fwprintf(arguments.log, L"An occurred while running the scans.\n");
		return result;
	}

	return 0;
}
