#include "lx_string.h"

int main (argc, argv)
	int argc;
	char **argv;
{
	lx_gd outgd;

	if (lx_gdnew (&outgd, 1, 80)) exit (1);

	if (lx_gdputs (&outgd, "herro dere and stuff\n")) exit (1);
	if (lx_gdputs (&outgd, "yeah, all that rap")) exit (1);
	if (lx_gdputs (&outgd, "... and stuff.\n")) exit (1);

	lx_gdflush(&outgd);
	return 0;
}
