
#include <stdlib.h>
#include <string.h>

#include "writers.h"

#include "writer_json.h"
#include "writer_xml.h"

struct writer writers[] = {
	{L"xml", xml_begin, xml_end, xml_open_section, xml_close_section, xml_start_itemlist, xml_start_itemlist_item, xml_end_itemlist_item, xml_end_itemlist, xml_add_value},
	{L"json", json_begin, json_end, json_open_section, json_close_section, json_start_itemlist, json_start_itemlist_item, json_end_itemlist_item, json_end_itemlist, json_add_value},
	{NULL, NULL, NULL, NULL, NULL, NULL}
};

int find_format(const wchar_t *format)
{
	int i = 0;
	while(writers[i].name) {
		if(wcscmp(writers[i].name, format) == 0) {
			return i;
		}
		i++;
	}
	return -1;
}

int print_formats(FILE *fp)
{
	int i = 0;
	fwprintf(fp, L"Available Writers:\n");
	while(writers[i].name) {
		fwprintf(fp, L"\t%s\n", writers[i].name);
		i++;
	}
	return 0;
}
