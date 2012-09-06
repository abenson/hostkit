#include "../common.h"
#include "modules.h"

struct module basic[] = {
	NULL
};

struct module basic_only[] = {
	NULL
};

struct module standard[] = {
	NULL
};

struct module standard_only[] = {
	NULL
};

struct module full[] = {
	NULL
};

struct module full_only[] = {
	NULL
};

int run_scan(struct module list[])
{
	int i;

	for(i=0; list[i].entry_point != NULL; i++)
	{
		if(list[i].entry_point() != 0) {
			return -1;
		}
	}
	return 0;
}

int run_basic_scan(void)
{
	run_scan(basic);
	run_scan(basic_only);
}

int run_standard_scan(void)
{
	run_scan(basic);
	run_scan(standard);
	run_scan(standard_only);
}

int run_full_scan(void)
{
	run_scan(basic);
	run_scan(standard);
	run_scan(full);
	run_scan(full_only);
}