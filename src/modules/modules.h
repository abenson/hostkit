#ifndef MODULES_H
#define MODULES_H

enum RUNMODE { RM_NONE, RM_BASIC, RM_STANDARD, RM_FULL };

struct module
{
	int (*entry_point)(void);
};

#endif
