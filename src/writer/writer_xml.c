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

int xml_open_section(log_t *log, const _TCHAR *name)
{
	_ftprintf(log->file, _T("%*s<%s>\n"), log->indentLevel * 3, _T(" "), log->section);
	return 0;
}

int xml_close_section(log_t *log)
{
	_ftprintf(log->file, _T("%*s</%s>\n"), log->indentLevel * 3, _T(" "), log->section);
	return 0;
}

int xml_start_itemlist(log_t *log, const TCHAR *name)
{
	_ftprintf(log->file, _T("%*s<%s>\n"), (log->indentLevel-1) * 3, _T(" "), log->itemlistName);
	return 0;
}

int xml_start_itemlist_item(log_t *log)
{

	_ftprintf(log->file, _T("%*s<%s>\n"), (log->indentLevel-1) * 3, _T(" "), log->itemlistName);
	return 0;
}

int xml_end_itemlist_item(log_t *log)
{
	_ftprintf(log->file, _T("%*s</%s>\n"), (log->indentLevel-1) * 3, _T(" "), log->itemlistName);
	return 0;
}

int xml_end_itemlist(log_t *log)
{
	_ftprintf(log->file, _T("%*s</%s>\n"), (log->indentLevel-1) * 3, _T(" "), log->itemlistName);
	return 0;
}

int xml_add_value(log_t *log, const _TCHAR *key, const _TCHAR *value)
{
	_ftprintf(log->file, _T("%*s<%s>%s</%s>\n"), (log->indentLevel-1) * 3, _T(" "), key, value, key);
	return 0;
}
