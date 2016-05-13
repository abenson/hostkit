#include <stdio.h>
#include <stdlib.h>

#include "writer.h"

void run(TCHAR *type)
{
	log_t *log;

	log = open_log(_T("-"), type);

	if(log == NULL)
	{
		puts("Failed.");
	}

	start_dict(log, _T("compile"));
	start_list(log);
	add_value(log, _T("date"), _T(__DATE__));
	add_value(log, _T("time"), _T(__TIME__));
	close_list(log);
	start_list(log);
	add_value(log, _T("file"), _T(__FILE__));
	add_value(log, _T("timestamp"), _T(__TIMESTAMP__));
	close_list(log);
	close_dict(log);

	start_dict(log, _T("test"));
	start_list(log);
	add_value(log, _T("test"), _T("field"));
	close_list(log);
	close_dict(log);

	close_log(log);
}

int main(int argc, char *argv[])
{
	run(_T("json"));
	run(_T("xml"));
	return 0;
}
