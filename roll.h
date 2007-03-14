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
