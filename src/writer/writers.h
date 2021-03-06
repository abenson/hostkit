#ifndef WRITERS_H
#define WRITERS_H

#include "writer.h"

struct writer {
	const _TCHAR *name;
	int (*begin)(log_t*);
	int (*end)(log_t*);
	int (*open_section)(log_t *, const _TCHAR*);
	int (*close_section)(log_t *);
	int (*start_itemlist)(log_t *, const TCHAR *);
	int (*start_itemlist_item)(log_t *, const TCHAR*);
	int (*end_itemlist_item)(log_t *);
	int (*end_itemlist)(log_t*);
	int (*add_value)(log_t*, const _TCHAR*, const _TCHAR*);
};

extern struct writer writers[];

int find_format(const _TCHAR *name);
int print_formats(FILE *fp);

#endif
