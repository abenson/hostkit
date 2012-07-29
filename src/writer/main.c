#include <stdio.h>
#include <stdlib.h>

#include "writer.h"

int main(int argc, char *argv[])
{
	log_t *log;

	log = open_log("-", "json");

	if(log == NULL) {
		puts("Failed.");
	}

	open_section(log, "compile");
	open_item(log);
	add_value(log, "date", __DATE__);
	add_value(log, "time", __TIME__);
	close_item(log);
	open_item(log);
	add_value(log, "file", __FILE__);
	add_value(log, "timestamp", __TIMESTAMP__);
	close_item(log);
	close_section(log);

	open_section(log, "test");
	open_item(log);
	add_value(log, "test", "field");
	close_item(log);
	close_section(log);

	close_log(log);

	return 0;
}
