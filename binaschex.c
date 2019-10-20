// binaschex - A library that supports converting ASCII/BINARY/HEX values
// expressed as strings. E.g. the form of '4142434445' (hex) is taken
// and converted to the binary represented by the hex digits. e.g.
// 'abcde'.
//
// (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
// File: binaschex.c - C Source file for binaschex
// Author: Kodetroll
// Date: April 2015
// Version: 0.99a (First to receive a version number)
//
// Includes code from strrep.c - C substring replacement by Drew Hess <dhess-src@bothan.net>.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "binaschex.h"

//=== Global Definitions ====================================================================================

//=== Global Variables ======================================================================================

char sbuf[250];							// for string processing (rpad, lpad, etc)
char tmpbuf[250];						// for file & printf operations

//=== Global Prototypes =====================================================================================

char* ucase(const char * s);
char* lcase(const char * s);
char* lpad(const char * s, int c, int len);
char* rpad(const char * s, int c, int len);
char* chomp(const char * s);

//=== Start of Utility functions ============================================================================

/* This method will convert any lowercase chars in a string
 * to uppercase and return the string
 *
 */
char*
ucase(const char * s)
{
    //string n,y;
    char x[250];
    int c,i;

    memset(x,0x00,sizeof(x));
    strcpy(x,s);

    memset(sbuf,0x00,sizeof(sbuf));
    for (i=0;i<strlen(x);i++)
		sbuf[i] = toupper(x[i]);

    return(sbuf);
}

/* This method will convert any uppercase chars in a string
 * to lowercase and return the string
 *
 */
char*
lcase(const char * s)
{
    //string n,y;
    char x[250];
    int c,i;

    memset(x,0x00,sizeof(x));
    strcpy(x,s);

    memset(sbuf,0x00,sizeof(sbuf));
    for (i=0;i<strlen(x);i++)
		sbuf[i] = tolower(x[i]);

    return(sbuf);
}

/* This method will pad the provided char string to the
 * left, out to the specified length using the specified
 * padding char. Returns the char string.
 */
char*
lpad(const char * s, int c, int len)
{
	strcpy(sbuf,s);

	if (len <= strlen(s))
		return(sbuf);

	do
	{
		memset(tmpbuf,0x00,sizeof(tmpbuf));
		strcpy(tmpbuf,sbuf);
		memset(sbuf,0x00,sizeof(sbuf));
		sbuf[0] = c;
		strcat(sbuf,tmpbuf);
	} while(strlen(sbuf) <= len-1);

	return(sbuf);

}

/* This method will pad the provided char string to the
 * right, out to the specified length using the specified
 * padding char. Returns the char string.
 */
char*
rpad(const char * s, int c, int len)
{
	int i = strlen(s);

	memset(sbuf,0x00,sizeof(sbuf));
	//printf("s: %s\n",s);
	if (len < strlen(s))
	{
		strncpy(sbuf,s,len);
		//printf("sbuf1: %s\n",sbuf);
		return(sbuf);
	}

	if (c == 0)
		c = 0x20;

	strcpy(sbuf,s);
	//printf("sbuf2: %s\n",sbuf);
	do { sbuf[i++] = c; } while (i < len);
	//printf("sbuf3: %s\n",sbuf);
	return(sbuf);

}

char*
chomp(const char * s)
{
	int l = strlen(s);
	int i = 0;
	int num_ws;
	char * y;

	//memset(y,0x00,sizeof(y));

	if ((strlen(s) == 0) || (s == NULL) || (s == ""))
		return("");

	y = strdup(s);

	//printf("s: '%s' (%d)\n",s,strlen(s));
	//printf("y: '%s' (%d)\n",y,strlen(y));
	//show_hexdump("y",y);

	int ws[] = { 0x00, 0x0a, 0x0d, '\t', ' ' };

	//printf("sizeof: %d\n",sizeof(ws));
	num_ws = sizeof(ws) / 4;
	//printf("num_ws: %d\n",num_ws);
	int o = 0;
	do
	{
		o = 0;
		//printf("l: %d, y[%d]: '%c' (%d)\n",l,l,y[l],y[l]);
		for (i=0;i<num_ws;i++)
			if (y[l] == ws[i])
				o = 1;
		//printf("o: %d\n",o);
		if (o == 1)
			y[l] = 0x00;
		l--;
	} while (o == 1);

	//printf("y: '%s' (%d)\n",y,strlen(y));
	//show_hexdump("y",y);

	return(y);
}

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
char*
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

