#ifndef OUTXML_H
#define OUTXML_H

#include "writer.h"

int xml_begin(log_t *log);
int xml_end(log_t *log);

int xml_open_section(log_t *, const _TCHAR*);
int xml_close_section(log_t *);

int xml_start_itemlist(log_t *, const TCHAR*);
int xml_start_itemlist_item(log_t*);
int xml_end_itemlist_item(log_t*);
int xml_end_itemlist(log_t *);

int xml_add_value(log_t *, const _TCHAR*, const _TCHAR*);

#endif
