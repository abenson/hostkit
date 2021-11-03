#ifndef WRITERS_H
#define WRITERS_H

#include "writer.h"

struct writer {
	const wchar_t *name;
	int (*begin)(log_t*);
	int (*end)(log_t*);
	int (*open_section)(log_t *, const wchar_t*);
	int (*close_section)(log_t *);
	int (*start_itemlist)(log_t *, const wchar_t *);
	int (*start_itemlist_item)(log_t *, const wchar_t*);
	int (*end_itemlist_item)(log_t *);
	int (*end_itemlist)(log_t*);
	int (*add_value)(log_t*, const wchar_t*, const wchar_t*);
};

extern struct writer writers[];

int find_format(const wchar_t *name);
int print_formats(FILE *fp);

#endif
