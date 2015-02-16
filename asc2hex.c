// asc2hex - A program that takes a string of the form 'ABCDE' and converts
// it to the form of '4142434445' (hex)
//
// (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
// Author: Kodetroll
// Date: January 2015
// Version: 0.99 (First to receive a version number)
//
// Includes code from strrep.c - C substring replacement by Drew Hess <dhess-src@bothan.net>.
//
//	Usage:
//	'asc2hex' <options> <HEXSTRING>
//
//	Where:
//	options:
//	    -h, --help                This information
//	    -v, --version             Version information
//	    --hexdump                 Turns on Hexdump of output string
//	    --nohexdump               Turns off Hexdump of output string
//	    -d, --dump {0:1}          Synonym for Hexdump where 0 is OFF and 1 is ON
//	    -f, --file <filename>     Load string from file
//	    -i, --input '<ASCSTRING>' Load string from command line
//	    <ASCSTRING>               String of Bytes in ASCII format, e.g. '123'.
//
//	If no ASCII string is provided on the command line, the user is prompted to enter it.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>

//=== Global Definitions ====================================================================================

#define Major 0
#define Minor 99
#define HEXDUMP_LINE_SIZE 16

//=== Global Variables ======================================================================================

/* Flag set by --verbose. */
static int verbose_flag;
static int hexdump_flag;

char inbuf[120];
char outbuf[120];

//=== Global Prototypes =====================================================================================
void HexDataDump(int DataLen, unsigned char * Data);
void usage(char * name);
int asc2hex(char * ibuf, char * obuf);


/*
 * This function provides a generalized hexdump facility. Data to be displayed should be in *Data
 * The length of the data string should be included in DataLen. Making this zero will use the
 * strlen value, making this -1 will use the sizeof value.
 * Output will be standard Format 'MMMM: HH HH HH ... HH |ASCII.STRING VALUES|'
 *
 */

void HexDataDump(int DataLen, unsigned char * Data)
{
	int n,i,j;
	unsigned char tmp[15];
	unsigned char tmp1[100];
	unsigned char tmp2[100];

	i = 0;
	do
	{
		memset(tmp1,0x00,sizeof(tmp1));
		memset(tmp2,0x00,sizeof(tmp2));
		sprintf(tmp1,"%04x: ",i);
		for (n=0;n<HEXDUMP_LINE_SIZE;n++)
		{
			if (i >= DataLen)
				sprintf(tmp,"%s","   ");
			else
				sprintf(tmp,"%02x ",Data[i]);
			strcat(tmp1,tmp);
			if ((Data[i] < 0x20) || (Data[i] > 0x7F))
				sprintf(tmp2+strlen(tmp2),"%c",'.');
			else
				sprintf(tmp2+strlen(tmp2),"%c",Data[i]);
			i++;
		}
		printf("%s",tmp1);
		printf("|%s|",tmp2);

		printf("\n");
	} while (i < DataLen);

	printf("\n");

}

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
	printf("    -d, --dump {0:1}          Synonym for Hexdump where 0 is OFF and 1 is ON\n");
	printf("    -f, --file <filename>     Load string from file\n");
	printf("    -i, --input '<HEXSTRING>' Load string from command line\n");
	printf("    <HEXSTRING>               String of Bytes in hex format, e.g. '443266'.\n");
	printf("    Note: If no hexstring is provided on the command line, the user is prompted to enter it.");
	printf("\n");
	exit(0);
}

int asc2hex(char * ibuf, char * obuf)
{
	int i,j;
	char tmp[4];

	memset(obuf,0x00,sizeof(obuf));
	i = 0;
	j = 0;
	do
	{
		sprintf(tmp,"%02x",ibuf[i++]);
		strncat(obuf,tmp,strlen(tmp));
	} while (i<strlen(ibuf));

	return(i);
}

int main(int argc, char * argv[])
{
	FILE * fp;
	int i,j,k;
	char c;
	char tmp[4];


	int cl;
	int gotin = 0;
	char buf[120];

	while (1)
    {
		// parse args
		static struct option long_options[] =
		{
			/* These options set a flag. */
			{"verbose",   no_argument,   &verbose_flag, 1},
			{"brief",     no_argument,   &verbose_flag, 0},
			{"hexdump",   no_argument,        &hexdump_flag, 1},
			{"nohexdump", no_argument,        &hexdump_flag, 0},
			/* These options don’t set a flag.
				 We distinguish them by their indices. */
			{"version", no_argument,       0, 'v'},
			{"help",    no_argument,       0, 'h'},
			{"dump",    no_argument,       0, 'd'},
			{"input",   required_argument, 0, 'i'},
			{"file",    required_argument, 0, 'f'},
			{0, 0, 0, 0}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;

		cl = getopt_long (argc, argv, "vhdc:d:f:i:",
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

			case 'd':
				hexdump_flag = atoi(optarg);
				break;

			case 'v':
				printf("Version: %d.%d\n",Major,Minor);
				exit(0);
				break;

			case 'h':
				usage(argv[0]);
				break;

			case 'f':
				printf ("Loading input from file: `%s'\n", optarg);
				fp = fopen (optarg,"r");
				if (fp != NULL)
				{
					while( ( c = fgetc(fp) ) != EOF ) {
						sprintf(buf,"%c",c);
						strcat(inbuf,buf);
					}
    				fclose (fp);
					gotin = 1;
				}
				else
				{
					printf("Error opening file '%s'!\n",optarg);
				}
				break;

			case 'i':
				strcpy(inbuf,optarg);
				gotin = 1;
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
			printf("Enter hex string (e.g. '424f54'): ");
			scanf("%78s",inbuf);
		}

	}

	asc2hex(inbuf,outbuf);

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
