#ifndef OUTRUBY_H
#define OUTRUBY_H

#include "writer.h"

int ruby_begin(log_t *log);
int ruby_end(log_t *log);

int ruby_start_dict(log_t *);
int ruby_close_dict(log_t *);

int ruby_start_list(log_t*);
int ruby_close_list(log_t*);

int ruby_add_value(log_t *, const _TCHAR*, const _TCHAR*);

#endif
