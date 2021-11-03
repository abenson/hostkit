#include "common.h"

#include "arguments.h"

#include "writer/writers.h"
#include "util.h"

struct arguments arguments;

void initialize_arguments(void)
{
	arguments.error = 0;
	arguments.version = FALSE;
	arguments.mode = RM_NONE;
	arguments.filename = NULL;
	arguments.file = stdout;
	arguments.writer = L"json";
	arguments.persistent = FALSE;
	arguments.service = FALSE;
	arguments.verbose = FALSE;
	arguments.debug = FALSE;
	arguments.log = stderr;
	arguments.pipe = L"hkadmin";
}

int validate_arguments(void)
{
	if(arguments.error > 0) {
		return ARGS_INVALID;
	}

	/* Check for invalid combinations. */
	if(arguments.mode != RM_NONE && arguments.persistent == TRUE) {
		return ARGS_INVALID;
	}

	/* If no mode is specified and we're not persistent, default to basic. */
	if(arguments.mode == RM_NONE && arguments.persistent == FALSE) {
		arguments.mode = RM_BASIC;
	}

	return ARGS_OK;
}

wchar_t* get_help(void)
{
	return
	L"Standalone options:\n"
	L"   /basic                Basic run mode.\n"
	L"   /standard             Standard run mode. Default.\n"
	L"   /full                 Full run mode.\n"
	L"   /filename <name>      Filename to write results to. Default is hostname.\n"
	L"   /writer <name>        Writer to use. Default is 'json'. Choose 'list' for available writers\n"
	L"\n"
	L"Persistent options\n"
	L"   /persist              Wait for instructions. Requires one or both of /server or /pipe.\n"
	L"   /server <server>      Call back to a server for instructions.\n"
	L"   /pipe <name>          Listen on a named pipe for instructions.\n"
	L"   /service              Install self and run as a service.\n"
	L"\n"
	L"Debug options:\n"
	L"   /verbose              Increases verbosity for logging.\n"
	L"   /debug                Enables debug output.\n"
	L"   /log <name>           Name of log. Defaults to stderr.\n"
	L"\n"
	L"Other options:\n"
	L"   /help                This message.\n"
	L"   /version             Display version.\n";
}

int parse_arguments(wchar_t *argv[])
{
	int i = 1;
	while(argv[i] != NULL) {
		if(wcscmp(argv[i], L"/help") == 0) {
			arguments.error = TRUE;
		} else if(wcscmp(argv[i], L"/version") == 0) {
			arguments.version = TRUE;
		} else if(wcscmp(argv[i], L"/basic") == 0) {
			arguments.mode = RM_BASIC;
		} else if(wcscmp(argv[i], L"/standard") == 0) {
			arguments.mode = RM_STANDARD;
		} else if(wcscmp(argv[i], L"/full") == 0) {
			arguments.mode = RM_FULL;
		} else if(wcscmp(argv[i], L"/filename") == 0) {
			if(argv[i+1] == NULL || wcslen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.filename = dupestr(argv[i+1]);
			}
			i++;
		} else if(wcscmp(argv[i], L"/writer") == 0) {
			if(argv[i+1] == NULL || wcslen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.writer = dupestr(argv[i+1]);
			}
			i++;
		} else if(wcscmp(argv[i], L"/persist") == 0) {
			arguments.persistent = TRUE;
		} else if(wcscmp(argv[i], L"/server") == 0) {
			if(argv[i+1] == NULL || wcslen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.server = dupestr(argv[i+1]);
			}
			i++;
		} else if(wcscmp(argv[i], L"/pipe") == 0) {
			if(argv[i+1] == NULL || wcslen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.pipe = dupestr(argv[i+1]);
			}
			i++;
		} else if(wcscmp(argv[i], L"/service") == 0) {
			arguments.service = TRUE;
		} else if(wcscmp(argv[i], L"/verbose") == 0) {
			arguments.verbose = TRUE;
		} else if(wcscmp(argv[i], L"/debug") == 0) {
			arguments.debug = TRUE;
		} else if(wcscmp(argv[i], L"/log") == 0) {
			if(argv[i+1] == NULL || wcslen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.log = _wfopen(argv[i+1], L"w+");
				if(arguments.log == NULL) {
					arguments.error = 2;
				}
			}
			i++;
		}
		i++;
	}

	return validate_arguments();
}
