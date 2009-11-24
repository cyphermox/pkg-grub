/* grub-mkrelpath.c - make a system path relative to its root */
/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2009 Free Software Foundation, Inc.
 *
 *  GRUB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GRUB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GRUB.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <grub/util/misc.h>
#include <getopt.h>

static struct option options[] =
  {
    {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'V'},
  };

static void
usage (int status)
{
  if (status)
    fprintf (stderr, "Try ``grub-mkrelpath --help'' for more information.\n");
  else
    printf ("\
Usage: grub-mkrelpath [OPTIONS] PATH\n\
\n\
Make a system path relative to it's root.\n\
\n\
Options:\n\
  -h, --help                display this message and exit\n\
  -V, --version             print version information and exit\n\
\n\
Report bugs to <%s>.\n", PACKAGE_BUGREPORT);

  exit (status);
}

int
main (int argc, char *argv[])
{
  char *argument, *relpath;

  progname = "grub-mkrelpath";

  /* Check for options.  */
  while (1)
    {
      int c = getopt_long (argc, argv, "hV", options, 0);

      if (c == -1)
	break;
      else
	switch (c)
	  {
	  case 'h':
	    usage (0);
	    break;

	  case 'V':
	    printf ("%s (%s) %s\n", progname, PACKAGE_NAME, PACKAGE_VERSION);
	    return 0;

	  default:
	    usage (1);
	    break;
	  }
    }

  if (optind >= argc)
    {
      fprintf (stderr, "No path is specified.\n");
      usage (1);
    }

  if (optind + 1 != argc)
    {
      fprintf (stderr, "Unknown extra argument `%s'.\n", argv[optind + 1]);
      usage (1);
    }

  argument = argv[optind];

  relpath = make_system_path_relative_to_its_root (argument);
  printf ("%s\n", relpath);
  free (relpath);

  return 0;
}