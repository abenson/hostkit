#ifndef WMODULES_H
#define WMODULES_H

#include "writer.h"

struct wmodule {
	const _TCHAR *name;
	int (*begin)(log_t*);
	int (*end)(log_t*);
	int (*open_section)(log_t *, const _TCHAR*);
	int (*close_section)(log_t *);

	int (*open_item)(log_t*);
	int (*close_item)(log_t*);

	int (*add_value)(log_t*, const _TCHAR*, const _TCHAR*);
};

extern struct wmodule modules[];

int find_format(const _TCHAR *name);

#endif
