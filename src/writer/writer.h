#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>

typedef struct log 
{
	FILE *file;
	int format;

	char *section;
	void *moduleData;

} log_t;

log_t* open_log(const char *filename, const char *format);

void close_log(log_t *log);

int open_section(log_t *log, const char *name);

int close_section(log_t *log);

int open_item(log_t *log);

int close_item(log_t *log);

int add_value(log_t *log, const char *key, const char *value);

#endif