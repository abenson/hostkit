#include <stdio.h>
#include <stdlib.h>

#include "writer_xml.h"

int xml_begin(log_t *log)
{
	fwprintf(log->file, L"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<results>\n");
	return 0;
}

int xml_end(log_t *log)
{
	fwprintf(log->file, L"</results>\n");
	return 0;
}

int xml_open_section(log_t *log, const wchar_t *name)
{
	fwprintf(log->file, L"%*ls<%ls>\n", log->indentLevel * 3, L" ", log->section);
	return 0;
}

int xml_close_section(log_t *log)
{
	fwprintf(log->file, L"%*ls</%ls>\n", log->indentLevel * 3, L" ", log->section);
	return 0;
}

int xml_start_itemlist(log_t *log, const wchar_t *name)
{
	fwprintf(log->file, L"%*ls<%ls>\n", log->indentLevel *3, L" ", log->itemlistName);
	return 0;
}

int xml_start_itemlist_item(log_t *log, const wchar_t *name)
{

	fwprintf(log->file, L"%*ls<%ls>\n", log->indentLevel * 3, L" ", log->itemlistItemName);
	return 0;
}

int xml_end_itemlist_item(log_t *log)
{
	fwprintf(log->file, L"%*ls</%ls>\n", log->indentLevel * 3, L" ", log->itemlistItemName);
	return 0;
}

int xml_end_itemlist(log_t *log)
{
	fwprintf(log->file, L"%*ls</%ls>\n", log->indentLevel *3, L" ", log->itemlistName);
	return 0;
}

int xml_add_value(log_t *log, const wchar_t *key, const wchar_t *value)
{
	int i;
	fwprintf(log->file, L"%*ls<%ls>", log->indentLevel * 3, L" ", key);

	for(i=0; value[i]; i++) {
		if(value[i] == 0x09 || value[i] == 0x0A	|| value[i] == 0x0D
			|| (0x20 <= value[i] && value[i] <= 0xD7FF)
			|| (0xE000 <= value[i] && value[i] <= 0xFFFD)
			|| (0x10000 <= value[i] && value[i] <= 0x10FFFF)) {
			switch(value[i]) {
				case '<':
					fwprintf(log->file, L"&lt;");
					break;
				case '>':
					fwprintf(log->file, L"&gt;");
					break;
				case '&':
					fwprintf(log->file, L"&amp;");
					break;
				case '\'':
					fwprintf(log->file, L"&apos;");
					break;
				case '"':
					fwprintf(log->file, L"&quot;");
					break;
				default:
					fwprintf(log->file, L"%c", value[i]);
			}
		}
	}

	fwprintf(log->file, L"</%ls>\n", key);
	return 0;
}
