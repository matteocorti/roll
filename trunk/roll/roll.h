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

/* data types */

#define OP_DICE   1
#define OP_NUMBER 2
#define OP_PLUS   3
#define OP_REP    4
#define OP_TIMES  5
#define OP_DIV    6

/*!
 * \struct node
 * \brief Parse tree node
 */
struct node {
  int           op;    /*!< node type  */
  struct node * left;  /*!< left node  */
  struct node * right; /*!< right node */
};

/* function prototypes */

void usage();
void error(char * message);
struct node * new_node(struct node * left, int op, struct node * right);

extern int  roll(int dice);
