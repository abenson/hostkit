#include <stdio.h>
#include <stdlib.h>

#include "writers/writer_json.h"

/* Helper functions */

static int escape_json(FILE *fp, const TCHAR *str)
{
	int i=0;

	while(str[i]) {
		switch(str[i]) {
			case '\b':
				_ftprintf(fp, _T("%s"), _T("\\b"));
				break;
			case '\f':
				_ftprintf(fp, _T("%s"), _T("\\f"));
				break;
			case '\n':
				_ftprintf(fp, _T("%s"), _T("\\n"));
				break;
			case '\r':
				_ftprintf(fp, _T("%s"), _T("\\r"));
				break;
			case '\t':
				_ftprintf(fp, _T("%s"), _T("\\t"));
				break;
			case '\"':
				_ftprintf(fp, _T("%s"), _T("\\\""));
				break;
			case '\\':
				_ftprintf(fp, _T("%s"), _T("\\\\"));
				break;
			default:
				_ftprintf(fp, _T("%c"), str[i]);
				break;
		}
		i++;
	}

	return i;
}

struct json_data
{
	int firstItem[512];
	int inDict[512];
};

int json_begin(log_t *log)
{
	struct json_data *data;
	data = malloc(sizeof(*data));
	if(data == NULL) {
		return -1;
	}
	memset(data, 0, sizeof(*data));
	log->moduleData = data;

	((struct json_data*)log->moduleData)->firstItem;
	((struct json_data*)log->moduleData)->inDict[0] = 1;

	_ftprintf(log->file, _T("{ "));
	return 0;
}

int json_end(log_t *log)
{
	free(log->moduleData);
	_ftprintf(log->file, _T(" }\n"));
	return 0;
}

int json_start_dict(log_t *log)
{
	if(log->section == NULL) {
		return -1;
	}
	if(((struct json_data*)log->moduleData)->firstItem[log->indentLevel-1] == 1) {
		_ftprintf(log->file, _T(", "));
	}
	if(((struct json_data*)log->moduleData)->inDict[log->indentLevel-1] == 1) {
		_ftprintf(log->file, _T("\"%s\":"), log->section);
	}
	_ftprintf(log->file, _T(" {"));
	((struct json_data*)log->moduleData)->firstItem[log->indentLevel-1] = 1;
	((struct json_data*)log->moduleData)->inDict[log->indentLevel] = 1;
	return 0;
}

int json_close_dict(log_t *log)
{
	_ftprintf(log->file, _T(" } "));
	((struct json_data*)log->moduleData)->firstItem[log->indentLevel] = 0;
	((struct json_data*)log->moduleData)->inDict[log->indentLevel] = 0;
	return 0;
}

int json_start_list(log_t *log)
{
	if(((struct json_data*)log->moduleData)->firstItem[log->indentLevel-1] == 1) {
		_ftprintf(log->file, _T(", "));
	}
	if(((struct json_data*)log->moduleData)->inDict[log->indentLevel-1] == 1) {
		_ftprintf(log->file, _T("\"%s\":"), log->section);
	}
	_ftprintf(log->file, _T(" ["));
	((struct json_data*)log->moduleData)->firstItem[log->indentLevel-1] = 1;
	((struct json_data*)log->moduleData)->inDict[log->indentLevel] = 0;
	return 0;
}

int json_close_list(log_t *log)
{
	_ftprintf(log->file, _T(" ] "));
	((struct json_data*)log->moduleData)->inDict[log->indentLevel] = 0;
	((struct json_data*)log->moduleData)->firstItem[log->indentLevel] = 0;
	return 0;
}

int json_add_value(log_t *log, const TCHAR *key, const TCHAR *value)
{
	if(((struct json_data*)log->moduleData)->firstItem[log->indentLevel-1] == 1) {
		_ftprintf(log->file, _T(", \"%s\": \""), key);
		escape_json(log->file, value);
		_ftprintf(log->file, _T("\" "));
	} else {
		_ftprintf(log->file, _T("  \"%s\": \""), key);
		escape_json(log->file, value);
		_ftprintf(log->file, _T("\" "));
	}
	((struct json_data*)log->moduleData)->firstItem[log->indentLevel-1] = 1;
	return 0;
}
