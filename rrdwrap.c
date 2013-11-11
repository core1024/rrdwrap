//	rrdwrap.c - wrapper functions for the rrd tool

//	Contributed by Antony Clothier

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "rrdwrap.h"


int wrap_rrd_create(char *argstr)
{
	char
		**argv;

	int
		i, argc;

	if((argv = string_to_argv(argstr, &argc)) != NULL)
	{
		optind=0; /* reset gnu getopt */
		opterr=0; /* no error messages */

		i = rrd_create(argc, argv);

		//	free up the memory
		Free_argv(argv);

		return i;
	}
	else
	{
		//	error
		return (-1);
	}
}


int wrap_rrd_update(char *argstr)
{
	char
		**argv;

	int
		i, argc;

	if((argv = string_to_argv(argstr, &argc)) != NULL)
	{
		optind=0; /* reset gnu getopt */
		opterr=0; /* no error messages */

		i = rrd_update(argc, argv);

		//	free up the memory
		Free_argv(argv);

		return i;
	}
	else
	{
		//	error
		return (-1);
	}
}


int wrap_rrd_restore(char *argstr)
{
	char
		**argv;

	int
		i, argc;

	if((argv = string_to_argv(argstr, &argc)) != NULL)
	{
		optind=0; /* reset gnu getopt */
		opterr=0; /* no error messages */

		i = rrd_restore(argc, argv);

		//	free up the memory
		Free_argv(argv);

		return i;
	}
	else
	{
		//	error
		return (-1);
	}
}


int wrap_rrd_dump(char *argstr)
{
	char
		**argv;

	int
		i, argc;

	if((argv = string_to_argv(argstr, &argc)) != NULL)
	{
		optind=0; /* reset gnu getopt */
		opterr=0; /* no error messages */

		i = rrd_dump(argc, argv);

		//	free up the memory
		Free_argv(argv);

		return i;
	}
	else
	{
		//	error
		return (-1);
	}
}


int wrap_rrd_tune(char *argstr)
{
	char
		**argv;

	int
		i, argc;

	if((argv = string_to_argv(argstr, &argc)) != NULL)
	{
		optind=0; /* reset gnu getopt */
		opterr=0; /* no error messages */

		i = rrd_tune(argc, argv);

		//	free up the memory
		Free_argv(argv);

		return i;
	}
	else
	{
		//	error
		return (-1);
	}
}


int wrap_rrd_graph(char *argstr, FILE *fd)
{
	char
		**prdata = NULL,	//	must be passed to the rrd_graph function but does not need to be initialised
		**argv = NULL;

	int
		i, argc,
		xsize = 0,	//	must be passed to the rrd_graph function but does not need to be initialised
		ysize = 0;	//	must be passed to the rrd_graph function but does not need to be initialised
	double
		ymin,	//	must be passed to the rrd_graph function but does not need to be initialised
		ymax;	//	must be passed to the rrd_graph function but does not need to be initialised

	if((argv = string_to_argv(argstr, &argc)) != NULL)
	{
		optind=0; /* reset gnu getopt */
		opterr=0; /* no error messages */

		i = rrd_graph(argc, argv, &prdata, &xsize, &ysize, fd, &ymin, &ymax);

		//	free up the memory
		Free_argv(argv);

		return i;
	}
	else
	{
		//	error
		return (-1);
	}
}



char** string_to_argv(char *argstring, int *argc)
{
	char
		inquotes = 0,
		*workstring,
		**argv;

	int
		i, nchars;

	if((nchars = strlen(argstring)) > 0)
	{
		workstring = (char*)calloc((nchars + 2), sizeof(char*));

		//	fill the array with space characters
		for(i=0; i < (nchars + 2); i++)
			workstring[i] = ' ';

		//	copy the argstring into the workstring (padded with spaces on both ends)
		for(i=0; i < nchars; i++)
			workstring[i+1] = argstring[i];

		for((*argc) = 1, i=0; i < nchars + 2; i++)
		{
			//	count the number of arguements
			if(isgraph(workstring[i]) > 0)
			{
				//	if current character is not whitespace and previous character is whitespace, increment (*argc)
				if((isgraph(workstring[i-1]) == 0) && (inquotes == 0))
					(*argc)++;

				//	check for the quote character
				if(workstring[i] == '"' || workstring[i] == '\'')
				{
					//	toggle inquotes flag
					inquotes = (char)(!inquotes);
				}

			}
			else
			{
				//	convert whitespace to null characters
				if(!inquotes)
					workstring[i] = '\0';
			}
		}

		//	no arguements in the string
		if((*argc) == 0)
		{
			free(workstring);
			return NULL;
		}
		else
		{
			inquotes = 0;

			argv = (char**)calloc((*argc), sizeof(char**));

			argv[0] = &workstring[0];

			for((*argc) = 1, i=1; i < nchars + 2; i++)
			{
				//	count the number of arguements
				if(isgraph(workstring[i]) > 0)
				{
					//	if current character is not whitespace and previous character is whitespace, increment (*argc)
					if((isgraph(workstring[i-1]) == 0) && (inquotes == 0))
					{
						argv[(*argc)] = &workstring[i];

						(*argc)++;
					}

					//	check for the quote character
					if(workstring[i] == '"' || workstring[i] == '\'')
					{
						// Strip the quotes
						memmove(&workstring[i], &workstring[i]+1, nchars - i );
						workstring[nchars] = '\0';

						//	toggle inquotes flag
						inquotes = (char)(!inquotes);
					}
				}
			}

			return argv;
		}
	}
	else
	{
		(*argc) = 0;
		return NULL;
	}
}


void Free_argv(char** argv)
{
	free(argv[0]);
	free(argv);
}

