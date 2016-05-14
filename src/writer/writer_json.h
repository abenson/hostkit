#ifndef OUTJSON_H
#define OUTJSON_H

#include "writer.h"

int json_begin(log_t *log);
int json_end(log_t *log);

int json_start_dict(log_t *);
int json_close_dict(log_t *);

int json_start_list(log_t*);
int json_close_list(log_t*);

int json_add_value(log_t *, const _TCHAR*, const _TCHAR*);

#endif
