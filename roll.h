/* Copyright (c) 2005, 2006, 2007  Matteo Corti
 * This file is part of roll
 *
 * You may distribute this file under the terms the GNU General Public
 * License.  See the file COPYING for more information.
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <time.h>
#include "config.h"

/* booleans */

#define TRUE  1
#define FALSE 0

/* various constants */
#define EXPRESSION_SIZE 1024
#define HUNDRED         -1

/* missing functions */
#ifndef HAVE_SRANDOMDEV

#ifdef HAVE_GETPID

#include <sys/types.h>
#include <unistd.h>

#define srandomdev() srand((unsigned) time(NULL) & getpid())

#else
#define srandomdev() srand((unsigned) time(NULL))
#endif

#endif

/* function prototypes */

void usage();
void error(char * message);

extern int  roll(int dice);
