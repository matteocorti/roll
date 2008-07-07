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

int sum_flag     = FALSE; /**< command line argument: sum series     */
static int verbose_flag = FALSE; /**< command line argument: verbose output */
static int version_flag = FALSE; /**< command line argument: version        */

/**
 * Prints the program's usage
 */
void usage() {
  
  printf("\nusage: %s [OPTION] expression\n\n", PACKAGE_NAME);
  printf("Options\n");
  printf(" -h, --help         show this help screen\n");
  printf(" -s, --sum-series   show the sum of roll series\n");
  printf(" -v, --verbose      increase verbosity\n");
  printf("     --version      prints the program version and exits\n");
  printf("\nPlease see the %s(1) man page for full documentation\n\n", PACKAGE_NAME);

}

/**
 * Prints the specified error message and exits with a failure status
 * @param message error message
 */
void error(char * message) {
  fprintf(stderr, "\nError: %s\n", message);
  exit(EXIT_FAILURE);
}

/** Wrapper for roll(int dice) translates special dices (e.g., d%)
 * @param sides sides of the dice
 */
int roll_dice(int sides) {
  if (sides != HUNDRED) {
    return roll(sides);
  } else {
      /* d100 -> d10*10+d10 */
    int  d1 = roll(10);
    int d10 = roll(10) % 10;
    if (d1 == 0 && d10 == 0) {
      return 100;
    } else if (d10 == 0) {
      return d1;
    } else {
      return d10*10 + d1;
    }
  }
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
      {"sum-series",  no_argument,       NULL, 's'},
      {"verbose",     no_argument,       NULL, 'v'},
      {"version",     no_argument,       &version_flag, TRUE},
      {"help",        no_argument,       NULL, 'h'},
      {NULL, 0, NULL, 0}
    };

    /* getopt_long stores the option index here. */
    int option_index = 0;
     
    c = getopt_long (argc, argv, "hvs",
		     long_options, &option_index);
    
    /* Detect the end of the options. */
    if (c == -1)
      break;
     
    switch (c) {

    case 'v':
      verbose_flag = TRUE;
      break;

    case 's':
      sum_flag = TRUE;
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

/**
 * Allocates a new IR node
 * @return newly allocated node
 */
struct ir_node * allocate_node ( void  ) {

  struct ir_node * node = malloc(sizeof(struct ir_node));
  if (node == NULL) {
    error("Out of memory\n");
    exit(EXIT_FAILURE);
  }

  return node;
  
}

/**
 * Allocates a new NUMBER node
 * @param number number value
 * @return a NUMBER node
 */
struct ir_node * new_number ( int number ) {

  struct ir_node * node = allocate_node();
  node->op    = OP_NUMBER;
  node->value = number;
  node->left  = NULL;
  node->right = NULL;

  return node;

}

/**
 * Comparison function for qsort
 * @param p1 first integer
 * @param p2 second integer
 */
int compare(const void * p1, const void * p2) {

  const int i1 = *((const int *)p1);
  const int i2 = *((const int *)p2);

  if (i1 > i2) {
    return 1;
  } else if (i1 < i2) {
    return -1;
  } else {
    return 0;
  }
  
}

/**
 * Allocates a new OP node
 * @param op operation
 * @param left left operand
 * @param right right operand
 * @return an OP node
 */
struct ir_node * new_op ( unsigned short int op, struct ir_node * left, struct ir_node * right) {

  struct ir_node * node = allocate_node();
  node->op    = op;
  node->value = 0;
  node->left  = left;
  node->right = right;
  return node;
  
}

/**
 * Allocates a new DICE node
 * @param sides a node representing the number of dice sides
 * @return a DICE node
 */
struct ir_node * new_dice ( struct ir_node * sides) {
  
  struct ir_node * node = allocate_node();
  node->op    = OP_DICE;
  node->value = 0;
  node->left  = NULL;
  node->right = sides;
  return node;
  
}

/**
 * Roll dices and compute expressions
 * @param node the root of the expression tree to compute
 * @param print set to true to print the result of the expression
 * @return the expression value
 */
int roll_expression ( struct ir_node * node, int print ) {

  int return_value = 0;
  int sum;
  int i;
  int sides;
  int repetitions;
  int high;
  int low;
  int * results;

  struct ir_node * cur;

  cur = node;
  while (cur != NULL) {

    sum = 0;
    
    switch (cur->op) {
    
    case OP_NUMBER:
      sum = cur->value;
      break;
      
    case OP_DICE:
      if (cur->left != NULL) {
        for (i = 0; i < roll_expression(cur->left, FALSE); i++) {
          sum += roll_dice( roll_expression(cur->right, FALSE) );
        }
      } else {
        sum = roll_dice( roll_expression(cur->right, FALSE) );
      }
      break;
      
    case OP_PLUS:
      sum =
        roll_expression( cur->left,  FALSE )
        +
        roll_expression( cur->right, FALSE );
      break;
      
    case OP_MINUS:
      sum =
        roll_expression( cur->left,  FALSE )
        -
        roll_expression( cur->right, FALSE );
      break;
      
    case OP_TIMES:
      sum =
        roll_expression( cur->left,  FALSE )
        *
        roll_expression( cur->right, FALSE );
      break;
      
    case OP_DIV:
      sum = (int)
        ceil( (float)roll_expression( cur->left,  FALSE ) /
              roll_expression( cur->right, FALSE ) );
      break;
      
    case OP_HIGH:
      
      sides       = roll_expression(cur->right->right, FALSE);
      repetitions = 1;
      high        = roll_expression(cur->left, FALSE);      
      
      if (cur->right->left != NULL) {
        repetitions = roll_expression(cur->right->left, FALSE);
      }

      /* array to store the results to sort */
      if (!(results = malloc(sizeof(int)*repetitions))) {
        error("Out of memory");
      }
      
      for(i=0; i<repetitions; i++) {
        results[i] = roll_dice(sides);
      }
      qsort(results, repetitions, sizeof(int), &compare);

      for(i=(repetitions-high); i<repetitions; i++) {
        sum += results[i];
      }
      
      free(results);
      
      break;
      
    case OP_LOW:
      
      sides       = roll_expression(cur->right->right, FALSE);
      repetitions = 1;
      low         = roll_expression(cur->left, FALSE);
      
      if (cur->right->left != NULL) {
        repetitions = roll_expression(cur->right->left, FALSE);
      }
      
      printf("low = %i, rep = %i\n", low, repetitions);
            
      /* array to store the results to sort */
      if (!(results = malloc(sizeof(int)*repetitions))) {
        error("Out of memory");
      }
      
      for(i=0; i<repetitions; i++) {
        results[i] = roll_dice(sides);
      }
      qsort(results, repetitions, sizeof(int), &compare);
      for(i=0; i<low; i++) {
        sum += results[i];
      }
      
      free(results);
      
      break;
      
    default :
      fprintf(stderr, "Implementation error: unkown IR node with code %i\n", cur->op);
      exit(EXIT_FAILURE);
    }

    return_value += sum;
    if (print == TRUE) {
      printf("%i\n", sum);
    }

    cur = cur->next;

  }

  
  return return_value;
  
}
