// hex2asc - A program that takes a string in the form of '4142434445' (hex)
// and converts it to the binary represented by the hex digits. e.g.
// 'abcde'.
//
// (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
// Author: Kodetroll
// Date: January 2015
// Version: 0.99.1 (First to receive a version number)
//
// Includes code from strrep.c - C substring replacement by Drew Hess <dhess-src@bothan.net>.
//
//	Usage:
//	'%s' <options> <HEXSTRING>
//
//	Where:
//	options:
//	    -h, --help                This information
//	    -v, --version             Version information
//	    --hexdump                 Turns on Hexdump of output string
//	    --nohexdump               Turns off Hexdump of output string
//	    -d, --dump {0:1}          Synonym for Hexdump where 0 is OFF and 1 is ON
//	    -f, --file <filename>     Load string from file
//	    -i, --input '<HEXSTRING>' Load string from command line
//	    <HEXSTRING>               String of Bytes in hex format, e.g. '443266'.
//		--printable               Display 'Printable' characters only.
//
//	If no hexstring is provided on the command line, the user is prompted to enter it.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>

#include "hex2asc.h"

#include "binaschex.h"

//=== Global Definitions ====================================================================================

//=== Global Variables ======================================================================================

/* Various Flags set by getopt. */
static int verbose_flag;
static int hexdump_flag;
int print_flag;
int unpar_flag;

char inbuf[5000];
char outbuf[5000];

//=== Global Prototypes =====================================================================================

void usage(char * name);

//=== Start of Utility functions ============================================================================

/* Provides usage help for the help command
 *
 */
void usage(char * name)
{
	printf("Usage: '%s' <options> <HEXSTRING>\n",name);
	printf("Where:\n");
	printf("options: \n");
	printf("    -h, --help                This information\n");
	printf("    -v, --version             Version information\n");
	printf("    --hexdump                 Turns on Hexdump of output string\n");
	printf("    --nohexdump               Turns off Hexdump of output string\n");
	printf("    --printable               Display 'Printable' characters only.\n");
	printf("    --unparity                Turns on parity to non-parity conversion (subtracts 0x80)\n");
	printf("    -d, --dump {0:1}          Synonym for Hexdump where 0 is OFF and 1 is ON\n");
	printf("    -f, --file <filename>     Load string from file\n");
	printf("    -i, --input '<HEXSTRING>' Load string from command line\n");
	printf("    <HEXSTRING>               String of Bytes in hex format, e.g. '443266'.\n");
	printf("    Note: If no hexstring is provided on the command line, the user is prompted to enter it.");
	printf("\n");
	exit(0);
}

int main(int argc, char * argv[])
{
	FILE * fp;
	int i,j,k,cl,inlen;
	char c;
	int gotin = 0;
	char buf[5000];

	print_flag = 0;
	unpar_flag = 0;

	while (1)
    {
		// parse args
		static struct option long_options[] =
		{
			/* These options set a flag. */
			{"verbose",   	no_argument,   &verbose_flag, 1},
			{"brief",     	no_argument,   &verbose_flag, 0},
			{"hexdump",   	no_argument,   &hexdump_flag, 1},
			{"nohexdump", 	no_argument,   &hexdump_flag, 0},
			{"printable", 	no_argument,     &print_flag, 1},
			{"unparity", 	no_argument,     &unpar_flag, 1},
			/* These options don’t set a flag.
				 We distinguish them by their indices. */
			{"version",   	no_argument,       0, 'v'},
			{"help",      	no_argument,       0, 'h'},
			{"dump",      	required_argument, 0, 'd'},
			{"input",     	required_argument, 0, 'i'},
			{"file",      	required_argument, 0, 'f'},
			{0, 0, 0, 0}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;

		cl = getopt_long (argc, argv, "vhc:d:i:f:",
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
				printf("Version: %d.%d.%d\n",Major,Minor,SubMinor);
				exit(0);
				break;

			case 'h':
				usage(argv[0]);
				break;

			case 'd':
				hexdump_flag = atoi(optarg);
				break;

			case 'i':
				strcpy(inbuf,optarg);
				gotin = 1;
				break;

			case 'f':
				if (verbose_flag)
					printf ("Loading input from file: `%s'\n", optarg);
				fp = fopen (optarg,"r");
				if (fp != NULL)
				{
					inlen = 0;
					while( ( c = fgetc(fp) ) != EOF ) {
						//if (c != ' ' && c != '\n') {
							sprintf(buf,"%c",c);
							strncat(inbuf,buf,1);
							inlen++;
						//}
					}
    				fclose (fp);
					gotin = 1;

				}
				else
				{
					printf("Error opening file '%s'!\n",optarg);
					exit(1);
				}
				break;

			case '?':
				/* getopt_long already printed an error message. */
				break;

			default:
				abort ();
		}
	}

	int mopt = 0;
	if (gotin == 0)
	{
		/* Print any remaining command line arguments (not options). */
		if (optind < argc)
		{
			mopt = optind;

			if (verbose_flag)
				printf ("non-option ARGV-elements: ");
			while (optind < argc)
			{
				if (verbose_flag)
					printf ("option(%d): %s\n", optind,argv[optind]);
				strcat(inbuf,argv[optind]);
				optind++;
			}
			if (verbose_flag)
				putchar ('\n');
		}

		if (mopt == 0)
		{
			printf("Enter hex string (e.g. '414F54' 75 chars max): ");
			scanf("%78s",inbuf);
		}

	}

	// Start of Program hex2asc

	// remove any spaces from string
	memset(buf,0x00,sizeof(buf));
	strcpy(buf,strrep(inbuf, " ", ""));

	// remove CR/LF from string (file input mostly)
	memset(inbuf,0x00,sizeof(inbuf));
	strcpy(inbuf,strrep(buf, "\n", ""));

	//printf("inlen: %d\n",inlen);
	//printf("inbuf: '%s'\n",inbuf);

	// Convert string from Hex ASCII chars to binary form
	j = hex2asc(inbuf, outbuf);

	// if hexdump is selected then the binary is output in
	// hexdump form, else it is copied to output
	if (hexdump_flag)
	{
		if (verbose_flag)
			printf("Data(hex) is : \n");
		HexDataDump(strlen(inbuf)/2,outbuf);
	}
	else
	{
		printf("%s",outbuf);
	}

	exit(0);
}
