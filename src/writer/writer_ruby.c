#include <stdio.h>
#include <stdlib.h>

#include "writer_json.h"

int ruby_begin(log_t *log)
{
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
	_ftprintf(log->file, _T(" :%s => {"), log->section);
	return 0;
}

int ruby_close_dict(log_t *log)
{
	_ftprintf(log->file, _T(" }, "));
	return 0;
}

int ruby_start_list(log_t *log)
{
	_ftprintf(log->file, _T(" :%s => ["), log->section);
	return 0;
}

int ruby_close_list(log_t *log)
{
	_ftprintf(log->file, _T(" ], "));
	return 0;
}

int ruby_add_value(log_t *log, const TCHAR *key, const TCHAR *value)
{
	_ftprintf(log->file, _T(":%s => \"%s\", "), key, value, key);
	return 0;
}
