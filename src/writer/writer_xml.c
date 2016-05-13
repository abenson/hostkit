#include <stdio.h>
#include <stdlib.h>

#include "writer_xml.h"

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

int xml_start_dict(log_t *log, const _TCHAR *name)
{
	_ftprintf(log->file, _T("   <%s>\n"), log->section);
	return 0;
}

int xml_close_dict(log_t *log)
{
	_ftprintf(log->file, _T("   </%s>\n"), log->section);
	return 0;
}

int xml_start_list(log_t *log)
{
	_ftprintf(log->file, _T("      <item>\n"));
	return 0;
}

int xml_close_list(log_t *log)
{
	_ftprintf(log->file, _T("      </item>\n"));
	return 0;
}

int xml_add_value(log_t *log, const _TCHAR *key, const _TCHAR *value)
{
	_ftprintf(log->file, _T("          <%s>%s</%s>\n"), key, value, key);
	return 0;
}
