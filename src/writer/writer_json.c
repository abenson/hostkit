#include <stdio.h>
#include <stdlib.h>

#include "writer_json.h"

struct json_data
{
	int followingSection, followingKeyVal;
};

int json_begin(log_t *log)
{
	struct json_data *data;
	data = malloc(sizeof(*data));
	if(data == NULL) {
		return -1;
	}
	log->moduleData = data;
	((struct json_data*)log->moduleData)->followingSection = 0;
	((struct json_data*)log->moduleData)->followingKeyVal = 0;
	_ftprintf(log->file, _T("{\n"));
	return 0;
}

int json_end(log_t *log)
{
	free(log->moduleData);
	_ftprintf(log->file, _T("\n}\n"));
	return 0;
}

int json_open_section(log_t *log, const _TCHAR *name)
{
	if(((struct json_data*)log->moduleData)->followingSection == 1) {
		_ftprintf(log->file, _T(",\n    \"%s\": {"), name);
	} else {
		_ftprintf(log->file, _T("   \"%s\": {"), name);
	}
	return 0;
}

int json_close_section(log_t *log)
{
	_ftprintf(log->file, _T("\n   }"));
	((struct json_data*)log->moduleData)->followingSection = 1;
	((struct json_data*)log->moduleData)->followingKeyVal = 0;
	return 0;
}

int json_add_value(log_t *log, const _TCHAR *key, const _TCHAR *value)
{
	if(((struct json_data*)log->moduleData)->followingKeyVal == 1) {
		_ftprintf(log->file, _T(",\n      \"%s\": \"%s\""), key, value, key);
	} else {
		_ftprintf(log->file, _T("\n      \"%s\": \"%s\""), key, value, key);
	}
	((struct json_data*)log->moduleData)->followingKeyVal = 1;
	return 0;
}
