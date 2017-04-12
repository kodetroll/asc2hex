// asc2hex - A program that takes a string of the form 'ABCDE' and converts
// it to the form of '4142434445' (hex)
//
// (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
// File: asc2hex.h - Header file for asc2hex.c
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

#ifndef __ASC2HEX_H__
#define __ASC2HEX_H__

//=== Global Definitions ====================================================================================

//#define Major 0
//#define Minor 99
#define BINASCHEX_LIB_VER 20150407
#define HEXDUMP_LINE_SIZE 16

//=== Global Variables ======================================================================================

extern int print_flag;
extern int unpar_flag;

//=== Global Prototypes =====================================================================================

#endif	// __ASC2HEX_H__