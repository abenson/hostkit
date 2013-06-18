#include "common.h"

#include "arguments.h"

#include "writer/writers.h"

struct arguments arguments;

void initialize_arguments(void)
{
	arguments.error = 0;
	arguments.version = FALSE;
	arguments.mode = RM_NONE;
	arguments.filename = _T("-");
	arguments.writer = _T("json");
	arguments.persistent = FALSE;
	arguments.service = FALSE;
	arguments.verbose = FALSE;
	arguments.debug = FALSE;
	arguments.logFile = stderr;
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
	} else {
		arguments.log = open_log(arguments.filename, arguments.writer);
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
_T("   /filename <name>      Filename to write results to. Default is standard output.\n")
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

int parse_arguments(_TCHAR *argv[])
{
	int i = 0;
	while(argv[i] != NULL) {
		if(_tcscmp(argv[i], _T("/help")) == 0) {
			arguments.error = TRUE;
		} else if(_tcscmp(argv[i], _T("/version")) == 0) {
			arguments.version = TRUE;
		} else if(_tcscmp(argv[i], _T("/basic")) == 0) {
			arguments.mode = RM_BASIC;
		} else if(_tcscmp(argv[i], _T("/standard")) == 0) {
			arguments.mode = RM_STANDARD;
		} else if(_tcscmp(argv[i], _T("/full")) == 0) {
			arguments.mode = RM_FULL;
		} else if(_tcscmp(argv[i], _T("/filename")) == 0) {
			if(argv[i+1] == NULL || _tcslen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.filename = dupestr(argv[i+1]);
			}
			i++;
		} else if(_tcscmp(argv[i], _T("/writer")) == 0) {
			if(argv[i+1] == NULL || _tcslen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.writer = find_format(argv[i+1]);
			}
			i++;
		} else if(_tcscmp(argv[i], _T("/persist")) == 0) {
			arguments.persistent = TRUE;
		} else if(_tcscmp(argv[i], _T("/server")) == 0) {
			if(argv[i+1] == NULL || _tcslen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.server = dupestr(argv[i+1]);
			}
			i++;
		} else if(_tcscmp(argv[i], _T("/pipe")) == 0) {
			if(argv[i+1] == NULL || _tcslen(argv[i+1]) == 0) {
				arguments.error = 1;
			} else {
				arguments.pipe = dupestr(argv[i+1]);
			}
			i++;
		} else if(_tcscmp(argv[i], _T("/service")) == 0) {
			arguments.service = TRUE;
		} else if(_tcscmp(argv[i], _T("/verbose")) == 0) {
			arguments.verbose = TRUE;
		} else if(_tcscmp(argv[i], _T("/debug")) == 0) {
			arguments.debug = TRUE;
		} else if(_tcscmp(argv[i], _T("/log")) == 0) 
		{
			if(argv[i+1] == NULL || _tcslen(argv[i+1]) == 0) 
			{
				arguments.error = 1;
			} 
			else 
			{
				_tfopen_s(&arguments.logFile, argv[i + 1], _T("w+"));
				if(arguments.log == NULL) 
				{
					arguments.error = 2;
				}
			}
			i++;
		}
		i++;
	}

	return validate_arguments();
}
