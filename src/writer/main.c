#include <stdio.h>
#include <stdlib.h>

#include "writer.h"

void run(TCHAR *type)
{
	log_t *log;

	log = open_log(_T("-"), type);

	if(log == NULL) {
		_ftprintf(stdout, _T("Did not open log.\n"));
		return;
	}

	start_dict(log, _T("compile"));
		add_value(log, _T("date"), _T(__DATE__));
		add_value(log, _T("time"), _T(__TIME__));
		add_value(log, _T("file"), _T(__FILE__));
		add_value(log, _T("timestamp"), _T(__TIMESTAMP__));
	close_dict(log);
	start_list(log, _T("a"));
		start_list(log, _T("b"));
			start_list(log, _T("c"));
				start_list(log, _T("d"));
				close_list(log);
			close_list(log);
		close_list(log);
	close_list(log);
	start_list(log, _T("listodata"));
		start_dict(log, _T("data"));
			add_value(log, _T("one"), _T("1"));
			add_value(log, _T("two"), _T("2"));
		close_dict(log);
		start_dict(log, _T("data"));
			add_value(log, _T("one"), _T("1"));
			add_value(log, _T("two"), _T("2"));
		close_dict(log);
		start_dict(log, _T("data"));
			add_value(log, _T("one"), _T("1"));
			add_value(log, _T("two"), _T("2"));
			add_value(log, _T("three"), _T("3"));
		close_dict(log);
	close_list(log);
	start_list(log, _T("listonumbers"));
		start_dict(log, _T("i123"));
			add_value(log, _T("one"), _T("1"));
			add_value(log, _T("two"), _T("2"));
		close_dict(log);
		start_dict(log, _T("i123"));
			add_value(log, _T("one"), _T("1"));
			add_value(log, _T("two"), _T("2"));
		close_dict(log);
		start_dict(log, _T("i123"));
			add_value(log, _T("one"), _T("1"));
			add_value(log, _T("two"), _T("2"));
			add_value(log, _T("three"), _T("3"));
		close_dict(log);
	close_list(log);
	start_dict(log, _T("book"));
		add_value(log, _T("author"), _T("Bilbo Baggins"));
		add_value(log, _T("title"), _T("There and Back Again"));
	close_dict(log);
	close_log(log);
}

int _tmain(int argc, char *argv[])
{
	run(_T("xml"));
	return 0;
}
