#ifndef MODULES_H
#define MODULES_H

#include "writer.h"

struct module {
	const char *name;
	int (*begin)(log_t*);
	int (*end)(log_t*);
	int (*open_section)(log_t *, const char*);
	int (*close_section)(log_t *);

	int (*open_item)(log_t*);
	int (*close_item)(log_t*);

	int (*add_value)(log_t*, const char*, const char*);
};

extern struct module modules[];

int find_format(const char *name);

#endif
