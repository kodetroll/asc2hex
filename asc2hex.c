// asc2hex - A program that takes a string of the form 'ABCDE' and converts
// it to the form of '4142434445' (hex)
//
// (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
// Author: Kodetroll
// Date: January 2015
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define Major 0
#define Minor 99

/* Flag set by --verbose. */
static int verbose_flag;

char inbuf[120];
char outbuf[120];

int main(int argc, char * argv[])
{
	int i,j,k;
	char c;
	char tmp[4];
	int cl;

	while (1)
    {

		// parse args
		static struct option long_options[] =
		{
			/* These options set a flag. */
			{"verbose", no_argument,       &verbose_flag, 1},
			{"brief",   no_argument,       &verbose_flag, 0},
			/* These options don’t set a flag.
				 We distinguish them by their indices. */
			{"version", no_argument,       0, 'v'},
			{"help",    no_argument,       0, 'h'},
	//		{"add",     no_argument,       0, 'a'},
	//		{"append",  no_argument,       0, 'b'},
	//		{"delete",  required_argument, 0, 'd'},
	//		{"create",  required_argument, 0, 'c'},
			{"file",    required_argument, 0, 'f'},
			{0, 0, 0, 0}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;

		cl = getopt_long (argc, argv, "vhc:d:f:",
				long_options, &option_index);

		/* Detect the end of the options. */
		if (cl == -1)
			break;

		switch (cl)
		{
			case 0:
				/* If this option set a flag, do nothing else now. */
				if (long_options[option_index].flag != 0)
					break;
				printf ("option %s", long_options[option_index].name);
				if (optarg)
					printf (" with arg %s", optarg);
				printf ("\n");
				break;

			case 'v':
				printf("Version: %d.%d\n",Major,Minor);
				exit(0);
				break;

			case 'h':
				printf("Usage: '%s' <options> HEXSTRING\n",argv[0]);
				exit(0);
				break;

			case 'f':
				printf ("option -f with value `%s'\n", optarg);
				break;

			case '?':
				/* getopt_long already printed an error message. */
				break;

			default:
				abort ();
		}
	}

	/* Print any remaining command line arguments (not options). */
	if (optind < argc)
	{
		printf ("non-option ARGV-elements: ");
		while (optind < argc)
			printf ("%s ", argv[optind++]);
		putchar ('\n');
	}

	if (argc < 2)
	{
		printf("Please enter string ('abcde'): ");
		scanf("%79s",inbuf);
	} else {
		strcpy(inbuf,argv[1]);
	}

	memset(outbuf,0x00,sizeof(outbuf));
	i = 0;
	j = 0;
	do
	{
		sprintf(tmp,"%02x",inbuf[i++]);
		strncat(outbuf,tmp,strlen(tmp));
	} while (i<strlen(inbuf));

	printf("%s",outbuf);

	exit(0);
}
