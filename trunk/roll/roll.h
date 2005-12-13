#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>

/* booleans */

#define TRUE  1
#define FALSE 0

/* item types */

#define DICE   1
#define NUMBER 2

/* various constants */
#define EXPRESSION_SIZE 1024

/* missing functions */
#ifndef HAVE_SRANDOMDEV
#define srandomdev() srand((unsigned) time(NULL)) 
#endif

/* function prototypes */

void usage();
void error(char * message);
int  roll(int dice);
