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
	_ftprintf(log->file, _T("{\n"));
	return 0;
}

int json_end(log_t *log)
{
	free(log->moduleData);
	_ftprintf(log->file, _T("\n}\n"));
	return 0;
}

int json_open_section(log_t *log, const _TCHAR *name)
{
	if(((struct json_data*)log->moduleData)->followingSection == 1) {
		_ftprintf(log->file, _T(",\n    \"%s\": {"), name);
	} else {
		_ftprintf(log->file, _T("   \"%s\": {"), name);
	}
	return 0;
}

int json_close_section(log_t *log)
{
	_ftprintf(log->file, _T("\n   }"));
	((struct json_data*)log->moduleData)->followingSection = 1;
	((struct json_data*)log->moduleData)->followingKeyVal = 0;
	return 0;
}

int json_start_itemlist(log_t *log, const TCHAR *name)
{
	if(((struct json_data*)log->moduleData)->followingSection == 1) {
		_ftprintf(log->file, _T(",\n    \"%s\": ["), name);
	} else {
		_ftprintf(log->file, _T("   \"%s\": ["), name);
	}
	return 0;
}

int json_start_itemlist_item(log_t *log)
{
	if(((struct json_data*)log->moduleData)->inItemList == 1) {
		_ftprintf(log->file, _T(",\n      {"));
	} else {
		_ftprintf(log->file, _T("\n      {"));
	}
	((struct json_data*)log->moduleData)->inItemList = 1;
	((struct json_data*)log->moduleData)->followingSection = 0;
	((struct json_data*)log->moduleData)->followingKeyVal = 0;
	return 0;
}

int json_end_itemlist_item(log_t *log)
{
	_ftprintf(log->file, _T("\n       }"));
	return 0;
}

int json_end_itemlist(log_t *log)
{
	_ftprintf(log->file, _T("\n       ]"));
	((struct json_data*)log->moduleData)->inItemList = 0;
	return 0;
}

int json_add_value(log_t *log, const _TCHAR *key, const _TCHAR *value)
{
	int i;
	if(((struct json_data*)log->moduleData)->followingKeyVal == 1) {
		_ftprintf(log->file, _T(","));
	}

	_ftprintf(log->file, _T("\n%*s\"%s\": \""), log->indentLevel * 3, _T(" "), key);

	for(i=0; value[i]; i++) {
		switch(value[i]) {
			case _T('"'):
				_ftprintf(log->file, _T("%s"), _T("\""));
				break;
			case _T('\\'):
				_ftprintf(log->file, _T("%s"), _T("\\\\"));
				break;
			case _T('/'):
				_ftprintf(log->file, _T("%s"), _T("\\/"));
				break;
			case _T('\b'):
				_ftprintf(log->file, _T("%s"), _T("\\b"));
				break;
			case _T('\f'):
				_ftprintf(log->file, _T("%s"), _T("\\f"));
				break;
			case _T('\n'):
				_ftprintf(log->file, _T("%s"), _T("\\n"));
				break;
			case _T('\r'):
				_ftprintf(log->file, _T("%s"), _T("\\r"));
				break;
			case _T('\t'):
				_ftprintf(log->file, _T("%s"), _T("\\t"));
				break;
			default:
				if(__isascii(value[i])) {
					_ftprintf(log->file, _T("%c"), value[i]);
				} else {
					_ftprintf(log->file, _T("%04d"), value[i]);
				}
		}
	}

	_ftprintf(log->file, _T("\""));

	((struct json_data*)log->moduleData)->followingKeyVal = 1;
	return 0;
}
