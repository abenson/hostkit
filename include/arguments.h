#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "common.h"

#include "modules/modules.h"

enum { ARGS_OK, ARGS_INVALID, ARGS_NONE };

struct arguments {
	int error;

	BOOL version;

	int mode;

	log_t *log;
	TCHAR *filename;
	TCHAR *writer;

	BOOL persistent;

	BOOL service;
	BOOL verbose;
	BOOL debug;

	FILE *logFile;

	_TCHAR *pipe;
	_TCHAR *server;
};

extern struct arguments arguments;

void initialize_arguments(void);

_TCHAR* get_help();

int parse_arguments(_TCHAR *argv[]);

#endif
