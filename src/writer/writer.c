#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "writer.h"
#include "writers.h"

log_t* open_log(const char *filename, const char *format)
{
	log_t *log;
	int fmtIndex;

	fmtIndex = find_format(format);
	if(fmtIndex < 0) { return NULL; }

	log = malloc(sizeof(*log));
	if(log) {
		if(strcmp(filename, "-") == 0) {
			log->file = stdout;
		} else {
			log->file = fopen(filename, "w+");
		}
		if(log->file) {
			log->format = fmtIndex;
			modules[log->format].begin(log);
			return log;
		}
		free(log);
	}
	return NULL;
}

void close_log(log_t *log)
{
	modules[log->format].end(log);
	if(log->file != stdout) {
		fclose(log->file);
	}
	free(log);
}

int open_section(log_t *log, const char *name)
{
	log->section = dupestr(name);
	return modules[log->format].open_section(log, name);
}

int close_section(log_t *log)
{
	int value; 
	value = modules[log->format].close_section(log);
	free(log->section);
	return value;
}

int open_item(log_t *log)
{
	return modules[log->format].open_item(log);
}

int close_item(log_t *log)
{
	return modules[log->format].close_item(log);
}

int add_value(log_t *log, const char *key, const char *value)
{
	return modules[log->format].add_value(log, key, value);
}
