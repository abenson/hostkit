#ifndef OUTPUT_H
#define OUTPUT_H

#include "../common.h"

#include "../util.h"

typedef struct log 
{
	FILE *file;
	int format;

	_TCHAR *section;
	void *moduleData;

} log_t;

log_t* open_log(const _TCHAR *filename, const _TCHAR *format);

void close_log(log_t *log);

int open_section(log_t *log, const _TCHAR *name);

int close_section(log_t *log);

int open_item(log_t *log);

int close_item(log_t *log);

int add_value(log_t *log, const _TCHAR *key, const _TCHAR *value);

#endif
