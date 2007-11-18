/* Copyright (c) 2005, 2006, 2007  Matteo Corti
 * This file is part of roll
 *
 * You may distribute this file under the terms the GNU General Public
 * License.  See the file COPYING for more information.
 */

/**
 * @file   roll.c
 * @author Matteo Corti
 * @brief  The main application file
 */

#include "roll.h"

static        int    verbose_flag = FALSE; /**< command line argument: verbose output */
static        int    version_flag = FALSE; /**< command line argument: version        */

static struct node * tree         = FALSE; /**< root of the parse tree */

/**
 * Prints the program's usage
 */
void usage() {
  
  printf("\nusage: %s [OPTION] expression\n\n", PACKAGE_NAME);
  printf("Options\n");
  printf(" -h, --help         show this help screen\n");
  printf(" -v, --verbose      increase verbosity\n");
  printf("     --version      prints the program version and exits\n");
  printf("\nPlease see the %s(1) man page for full documentation\n\n", PACKAGE_NAME);

}

/**
 * Allocates a parse tree node
 * @param left  left branch
 * @param op    node type
 * @param right right branch
 */
struct node * new_node(struct node * left, int op, struct node * right) {
  struct node * node = malloc(sizeof(struct node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->left  = left;
  node->op    = op;
  node->right = right;
  return node;
}

/**
 * Prints the specified error message and exits with a failure status
 * @param message error message
 */
void error(char * message) {
  fprintf(stderr, "\nError: %s\n", message);
  exit(EXIT_FAILURE);
}

/** Rolls an n-sided dice
 * @param dice number of sides of the rolled dice
 * @return     result of the dice roll
 */
int roll(int dice) {

  /* 
   * In: W. H. Press et al,Numerical Recipes in C: The Art of
   * Scientific Computing.  New York, Cambridge University Press,
   * 1992, 2nd ed., p. 277
   *
   * "If you want to generate a random integer between 1 
   *  and 10, you should always do it by using high-order *
   *  bits, as in
   *
   *  j=1+(int) (10.0*rand()/(RAND_MAX+1.0));
   */

  int res = 1+(int)(((double)dice)*random()/(RAND_MAX+1.0));
  if (verbose_flag) {
    printf("d%i -> %i\n", dice, res);
  }

  return res;

}

void debug_parse_tree (struct node * n) {
  printf("[ ");
  if (n->left != NULL) {
    debug_parse_tree(n->left);
  }
  printf(" %i ", n->op);
  if (n->right != NULL) {
    debug_parse_tree(n->right);
  }
  printf(" ]");
}

/**
 * Main program
 * @param argc number of command line arguments
 * @param argv array of strings with the command line arguments
 */
int main(int argc, char **argv) {

  int    c;
  char   expression[EXPRESSION_SIZE];
  int    expression_size;
  size_t argument_size;

  srandomdev();
     
  while (TRUE) {

    static struct option long_options[] = {
      {"verbose",     no_argument,       NULL, 'v'},
      {"version",     no_argument,       &version_flag, TRUE},
      {"help",        no_argument,       NULL, 'h'},
      {NULL, 0, NULL, 0}
    };

    /* getopt_long stores the option index here. */
    int option_index = 0;
     
    c = getopt_long (argc, argv, "hv",
		     long_options, &option_index);
    
    /* Detect the end of the options. */
    if (c == -1)
      break;
     
    switch (c) {

    case 'v':
      verbose_flag = TRUE;
      break;

    case 'h':
      usage();
      exit(0);

    case '?':
      usage();
      /* getopt_long already printed an error message. */
      exit(EXIT_SUCCESS);
      
    case 0:
      break;

    default:
      abort ();
    }

  }

  if (version_flag) {
    printf("%s %s\n", PACKAGE_NAME, PACKAGE_VERSION);
    exit(EXIT_SUCCESS);
  }      

  argc -= optind;
  argv += optind;         
  
  /* build string to parse */
  expression[0] = '\0';
  expression_size = 0;
  while(argc>0) {
    argument_size = strlen(*argv);
    expression_size += argument_size;
    if (expression_size >= EXPRESSION_SIZE) {
      error("Expression too long!\n");
    }
    strncat(expression, *argv, EXPRESSION_SIZE);
    argc--;
    argv++;
  }
  
  if (expression_size > 0) {
    yy_scan_string(expression);
    yyparse();
  } else {
    error("No expression provided!\nPlease use the \"-h\" option.\n");
    exit(EXIT_FAILURE);
  }

  return 0;

}
