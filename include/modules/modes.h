#ifndef MODES_H
#define MODES_H

#include <windows.h>
#include <tchar.h>

/*** SHARED FUNCTIONS */

int lsdir(const TCHAR *rootpath);

/*** BASIC MODE *************/

int host_details(void);
int disk_details(void);

/* STANDARD MODE ************/

int enum_windir(void);

/* FULL MODE ****************/

#endif