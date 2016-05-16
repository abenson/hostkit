
#include <windows.h>
#include <tchar.h>

#include <stdlib.h>
#include <string.h>

#include "writers.h"

#include "writer_json.h"
#include "writer_xml.h"
#include "writer_ruby.h"

struct wmodule modules[] =
{
	{_T("xml"), xml_begin, xml_end, xml_start_dict, xml_close_dict, xml_start_list, xml_close_list, xml_add_value},
/*
	{_T("json"), json_begin, json_end, json_start_dict, json_close_dict, json_start_list, json_close_list, json_add_value},
	{_T("ruby"), ruby_begin, ruby_end, ruby_start_dict, ruby_close_dict, ruby_start_list, ruby_close_list, ruby_add_value},
*/
	{NULL, NULL, NULL, NULL, NULL, NULL}
};

int find_format(const TCHAR *format)
{
	int i = 0;

	if(_tcscmp(format, _T("list")) == 0) {
		_ftprintf(stdout, _T("Available writer modules:\n"));
		while(modules[i].name) {
			_ftprintf(stdout, _T("   %s\n"), modules[i].name);
			i++;
		}
		return -1;
	}

	while(modules[i].name) {
		if(_tcscmp(modules[i].name, format) == 0) {
			return i;
		}
		i++;
	}
	return -1;
}
