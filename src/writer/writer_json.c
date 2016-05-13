#include <stdio.h>
#include <stdlib.h>

#include "writer_json.h"

struct json_data
{
	int followingItem, followingSection, followingKeyVal;
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
	((struct json_data*)log->moduleData)->followingItem = 0;
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

int json_start_dict(log_t *log, const TCHAR *name)
{
	if(log->section == NULL) {
		return -1;
	}
	if(((struct json_data*)log->moduleData)->followingSection == 1) {
		_ftprintf(log->file, _T(",\n\t\"%s\": ["), log->section);
	} else {
		_ftprintf(log->file, _T("\n\t\"%s\": ["), log->section);
	}
	return 0;
}

int json_close_dict(log_t *log)
{
	_ftprintf(log->file, _T("\n\t]"));
	((struct json_data*)log->moduleData)->followingSection = 1;
	((struct json_data*)log->moduleData)->followingItem = 0;
	((struct json_data*)log->moduleData)->followingKeyVal = 0;
	return 0;
}

int json_start_list(log_t *log)
{
	if(((struct json_data*)log->moduleData)->followingItem == 1) {
		_ftprintf(log->file, _T(",\n\t\t{"));
	} else {
		_ftprintf(log->file, _T("\n\t\t{"));
	}
	return 0;
}

int json_close_list(log_t *log)
{
	_ftprintf(log->file, _T("\n\t\t}"));
	((struct json_data*)log->moduleData)->followingItem = 1;
	((struct json_data*)log->moduleData)->followingKeyVal = 0;
	return 0;
}

int json_add_value(log_t *log, const TCHAR *key, const TCHAR *value)
{
	if(((struct json_data*)log->moduleData)->followingKeyVal == 1) {
		_ftprintf(log->file, _T(",\n\t\t\t\"%s\": \"%s\""), key, value, key);
	} else {
		_ftprintf(log->file, _T("\n\t\t\t\"%s\": \"%s\""), key, value, key);
	}
	((struct json_data*)log->moduleData)->followingKeyVal = 1;
	return 0;
}
