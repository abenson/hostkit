#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "writer.h"
#include "writers.h"

log_t *scanLog;

log_t* open_log(const wchar_t *filename, const wchar_t *format)
{
	log_t *log;
	int fmtIndex;

	fmtIndex = find_format(format);
	if(fmtIndex < 0) { return NULL; }

	log = malloc(sizeof(*log));
	if(log) {
		log->indentLevel = 0;
		if(wcscmp(filename, L"-") == 0) {
			log->file = stdout;
		} else {
			log->file = _wfopen(filename, L"w+");
		}
		if(log->file) {
			log->format = fmtIndex;
			writers[log->format].begin(log);
			return log;
		}
		free(log);
	}
	return NULL;
}

void close_log(log_t *log)
{
	writers[log->format].end(log);
	if(log->file != stdout) {
		fclose(log->file);
	}
	free(log);
}

int open_section(log_t *log, const wchar_t *name)
{
	log->section = dupestr(name);
	log->indentLevel++;
	return writers[log->format].open_section(log, name);
}

int close_section(log_t *log)
{
	int value; 
	value = writers[log->format].close_section(log);
	log->indentLevel--;
	free(log->section);
	return value;
}

int start_itemlist(log_t *log, const wchar_t *name)
{
	log->itemlistName = dupestr(name);
	log->indentLevel++;
	return writers[log->format].start_itemlist(log, name);
}

int start_itemlist_item(log_t *log, const wchar_t *name)
{
	log->indentLevel++;
	log->itemlistItemName = dupestr(name);
	return writers[log->format].start_itemlist_item(log, name);
}

int end_itemlist_item(log_t *log)
{
	int value;
	value = writers[log->format].end_itemlist_item(log);
	log->indentLevel--;
	free(log->itemlistItemName);
	return value;
}

int end_itemlist(log_t *log)
{
	int value; 
	value = writers[log->format].end_itemlist(log);
	log->indentLevel--;
	free(log->itemlistName);
	return value;
}

int add_value(log_t *log, const wchar_t *key, const wchar_t *value)
{
	int retVal;
	log->indentLevel++;
	retVal = writers[log->format].add_value(log, key, value);
	log->indentLevel--;
	return retVal;
}
