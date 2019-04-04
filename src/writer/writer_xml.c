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
	int i;
	_ftprintf(log->file, _T("%*s<%s>"), (log->indentLevel-1) * 3, _T(" "), key);

	for(i=0; value[i]; i++) {
		if(value[i] == 0x09 || value[i] == 0x0A	|| value[i] == 0x0D
			|| 0x20 <= value[i] && value[i] <= 0xD7FF
			|| 0xE000 <= value[i] && value[i] <= 0xFFFD
			|| 0x10000 <= value[i] && value[i] <= 0x10FFFF) {
			switch(value[i]) {
				case '<':
					_ftprintf(log->file, _T("&lt;"));
					break;
				case '>':
					_ftprintf(log->file, _T("&gt;"));
					break;
				case '&':
					_ftprintf(log->file, _T("&amp;"));
					break;
				case '\'':
					_ftprintf(log->file, _T("&apos;"));
					break;
				case '"':
					_ftprintf(log->file, _T("&quot;"));
					break;
				default:
					_ftprintf(log->file, _T("%c"), value[i]);
			}
		}
	}

	_ftprintf(log->file, _T("</%s>\n"), key);
	return 0;
}
