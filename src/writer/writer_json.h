#ifndef OUTJSON_H
#define OUTJSON_H

#include "writer.h"

int json_begin(log_t *log);
int json_end(log_t *log);

int json_open_section(log_t *, const _TCHAR*);
int json_close_section(log_t *);

int json_start_itemlist(log_t *, const TCHAR*);
int json_start_itemlist_item(log_t*);
int json_end_itemlist_item(log_t*);
int json_end_itemlist(log_t *);

int json_add_value(log_t *, const _TCHAR*, const _TCHAR*);


#endif
