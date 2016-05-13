
#include <stdlib.h>
#include <string.h>

#include "writers.h"

#include "writer_json.h"
#include "writer_xml.h"

struct wmodule modules[] =
{
	{_T("xml"), xml_begin, xml_end, xml_start_dict, xml_close_dict, xml_start_list, xml_close_list, xml_add_value},
	{_T("json"), json_begin, json_end, json_start_dict, json_close_dict, json_start_list, json_close_list, json_add_value},
	{NULL, NULL, NULL, NULL, NULL, NULL}
};

int find_format(const _TCHAR *format)
{
	int i = 0;
	while(modules[i].name)
	{
		if(_tcscmp(modules[i].name, format) == 0)
		{
			return i;
		}
		i++;
	}
	return -1;
}
