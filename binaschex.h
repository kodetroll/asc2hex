// binaschex - A library that supports converting ASCII/BINARY/HEX values
// expressed as strings. E.g. the form of '4142434445' (hex) is taken
// and converted to the binary represented by the hex digits. e.g.
// 'abcde'.
//
// (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
// File: binaschex.h - Header file for binaschex.c
// Author: Kodetroll
// Date: April 2015
// Version: 0.99a (First to receive a version number)
//
// Includes code from strrep.c - C substring replacement by Drew Hess <dhess-src@bothan.net>.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>

#ifndef __BINASCHEX_H__
#define __BINASCHEX_H__

//=== Global Definitions ====================================================================================

//#define Major 0
//#define Minor 99
#define BINASCHEX_LIB_VER 20150407
#define HEXDUMP_LINE_SIZE 16

//=== Global Variables ======================================================================================

extern int print_flag;

//=== Global Prototypes =====================================================================================

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
char* strrep(const char *s1, const char *s2, const char *s3);

unsigned int cvt2int(char* ibuf);

/* Converts a single char representing a hex number '0-9,A-F,a-f'
 * to it's numeric integer value. e.g. '1' (0x31) returns 0x01
 *
 */
int hex2int(char c);

/* This function takes the contents of the input buffer (ibuf) and copies them to
 * the output buffer (obuf), converting the expressed hexadecimal value of the
 * input buffer to it's ASCII character, on the fly. E.g. '41424364' becomes
 * 'ABCd'. The return value of the function is the number of characters in the
 * output buffer after conversion (obuf length).
 *
 */
int hex2asc(char * ibuf, char * obuf);

/* This function takes the contents of the input buffer (ibuf) and copies them to
 * the output buffer (obuf), converting the integer value of the ASCII character
 * in the input buffer to it's hex representation, on the fly. E.g. 'ABCd' becomes
 * '41424364'. The return value of the function is the number of characters converted
 * to the output buffer (ibuf length).
 *
 */
int asc2hex(char * ibuf, char * obuf);

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
void HexDataDump(int DataLen, unsigned char * Data);

#endif	// __BINASCHEX_H__