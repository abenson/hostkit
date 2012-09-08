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
	TCHAR *filename;
	int writer;

	BOOL persistent;

	BOOL service;
	BOOL verbose;
	BOOL debug;
	FILE *log;

	TCHAR *pipe;
	TCHAR *server;
};

extern struct arguments arguments;

void initialize_arguments(void);

TCHAR* get_help();

int parse_arguments(TCHAR *argv[]);

#endif
