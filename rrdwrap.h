//	rrdwrap.h - wrapper functions for the rrd tool

//	Contributed by Antony Clothier, December 2001


#ifndef RRD_WRAP_H

#define RRD_WRAP_H

	#include <rrd.h>

	int wrap_rrd_create(char *argstr);

	int wrap_rrd_update(char *argstr);

	int wrap_rrd_graph(char *argstr, FILE *fd);

	int wrap_rrd_restore(char *argstr);

	int wrap_rrd_dump(char *argstr);

	int wrap_rrd_tune(char *argstr);

	char** string_to_argv(char *argstring, int *argc);

	void Free_argv(char** argv);

#endif

