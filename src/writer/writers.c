
#include <stdlib.h>
#include <string.h>

#include "writers.h"

#include "writer_json.h"
#include "writer_xml.h"

struct writer writers[] = {
	{_T("xml"), xml_begin, xml_end, xml_open_section, xml_close_section, xml_add_value},
	{_T("json"), json_begin, json_end, json_open_section, json_close_section, json_add_value},
	{NULL, NULL, NULL, NULL, NULL, NULL}
};

int find_format(const _TCHAR *format)
{
	int i = 0;
	while(writers[i].name) {
		if(_tcscmp(writers[i].name, format) == 0) {
			return i;
		}
		i++;
	}
	return -1;
}

int print_formats(FILE *fp)
{
	int i = 0;
	_ftprintf(fp, _T("Available Writers:\n"));
	while(writers[i].name) {
		_ftprintf(fp, _T("\t%s\n"), writers[i].name);
		i++;
	}
	return 0;
}
