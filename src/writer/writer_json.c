#include <stdio.h>
#include <stdlib.h>

#include "writer_json.h"

struct json_data
{
	int followingSection, followingKeyVal, inItemList;
};

int json_begin(log_t *log)
{
	struct json_data *data;
	data = malloc(sizeof(*data));
	if(data == NULL) {
		return -1;
	}
	log->moduleData = data;
	((struct json_data*)log->moduleData)->followingSection = 0;
	((struct json_data*)log->moduleData)->followingKeyVal = 0;
	((struct json_data*)log->moduleData)->inItemList = 0;
	fwprintf(log->file, L"{\n");
	return 0;
}

int json_end(log_t *log)
{
	free(log->moduleData);
	fwprintf(log->file, L"\n}\n");
	return 0;
}

int json_open_section(log_t *log, const wchar_t *name)
{
	if(((struct json_data*)log->moduleData)->followingSection == 1) {
		fwprintf(log->file, L",\n%*ls\"%ls\": {", log->indentLevel * 3, L" ", name);
	} else {
		fwprintf(log->file, L"%*ls\"%ls\": {", log->indentLevel * 3, L" ", name);
	}
	return 0;
}

int json_close_section(log_t *log)
{
	fwprintf(log->file, L"\n%*ls}", log->indentLevel * 3, L" ");
	((struct json_data*)log->moduleData)->followingSection = 1;
	((struct json_data*)log->moduleData)->followingKeyVal = 0;
	return 0;
}

int json_start_itemlist(log_t *log, const wchar_t *name)
{
	if(((struct json_data*)log->moduleData)->followingSection == 1) {
		fwprintf(log->file, L",\n%*ls\"%ls\": [", log->indentLevel * 3, L" ", name);
	} else {
		fwprintf(log->file, L"%*ls\"%ls\": [", log->indentLevel * 3, L" ", name);
	}
	return 0;
}

int json_start_itemlist_item(log_t *log, const wchar_t *name)
{
	if(((struct json_data*)log->moduleData)->inItemList == 1) {
		fwprintf(log->file, L",\n%*ls{",log->indentLevel * 3, L" ");
	} else {
		fwprintf(log->file, L"\n%*ls{", log->indentLevel * 3, L" ");
	}
	((struct json_data*)log->moduleData)->inItemList = 1;
	((struct json_data*)log->moduleData)->followingSection = 0;
	((struct json_data*)log->moduleData)->followingKeyVal = 0;
	return 0;
}

int json_end_itemlist_item(log_t *log)
{
	fwprintf(log->file, L"\n%*ls}", log->indentLevel * 3, L" ");
	return 0;
}

int json_end_itemlist(log_t *log)
{
	fwprintf(log->file, L"\n%*ls]", log->indentLevel * 3, L" ");
	((struct json_data*)log->moduleData)->inItemList = 0;
	return 0;
}

int json_add_value(log_t *log, const wchar_t *key, const wchar_t *value)
{
	int i;
	if(((struct json_data*)log->moduleData)->followingKeyVal == 1) {
		fwprintf(log->file, L",");
	}

	fwprintf(log->file, L"\n%*ls\"%ls\": \"", log->indentLevel * 3, L" ", key);

	for(i=0; value[i]; i++) {
		switch(value[i]) {
			case L'"':
				fwprintf(log->file, L"%ls", L"\"");
				break;
			case L'\\':
				fwprintf(log->file, L"%ls", L"\\\\");
				break;
			case L'/':
				fwprintf(log->file, L"%ls", L"\\/");
				break;
			case L'\b':
				fwprintf(log->file, L"%ls", L"\\b");
				break;
			case L'\f':
				fwprintf(log->file, L"%ls", L"\\f");
				break;
			case L'\n':
				fwprintf(log->file, L"%ls", L"\\n");
				break;
			case L'\r':
				fwprintf(log->file, L"%ls", L"\\r");
				break;
			case L'\t':
				fwprintf(log->file, L"%ls", L"\\t");
				break;
			default:
				if(__isascii(value[i])) {
					fwprintf(log->file, L"%c", value[i]);
				} else {
					fwprintf(log->file, L"%04d", value[i]);
				}
		}
	}

	fwprintf(log->file, L"\"");

	((struct json_data*)log->moduleData)->followingKeyVal = 1;
	return 0;
}
