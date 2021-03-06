#ifndef MODULES_H
#define MODULES_H

enum RUNMODE { RM_NONE, RM_BASIC, RM_STANDARD, RM_FULL };

struct module
{
	int (*entry_point)(void);
};

int run_basic_scan(void);
int run_standard_scan(void);
int run_full_scan(void);

#endif
