#ifndef OUTXML_H
#define OUTXML_H

#include "writer.h"

int xml_begin(log_t *log);
int xml_end(log_t *log);

int xml_start_dict(log_t *, const _TCHAR*);
int xml_close_dict(log_t *);

int xml_start_list(log_t*);
int xml_close_list(log_t*);

int xml_add_value(log_t *, const _TCHAR*, const _TCHAR*);

#endif
