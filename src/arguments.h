#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "common.h"

#include "modules/modules.h"

enum { ARGS_OK, ARGS_INVALID, ARGS_NONE };

struct arguments {
	int error;

	BOOL version;

	int mode;
	FILE *file;
	wchar_t *filename;
	wchar_t *writer;

	BOOL persistent;

	BOOL service;
	BOOL verbose;
	BOOL debug;
	FILE *log;

	wchar_t *pipe;
	wchar_t *server;
};

extern struct arguments arguments;

void initialize_arguments(void);

wchar_t* get_help();

int parse_arguments(wchar_t *argv[]);

#endif
