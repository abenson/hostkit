#ifndef OUTPUT_H
#define OUTPUT_H

#include "../common.h"

#include "../util.h"

typedef struct log 
{
	FILE *file;
	int format;

	_TCHAR *section;
	_TCHAR *itemlistName;
	_TCHAR *itemlistItemName;
	void *moduleData;

	int indentLevel;

} log_t;

extern log_t *scanLog;

log_t* open_log(const _TCHAR *filename, const _TCHAR *format);

void close_log(log_t *log);

int open_section(log_t *log, const _TCHAR *name);

int close_section(log_t *log);

int start_itemlist(log_t *log, const TCHAR *name);

int start_itemlist_item(log_t *log, const TCHAR *name);

int end_itemlist_item(log_t *log);

int end_itemlist(log_t *log);

int add_value(log_t *log, const _TCHAR *key, const _TCHAR *value);

#endif
