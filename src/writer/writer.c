#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "writer.h"
#include "writers.h"

static void add_section(log_t *log, const TCHAR *name)
{
	const TCHAR **newlist;
	const TCHAR *value;

	newlist = realloc(log->sections, sizeof(*newlist) * log->indentLevel+1);
	if(newlist) {
		log->sections = newlist;
	}
	log->sections[log->indentLevel] = dupestr(name);
	log->section = log->sections[log->indentLevel];

	log->indentLevel++;
}

static void pop_section(log_t *log)
{
	const TCHAR **newlist;
	const TCHAR *value;

	free((TCHAR*)log->sections[log->indentLevel]);
	log->sections[log->indentLevel] = NULL;

	log->indentLevel--;

	newlist = realloc(log->sections, sizeof(*newlist) * log->indentLevel+1);
	if(newlist) {
		log->sections = newlist;
		log->section = log->sections[log->indentLevel];
	} else {
		_ftprintf(log->file, _T("This explains a lot."));
	}
}

static void debug_sections(log_t *log)
{
	int i;
	_ftprintf(log->file, _T("DEBUG: "));
	if(log->sections == NULL) {
		_ftprintf(log->file, _T("Empty\n"));
		return;
	}
	for(i=0; i<log->indentLevel; i++) {
		if(log->sections[i] == NULL) {
			_ftprintf(log->file, _T("NULL"));
			break;
		}
		_ftprintf(log->file, _T("%s, "), log->sections[i]);
	}
	_ftprintf(log->file, _T("\n"));
}

log_t* open_log(const _TCHAR *filename, const _TCHAR *format)
{
	log_t *log;
	int fmtIndex;
	errno_t _err;

	fmtIndex = find_format(format);
	if(fmtIndex < 0) { return NULL; }

	log = malloc(sizeof(*log));

	if(log)
	{
		log->indentLevel = 0;
		log->sections = NULL;
		log->section = NULL;
		if(_tcscmp(filename, _T("-")) == 0)
		{
			log->file = stdout;
		}
		else
		{
			log->file = _tfopen(filename, _T("w+"));
		}

		if(log->file)
		{
			log->format = fmtIndex;
			modules[log->format].begin(log);
			return log;
		}
		free(log);
	}
	return NULL;
}

void close_log(log_t *log)
{
	modules[log->format].end(log);

	if(log->file != stdout)
	{
		fclose(log->file);
	}

	free(log);
}

int start_dict(log_t *log, const _TCHAR *name)
{
	int value;
	add_section(log, name);
	value = modules[log->format].start_dict(log);
	return value;
}

int close_dict(log_t *log)
{
	int value;
	value = modules[log->format].close_dict(log);
	pop_section(log);
	return value;
}

int start_list(log_t *log, const TCHAR *name)
{
	int value;
	add_section(log, name);
	value = modules[log->format].start_list(log);
	return value;
}

int close_list(log_t *log)
{
	int value;
	value = modules[log->format].close_list(log);
	pop_section(log);
	return value;
}

int add_value(log_t *log, const _TCHAR *key, const _TCHAR *value)
{
	int ret;
	log->indentLevel++;
	ret = modules[log->format].add_value(log, key, value);
	log->indentLevel--;
	return ret;
}

