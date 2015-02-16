// hex2asc - A program that takes a string in the form of '4142434445' (hex)
// and converts it to the binary represented by the hex digits. e.g.
// 'abcde'.
//
// (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
// Author: Kodetroll
// Date: January 2015
// Version: 0.99 (First to receive a version number)
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
//
//	If no hexstring is provided on the command line, the user is prompted to enter it.
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

int hex2int(char c);
void HexDataDump(int DataLen, unsigned char * Data);
void usage(char * name);

//=== Start of Utility functions ============================================================================

/*
 * This function returns string s1 if string s2 is an empty string, or
 * if s2 is not found in s1. If s2 is found in s1, the function
 * returns a new null-terminated string whose contents are identical
 * to s1, except that all occurrences of s2 in the original string s1
 * are, in the new string, replaced by the string s3. The caller owns
 * the new string.
 *
 * Strings s1, s2, and s3 must all be null-terminated strings. If any
 * of s1, s2, or s3 are NULL, the function returns NULL, indicating an
 * error condition. If any other error occurs, the function returns
 * NULL.
 *
 * This code is written pedantically, primarily so that asserts can be
 * used liberally. The code could certainly be optimized and/or made
 * less verbose, and I encourage you to do that if you use strstr in
 * your production code, once you're comfortable that it functions as
 * intended. Each assert makes plain an invariant condition that is
 * assumed to be true by the statement(s) that immediately follow the
 * assert. Some of the asserts are trivially true, as written, but
 * they're included, nonetheless, in case you, in the process of
 * optimizing or adapting the code for your own purposes, make a
 * change that breaks an assumption made downstream by the original
 * code.
 */

// strrep() substring replacement by Drew Hess <dhess-src@bothan.net>.
char *
strrep(const char *s1, const char *s2, const char *s3)
{
	if (!s1 || !s2 || !s3)
		return 0;
	size_t s1_len = strlen(s1);
	if (!s1_len)
		return (char *)s1;
	size_t s2_len = strlen(s2);
	if (!s2_len)
		return (char *)s1;

	/*
	* Two-pass approach: figure out how much space to allocate for
	* the new string, pre-allocate it, then perform replacement(s).
	*/

	size_t count = 0;
	const char *p = s1;
	assert(s2_len); /* otherwise, strstr(s1,s2) will return s1. */
	do {
		p = strstr(p, s2);
		if (p) {
			p += s2_len;
		++count;
		}
	} while (p);

	if (!count)
		return (char *)s1;

	/*
	* The following size arithmetic is extremely cautious, to guard
	* against size_t overflows.
	*/
	assert(s1_len >= count * s2_len);
	assert(count);
	size_t s1_without_s2_len = s1_len - count * s2_len;
	size_t s3_len = strlen(s3);
	size_t newstr_len = s1_without_s2_len + count * s3_len;
	if (s3_len &&
		((newstr_len <= s1_without_s2_len) || (newstr_len + 1 == 0)))
		/* Overflow. */
		return 0;

	char *newstr = (char *)malloc(newstr_len + 1); /* w/ terminator */
	if (!newstr)
		/* ENOMEM, but no good way to signal it. */
		return 0;

	char *dst = newstr;
	const char *start_substr = s1;
	size_t i;
	for (i = 0; i != count; ++i) {
		const char *end_substr = strstr(start_substr, s2);
		assert(end_substr);
		size_t substr_len = end_substr - start_substr;
		memcpy(dst, start_substr, substr_len);
		dst += substr_len;
		memcpy(dst, s3, s3_len);
		dst += s3_len;
		start_substr = end_substr + s2_len;
	}

	/* copy remainder of s1, including trailing '\0' */
	size_t remains = s1_len - (start_substr - s1) + 1;
	assert(dst + remains == newstr + newstr_len + 1);
	memcpy(dst, start_substr, remains);
	assert(strlen(newstr) == newstr_len);
	return newstr;
}

/* Converts a single char representing a hex number '0-9,A-F,a-f'
 * to it's numeric integer value. e.g. '1' (0x31) becomes 1
 *
 */
int hex2int(char c)
{
	switch(c)
	{
		case '0':
			return(0);
			break;
		case '1':
			return(1);
			break;
		case '2':
			return(2);
			break;
		case '3':
			return(3);
			break;
		case '4':
			return(4);
			break;
		case '5':
			return(5);
			break;
		case '6':
			return(6);
			break;
		case '7':
			return(7);
			break;
		case '8':
			return(8);
			break;
		case '9':
			return(9);
			break;
		case 'a':
			return(10);
			break;
		case 'b':
			return(11);
			break;
		case 'c':
			return(12);
			break;
		case 'd':
			return(13);
			break;
		case 'e':
			return(14);
			break;
		case 'f':
			return(15);
			break;
		case 'A':
			return(10);
			break;
		case 'B':
			return(11);
			break;
		case 'C':
			return(12);
			break;
		case 'D':
			return(13);
			break;
		case 'E':
			return(14);
			break;
		case 'F':
			return(15);
			break;
		default:
			return(0);
			break;
	}
}


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

int main(int argc, char * argv[])
{
	FILE * fp;
	int i,j,k;
	char c;
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

	// remove whitespace from string
	memset(buf,0x00,sizeof(buf));
	strcpy(buf,strrep(inbuf, " ", ""));

	// remove CR/LF from string (file input mostly)
	memset(inbuf,0x00,sizeof(inbuf));
	strcpy(inbuf,strrep(buf, "\n", ""));

	// Convert string from Hex ASCII chars to binary form
	memset(outbuf,0x00,sizeof(outbuf));
	i = 0;
	j = 0;
	do
	{
		c = hex2int(inbuf[i++]) * 16;
		c += hex2int(inbuf[i++]);
		outbuf[j++] = c;
	} while(i < strlen(inbuf));

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
