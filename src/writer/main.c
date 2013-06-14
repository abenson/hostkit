#include <stdio.h>
#include <stdlib.h>

#include "writer.h"

int main(int argc, char *argv[])
{
	log_t *log;

	log = open_log(_T("-"), _T("json"));

	if(log == NULL) {
		puts("Failed.");
	}

	open_section(log, _T("compile"));
	open_item(log);
	add_value(log, _T("date"), _T(__DATE__));
	add_value(log, _T("time"), _T(__TIME__));
	close_item(log);
	open_item(log);
	add_value(log, _T("file"), _T(__FILE__));
	add_value(log, _T("timestamp"), _T(__TIMESTAMP__));
	close_item(log);
	close_section(log);

	open_section(log, _T("test"));
	open_item(log);
	add_value(log, _T("test"), _T("field"));
	close_item(log);
	close_section(log);

	close_log(log);

	return 0;
}
