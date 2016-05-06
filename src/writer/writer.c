#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "writer.h"
#include "writers.h"

log_t* open_log(const _TCHAR *filename, const _TCHAR *format)
{
	log_t *log;
	int fmtIndex;
	errno_t _err;

	fmtIndex = find_format(format);
	if(fmtIndex < 0) { return NULL; }

	log = (log_t *) malloc(sizeof(*log));

	if(log)
	{
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

int open_section(log_t *log, const _TCHAR *name)
{
	log->section = dupestr(name);

	return modules[log->format].open_section(log, log->section);
}

int close_section(log_t *log)
{
	int value;
	value = modules[log->format].close_section(log);
	free(log->section);
	return value;
}

int open_item(log_t *log)
{
	return modules[log->format].open_item(log);
}

int close_item(log_t *log)
{
	return modules[log->format].close_item(log);
}

int add_value(log_t *log, const _TCHAR *key, const _TCHAR *value)
{
	return modules[log->format].add_value(log, key, value);
}
