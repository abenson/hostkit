#include <stdio.h>
#include <stdlib.h>

#include "writer_json.h"

enum {
	ST_NONE,
	ST_LIST,
	ST_DICT
};

struct ruby_data {
	int sectionType[512];
};

int ruby_begin(log_t *log)
{
	struct ruby_data *data;
	data = malloc(sizeof(*data));
	if(data == NULL) {
		return -1;
	}
	memset(data, 0, sizeof(struct ruby_data));
	log->moduleData = data;
	((struct ruby_data*)log->moduleData)->sectionType[log->indentLevel] = ST_DICT;

	_ftprintf(log->file, _T("{ "));
	return 0;
}

int ruby_end(log_t *log)
{
	_ftprintf(log->file, _T(" }\n"));
	return 0;
}

int ruby_start_dict(log_t *log)
{
	if(log->section == NULL) {
		return -1;
	}
	if(((struct ruby_data*)log->moduleData)->sectionType[log->indentLevel-1] == ST_DICT) {
		_ftprintf(log->file, _T(" :%s => {"), log->section);
	} else {
		_ftprintf(log->file, _T(" {"), log->section);
	}
	((struct ruby_data*)log->moduleData)->sectionType[log->indentLevel] = ST_DICT;
	return 0;
}

int ruby_close_dict(log_t *log)
{
	_ftprintf(log->file, _T(" }, "));
	return 0;
}

int ruby_start_list(log_t *log)
{
	if(((struct ruby_data*)log->moduleData)->sectionType[log->indentLevel-1] == ST_DICT) {
		_ftprintf(log->file, _T(" :%s => ["), log->section);
	} else {
		_ftprintf(log->file, _T(" ["), log->section);
	}
	((struct ruby_data*)log->moduleData)->sectionType[log->indentLevel] = ST_LIST;
	return 0;
}

int ruby_close_list(log_t *log)
{
	_ftprintf(log->file, _T(" ], "));
	return 0;
}

int ruby_add_value(log_t *log, const TCHAR *key, const TCHAR *value)
{
	if(((struct ruby_data*)log->moduleData)->sectionType[log->indentLevel-1] == ST_DICT) {
		_ftprintf(log->file, _T(":%s => \"%s\", "), key, value, key);
	} else {
		_ftprintf(log->file, _T("{ :%s => \"%s\" }, "), key, value, key);
	}
	return 0;
}
