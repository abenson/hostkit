
#include <stdlib.h>
#include <string.h>

#include "writers.h"

#include "writer_json.h"
#include "writer_xml.h"

struct module modules[] = {
	{_T("xml"), xml_begin, xml_end, xml_open_section, xml_close_section, xml_open_item, xml_close_item, xml_add_value},
	{_T("json"), json_begin, json_end, json_open_section, json_close_section, json_open_item, json_close_item, json_add_value},
	{NULL, NULL, NULL, NULL, NULL, NULL}
};

int find_format(const _TCHAR *format)
{
	int i = 0;
	while(modules[i].name) {
		if(_tcscmp(modules[i].name, format) == 0) {
			return i;
		}
		i++;
	}
	return -1;
}
