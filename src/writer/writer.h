#ifndef OUTPUT_H
#define OUTPUT_H

#include "../common.h"

#include "../util.h"

typedef struct log 
{
	FILE *file;
	int format;

	wchar_t *section;
	wchar_t *itemlistName;
	wchar_t *itemlistItemName;
	void *moduleData;

	int indentLevel;

} log_t;

extern log_t *scanLog;

log_t* open_log(const wchar_t *filename, const wchar_t *format);

void close_log(log_t *log);

int open_section(log_t *log, const wchar_t *name);

int close_section(log_t *log);

int start_itemlist(log_t *log, const wchar_t *name);

int start_itemlist_item(log_t *log, const wchar_t *name);

int end_itemlist_item(log_t *log);

int end_itemlist(log_t *log);

int add_value(log_t *log, const wchar_t *key, const wchar_t *value);

#endif
