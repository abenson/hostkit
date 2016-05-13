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

	TCHAR *section;
	void *moduleData;

} log_t;

log_t* open_log(const TCHAR *filename, const TCHAR *format);

void close_log(log_t *log);

int open_section(log_t *log, const TCHAR *name);

int close_section(log_t *log);

int open_item(log_t *log);

int close_item(log_t *log);

int add_value(log_t *log, const TCHAR *key, const TCHAR *value);

#endif
