#ifndef OUTPUT_H
#define OUTPUT_H

#include <windows.h>
#include <tchar.h>

#include <stdio.h>

#include "../common.h"

typedef struct log
{
	FILE *file;
	int format;

	int indentLevel;

	const TCHAR **sections;

	const TCHAR *section;

	void *moduleData;

} log_t;

log_t* open_log(const TCHAR *filename, const TCHAR *format);

void close_log(log_t *log);

int start_dict(log_t *log, const TCHAR *name);

int close_dict(log_t *log);

int start_list(log_t *log, const TCHAR *name);

int close_list(log_t *log);

int add_value(log_t *log, const TCHAR *key, const TCHAR *value);

#endif
