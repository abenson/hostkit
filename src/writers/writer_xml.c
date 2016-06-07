#include <stdio.h>
#include <stdlib.h>

#include "writers/writer_xml.h"

static void indent(FILE *file, int level)
{
	int i;
	for(i=0; i<level; i++) {
		_ftprintf(file, _T("   "));
	}
}

static void xml_tag_open(log_t *log)
{
	indent(log->file, log->indentLevel);
	_ftprintf(log->file, _T("<%s>\n"), log->section);
}

static void xml_tag_close(log_t *log)
{
	indent(log->file, log->indentLevel);
	_ftprintf(log->file, _T("</%s>\n"), log->section);
}

int xml_begin(log_t *log)
{
	_ftprintf(log->file, _T("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<results>\n"));
	return 0;
}

int xml_end(log_t *log)
{
	_ftprintf(log->file, _T("</results>\n"));
	return 0;
}

int xml_start_dict(log_t *log)
{
	xml_tag_open(log);
	return 0;
}

int xml_close_dict(log_t *log)
{
	xml_tag_close(log);
	return 0;
}

int xml_start_list(log_t *log)
{
	xml_tag_open(log);
	return 0;
}

int xml_close_list(log_t *log)
{
	xml_tag_close(log);
	return 0;
}

int xml_add_value(log_t *log, const _TCHAR *key, const _TCHAR *value)
{
	indent(log->file, log->indentLevel);
	_ftprintf(log->file, _T("<%s>%s</%s>\n"), key, value, key);
	return 0;
}
