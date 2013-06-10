#include <stdio.h>
#include <stdlib.h>

#include "writer_xml.h"

int xml_begin(log_t *log)
{
	fprintf(log->file, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<results>\n");
	return 0;
}

int xml_end(log_t *log)
{
	fprintf(log->file, "</results>\n");
	return 0;
}

int xml_open_section(log_t *log, const _TCHAR *name)
{
	fprintf(log->file, "   <%s>\n", log->section);
	return 0;
}

int xml_close_section(log_t *log)
{
	fprintf(log->file, "   </%s>\n", log->section);
	return 0;
}

int xml_open_item(log_t *log)
{
	fprintf(log->file, "      <item>\n");
	return 0;
}

int xml_close_item(log_t *log)
{
	fprintf(log->file, "      </item>\n");
	return 0;
}

int xml_add_value(log_t *log, const _TCHAR *key, const _TCHAR *value)
{
	fprintf(log->file, "          <%s>%s</%s>\n", key, value, key);
	return 0;
}
