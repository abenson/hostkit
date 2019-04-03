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
	arguments.writer = _T("json");
	arguments.persistent = FALSE;
	arguments.service = FALSE;
	arguments.verbose = FALSE;
	arguments.debug = FALSE;
	arguments.log = stderr;
	arguments.pipe = _T("hkadmin");
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

	/* If no mode is specified and we're not persistent, default to standard. */
	if(arguments.mode == RM_NONE && arguments.persistent == FALSE) {
		arguments.mode = RM_STANDARD;
	}

	return ARGS_OK;
}

_TCHAR* get_help(void)
{
	return
	_T("Standalone options:\n")
	_T("   /basic                Basic run mode.\n")
	_T("   /standard             Standard run mode. Default.\n")
	_T("   /full                 Full run mode.\n")
	_T("   /filename <name>      Filename to write results to. Default is hostname.\n")
	_T("   /writer <name>        Writer to use. Default is 'json'. Choose 'list' for available writers\n")
	_T("\n")
	_T("Persistent options\n")
	_T("   /persist              Do not run automatically, but wait for instructions from the named pipe.\n")
	_T("   /server <server>      Call back to a server for instructions. Disables default persist pipe.\n")
	_T("   /pipe <name>          Creates a named pipe.\n")
	_T("\n")
	_T("Common options:\n")
	_T("   /service              Install self and run as a service.\n")
	_T("   /verbose              Increases verbosity for logging.\n")
	_T("   /debug                Enables debug output.\n")
	_T("   /log <name>           Name of log. Defaults to stderr.\n")
	_T("\n")
	_T("Other options:\n")
	_T("   /help                This message.\n")
	_T("   /version             Display version.\n");
}

int parse_arguments(char *argv[])
{
	int i = 1;
	while(argv[i] != NULL) {
		if(strcmp(argv[i], "/help") == 0) {
			arguments.error = TRUE;
		} else if(strcmp(argv[i], "/version") == 0) {
			arguments.version = TRUE;
		} else if(strcmp(argv[i], "/basic") == 0) {
			arguments.mode = RM_BASIC;
		} else if(strcmp(argv[i], "/standard") == 0) {
			arguments.mode = RM_STANDARD;
		} else if(strcmp(argv[i], "/full") == 0) {
			arguments.mode = RM_FULL;
		} else if(strcmp(argv[i], "/filename") == 0) {
			if(argv[i+1] == NULL || strlen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.filename = dupe2tchar(argv[i+1]);
			}
			i++;
		} else if(strcmp(argv[i], "/writer") == 0) {
			if(argv[i+1] == NULL || strlen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.writer = dupe2tchar(argv[i+1]);
			}
			i++;
		} else if(strcmp(argv[i], "/persist") == 0) {
			arguments.persistent = TRUE;
		} else if(strcmp(argv[i], "/server") == 0) {
			if(argv[i+1] == NULL || strlen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.server = dupe2tchar(argv[i+1]);
			}
			i++;
		} else if(strcmp(argv[i], "/pipe") == 0) {
			if(argv[i+1] == NULL || strlen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.pipe = dupe2tchar(argv[i+1]);
			}
			i++;
		} else if(strcmp(argv[i], "/service") == 0) {
			arguments.service = TRUE;
		} else if(strcmp(argv[i], "/verbose") == 0) {
			arguments.verbose = TRUE;
		} else if(strcmp(argv[i], "/debug") == 0) {
			arguments.debug = TRUE;
		} else if(strcmp(argv[i], "/log") == 0) {
			if(argv[i+1] == NULL || strlen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.log = fopen(argv[i+1], "w+");
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
