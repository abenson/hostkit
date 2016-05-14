#ifndef WMODULES_H
#define WMODULES_H

#include "writer.h"

struct wmodule
{
	const _TCHAR *name;
	int (*begin)(log_t*);
	int (*end)(log_t*);
	int (*start_dict)(log_t *);
	int (*close_dict)(log_t *);

	int (*start_list)(log_t*);
	int (*close_list)(log_t*);

	int (*add_value)(log_t*, const _TCHAR*, const _TCHAR*);
};

extern struct wmodule modules[];

int find_format(const _TCHAR *name);

#endif