unsigned int
cvt2int(char* ibuf)
{
	char *p;
	int sum = 0;
	int i,k,n,b;

	//printf("ibuf(%d): '%s'\n",strlen(ibuf),ibuf);
	p = strdup(lpad(ibuf,'0',8));

	//printf("p(%d): '%s'\n",strlen(p),p);

	for (i=0;i<strlen(ibuf);i++)
	{
		k = strlen(ibuf)-i-1;
		n = hex2int(ibuf[i]);
		b = pow (16, k);
		//printf("i: %d, k: %d, strlen(ibuf): %d, ibuf[%d]: '%c' (0x%02x), n: %d, b: 0x%02x \n",i,k,strlen(ibuf),k,ibuf[i],ibuf[i],n,b);

		sum+= n * b;
		//printf("sum: '%d' 0x%02x\n",sum,sum);
	}

	//printf("sum: '%d' 0x%02x\n",sum,sum);
	return(sum);

}

/* Converts a single char representing a hex number '0-9,A-F,a-f'
 * to it's numeric integer value. e.g. '1' (0x31) returns 0x01
 *
 */
int
hex2int(char c)
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

/* This function takes the contents of the input buffer (ibuf) and copies them to
 * the output buffer (obuf), converting the expressed hexadecimal value of the
 * input buffer to it's ASCII character, on the fly. E.g. '41424364' becomes
 * 'ABCd'. The return value of the function is the number of characters in the
 * output buffer after conversion (obuf length).
 *
 */
int
hex2asc(char * ibuf, char * obuf)
{
	int i,j,c;
	//char c;

	// Convert string from Hex ASCII chars to binary form
	memset(obuf,0x00,sizeof(obuf));
	i = 0;
	j = 0;
	do
	{
		c = hex2int(ibuf[i++]) * 16;
		c += hex2int(ibuf[i++]);
		if (unpar_flag == 1)
			if (c > 0x7f)
				c -= 0x80;

		if (print_flag == 1)
			if ((c < 0x20) || (c > 0x7f))
				c = 0x2e;

		obuf[j++] = (char)c;
	} while(i < strlen(ibuf));

	return(j);
}

/* This function takes the contents of the input buffer (ibuf) and copies them to
 * the output buffer (obuf), converting the integer value of the ASCII character
 * in the input buffer to it's hex representation, on the fly. E.g. 'ABCd' becomes
 * '41424364'. The return value of the function is the number of characters converted
 * to the output buffer (ibuf length).
 *
 */
int
asc2hex(char * ibuf, char * obuf)
{
	int i,j,k;
	char tmp[4];

	memset(obuf,0x00,sizeof(obuf));
	i = 0;
	j = 0;
	do
	{
		k = ibuf[i++];
		if (unpar_flag == 1)
			if (k > 0x7F)
				k -= 0x80;
		sprintf(tmp,"%02x",k);
		strncat(obuf,tmp,strlen(tmp));
	} while (i<strlen(ibuf));

	return(i);
}

/*
 * This function provides a generalized hexdump facility. Data to be displayed should be provided
 * via the *Data pointer. The length of the data string should be included in DataLen. Making this
 * zero will use the strlen value, making this -1 will use the sizeof value. This value must be
 * provided if there are ASCII NULs in the string, as string processing will be terminated at the
 * first NULL ('\0') found, unless the DataLen value is provided with a non-zero positive value.
 * Output to the screen will be od the standard hexdump Format:
 *     'MMMM: HH HH HH ... HH |ASCII.STRING VALUES|'
 *
 */

void
HexDataDump(int DataLen, unsigned char * Data)
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

