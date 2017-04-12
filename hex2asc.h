// hex2asc - A library that supports converting ASCII/BINARY/HEX values
// expressed as strings. E.g. the form of '4142434445' (hex) is taken
// and converted to the binary represented by the hex digits. e.g.
// 'abcde'.
//
// (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
// File: hex2asc.h - Header file for hex2asc.c
// Author: Kodetroll
// Date: April 2017
// Version: 0.99a (First to receive a version number)
//
// Includes code from strrep.c - C substring replacement by Drew Hess <dhess-src@bothan.net>.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>

#ifndef __HEX2ASC_H__
#define __HEX2ASC_H__

//=== Global Definitions ====================================================================================

//#define Major 0
//#define Minor 99
#define BINASCHEX_LIB_VER 20150407
#define HEXDUMP_LINE_SIZE 16

//=== Global Variables ======================================================================================

extern int print_flag;
extern int unpar_flag;

//=== Global Prototypes =====================================================================================

#endif	// __HEX2ASC_H__