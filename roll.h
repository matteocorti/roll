/* Copyright (c) 2005, 2006, 2007  Matteo Corti
 * This file is part of roll
 *
 * You may distribute this file under the terms the GNU General Public
 * License.  See the file COPYING for more information.
 */

/**
 * @file   roll.h
 * @author Matteo Corti
 * @brief  The main include file
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <time.h>
#include "config.h"

/** @def TRUE
 * Boolean true
 */
#define TRUE  1

/** @def FALSE
 * Boolean false
 */
#define FALSE 0


/** @todo The maximum expression length should be dynamic */
/** @def EXPRESSION_SIZE
 * Maximum expression length
 */
#define EXPRESSION_SIZE 1024

/** @def HUNDRED
 * Constant representing a 1d100 rolled with 1d10 for the units and 1d10 for the tens
 */
#define HUNDRED         -1

#ifndef HAVE_SRANDOMDEV

#ifdef HAVE_GETPID

#include <sys/types.h>
#include <unistd.h>

/** @def srandomdev
 * defines srandomdev usig srand of the current time
 * bitwise anded with the PID if srandomdev is missing
 */
#define srandomdev() srand((unsigned) time(NULL) & getpid())

#else

/** @def srandomdev
 * defines srandomdev usig srand of the current time
 * if srandomdev and getpid are missing
 */
#define srandomdev() srand((unsigned) time(NULL))

#endif

#endif

/* function prototypes */

void usage();
void error(char * message);

extern int  roll(int dice);
