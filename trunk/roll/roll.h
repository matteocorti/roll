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
#include <math.h>
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

/* parse tree nodes */

#define OP_NUMBER 1 /*!< Number node               */
#define OP_TIMES  2 /*!< Multiplication node       */
#define OP_DIV    3 /*!< Integer division node     */
#define OP_DICE   4 /*!< N-sided dice node         */
#define OP_PLUS   5 /*!< Addition node             */
#define OP_MINUS  6 /*!< Subtraction node          */
#define OP_HIGH   7 /*!< Keep highest results node */
#define OP_LOW    8 /*!< Keep lowest resutls node  */

/**
 * @struct ir_node
 * @brief  node of the intermediate representation parse tree
 *
 * Node of the intermediate representation parse tree
 */
struct ir_node {
  struct ir_node * left;  /*!< Left branch        */
  struct ir_node * right; /*!< Right branch       */
  struct ir_node * next;  /*!< Next tree          */
  unsigned short int op;  /*!< Node type          */
  int value;              /*!< Optiona node value */
};

/* function prototypes */

void usage();
void error(char * message);

extern int  roll(int dice);
extern int roll_expression ( struct ir_node * node, int print );

struct ir_node * allocate_node ( void  );
struct ir_node * new_number    ( int number );
struct ir_node * new_op        ( unsigned short int op, struct ir_node * left, struct ir_node * right);
struct ir_node * new_dice      ( struct ir_node *  sides);
