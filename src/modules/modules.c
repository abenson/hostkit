#include "modules.h"

#include "basic/basic.h"
#include "standard/standard.h"
#include "full/full.h"

struct module basic[] = {
	host_details,
	disk_details,
	NULL
};

struct module basic_only[] = {
	NULL
};

struct module standard[] = {
	NULL
};

struct module standard_only[] = {
	enum_windir
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
			return ERR_MODFAIL;
		}
	}
	return ERR_NONE;
}

int run_basic_scan(void)
{
	run_scan(basic);
	run_scan(basic_only);

	return ERR_NONE;
}

int run_standard_scan(void)
{
	run_scan(basic);
	run_scan(standard);
	run_scan(standard_only);

	return ERR_NONE;
}

int run_full_scan(void)
{
	run_scan(basic);
	run_scan(standard);
	run_scan(full);
	run_scan(full_only);

	return ERR_NONE;
}
