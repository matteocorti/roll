/* Copyright (c) 2005-2011  Matteo Corti
 * This file is part of roll
 *
 * You may distribute this file under the terms the GNU General Public
 * License.  See the file COPYING for more information.
 */

/*!
 * \file   roll.c
 * \author Matteo Corti
 * \brief  The main application file
 */

#include "roll.h"

int sum_flag     = FALSE; /**< command line argument: sum series     */
static int verbose_flag = FALSE; /**< command line argument: verbose output */
static int version_flag = FALSE; /**< command line argument: version        */

extern int positive_flag = FALSE; /**< command line argument: allow only positive results */

#ifdef DEBUG
int debug_flag = 0; /**< command line argument: debug output */
#endif


/*!
 * \brief Prints the program's usage
 */
void usage() {
  
  printf("\nusage: %s [OPTION] expression\n\n", PACKAGE_NAME);
  printf("Options\n");
  printf(" -p, --positive     allow only positive results\n");
  printf(" -h, --help         show this help screen\n");
  printf(" -s, --sum-series   show the sum of roll series\n");
  printf(" -v, --verbose      increase verbosity\n");
  printf("     --version      prints the program version and exits\n");
#ifdef DEBUG
  printf(" -d, --debug        debugging output\n");
#endif
  printf("\nPlease see the %s(1) man page for full documentation\n\n", PACKAGE_NAME);

}

/*!
 * \brief          Prints the specified error message and exits with a failure status
 * \param[message] error message
 */
void error(char * message) {
  fprintf(stderr, "\nError: %s\n", message);
  exit(EXIT_FAILURE);
}

/*!
 * \brief        Wrapper for roll(int dice) translates special dices (e.g., d%)
 * \param[sides] Sides of the dice
 */
int roll_dice(int sides) {

  int result = 0;
  int d10;
  int d1;
  
  if ( sides == HUNDRED ) {
    
    /* d100 -> d10*10+d10 */
    
    d10 = roll(10);
    if (verbose_flag) {
      printf("d10 -> %i\n", d10);
    }
    d10 = d10 % 10;
    
    d1 = roll(10);
    if (verbose_flag) {
      printf("d10 -> %i\n", d1);
    }
    
    if (d1 == 0 && d10 == 0) {
      result = 100;
    } else if (d10 == 0) {
      result = d1;
    } else {
      result = d10*10 + d1;
    }

  } else if ( sides == FUDGE_DICE ) {

    result = roll(3) - 2;

    if (verbose_flag) {

      switch (result) {
      case -1:
        printf("dF -> -\n");
        break;
      case 0:
        printf("dF -> o\n");
        break;
      case 1:
        printf("dF -> +\n");
        break;        
      }
    }
    
  } else {

    result = roll(sides);
    
    if (verbose_flag) {
      printf("d%i -> %i\n", sides, result);
    }

  }

  return result;
  
}

/*!
 * \brief       Rolls an n-sided dice
 * \param[dice] Number of sides of the rolled dice
 * \return      Result of the dice roll
 */
int roll(int dice) {

  /* 
   * In: W. H. Press et al,Numerical Recipes in C: The Art of
   * Scientific Computing.  New York, Cambridge University Press,
   * 1992, 2nd ed., p. 277
   *
   * "If you want to generate a random integer between 1 
   *  and 10, you should always do it by using high-order
   *  bits, as in
   *
   *  j=1+(int) (10.0*rand()/(RAND_MAX+1.0));
   */

  int res = 1+(int)(((double)dice)*random()/(RAND_MAX+1.0));

  return res;

}

/*!
 * \brief       Main program
 * \param[argc] Number of command line arguments
 * \param[argv] Array of strings with the command line arguments
 * \return      Exit status
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
      {"positive",    no_argument,       NULL, 'p'},
      {"verbose",     no_argument,       NULL, 'v'},
      {"version",     no_argument,       &version_flag, TRUE},
      {"help",        no_argument,       NULL, 'h'},
#ifdef DEBUG
      {"debug",       no_argument,       NULL, 'd'},
#endif
      {NULL, 0, NULL, 0}
    };

    /* getopt_long stores the option index here. */
    int option_index = 0;

#ifdef DEBUG
    c = getopt_long (argc, argv, "hvspd",
		     long_options, &option_index);
#else
    c = getopt_long (argc, argv, "hvsp",
		     long_options, &option_index);
#endif
    
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
      
    case 'p':
      positive_flag = TRUE;
      break;

    case 'h':
      usage();
      exit(0);

    case '?':
      usage();
      /* getopt_long already printed an error message. */
      exit(EXIT_SUCCESS);

#ifdef DEBUG
    case 'd':
      debug_flag++;
      break;      
#endif
      
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

/*!
 * \brief  Allocates a new IR node
 * \return Newly allocated node
 */
struct ir_node * allocate_node ( void  ) {

  struct ir_node * node = malloc(sizeof(struct ir_node));
  if (node == NULL) {
    error("Out of memory\n");
    exit(EXIT_FAILURE);
  }

  return node;
  
}

/*!
 * \brief         Allocates a new NUMBER node
 * \param[number] Number value
 * \return        A NUMBER node
 */
struct ir_node * new_number ( int number ) {

  struct ir_node * node = allocate_node();
  node->op    = OP_NUMBER;
  node->value = number;
  node->left  = NULL;
  node->right = NULL;

  return node;

}

/*!
 * \brief     Comparison function for qsort
 * \param[p1] First integer
 * \param[p2] Second integer
 * \return    1 if p1 > p2, -1 if p1 < p2 and 0 if p1 and p2 are equal
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

/*!
 * \brief        Allocates a new OP node
 * \param[op]    Operation
 * \param[left]  Left operand
 * \param[right] Right operand
 * \return       An OP node
 */
struct ir_node * new_op ( unsigned short int op, struct ir_node * left, struct ir_node * right) {

  struct ir_node * node = allocate_node();
  node->op    = op;
  node->value = 0;
  node->left  = left;
  node->right = right;
  return node;
  
}

/*!
 * \brief        Allocates a new DICE node
 * \param[sides] A node representing the number of dice sides
 * \return       A DICE node
 */
struct ir_node * new_dice ( struct ir_node * sides) {
  
  struct ir_node * node = allocate_node();
  node->op    = OP_DICE;
  node->value = 0;
  node->left  = NULL;
  node->right = sides;
  return node;
  
}

int checked_sum( int op1, int op2 ) {
  if ( (op2 > 0 && op1 > INT_MAX - op2) ||
       (op2 < 0 && op1 < INT_MIN - op2)) {
    error("Overflow");
  }
  return op1+op2;
}

int checked_multiplication( int op1, int op2 ) {
  int result = op1 * op2;
  if (op1 != 0 && result / op1 != op2 ) {
    error("Overflow");
  }
  return result;
}

/*!
 * \brief        Roll dices and compute expressions
 * \param[node]  The root of the expression tree to compute
 * \param[print] Set to true to print the result of the expression
 * \return       The expression value
 */
int roll_expression ( struct ir_node * node, int print ) {

  int  high;
  int  i;
  int  limit;
  int  low;
  int  repetitions;
  int  return_value = 0;
  int  sides;
  int  sum;
  int  tmp;
  int * results;

  struct ir_node * cur;
  
  cur = node;
  while (cur != NULL) {

    sum = 0;

    switch (cur->op) {
    
    case OP_NUMBER:
      sum = cur->value;
      break;

    case OP_REP:

      for (i = 0; i < roll_expression(cur->left, FALSE); i++) {
        sum = checked_sum( sum, roll_expression(cur->right, FALSE) );
      }
      break;
      
    case OP_DICE:
      sum = roll_dice( roll_expression(cur->right, FALSE) );
      break;
      
    case OP_PLUS:
      sum = checked_sum( roll_expression( cur->left,  FALSE ),
                         roll_expression( cur->right, FALSE ) );
      break;
      
    case OP_MINUS:
      sum = checked_sum( roll_expression( cur->left,  FALSE ),
                         -roll_expression( cur->right, FALSE ) );
      break;
      
    case OP_TIMES:
      sum = checked_multiplication( roll_expression( cur->left,  FALSE ),
                                   roll_expression( cur->right, FALSE ) );
      break;
      
    case OP_DIV:
      sum = (int)
        ceil( (float)roll_expression( cur->left,  FALSE ) /
              roll_expression( cur->right, FALSE ) );
      break;
      
    case OP_HIGH:

      sides       = roll_expression(cur->right->right->right, FALSE);
      repetitions = roll_expression(cur->right->left,  FALSE);
      high        = roll_expression(cur->left, FALSE);      

      /* array to store the results to sort */
      if (!(results = malloc(sizeof(int)*repetitions))) {
        error("Out of memory");
      }
      
      for(i=0; i<repetitions; i++) {
        results[i] = roll_dice(sides);
      }
      qsort(results, repetitions, sizeof(int), &compare);

      for(i=(repetitions-high); i<repetitions; i++) {
        sum = checked_sum( sum, results[i] );
      }
      
      free(results);
      
      break;
      
    case OP_LOW:
      
      sides       = roll_expression(cur->right->right->right, FALSE);
      repetitions = roll_expression(cur->right->left,  FALSE);
      low         = roll_expression(cur->left, FALSE);
      
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
      for(i=0; i<low; i++) {
        sum = checked_sum( sum, results[i] );
      }
      
      free(results);
      
      break;

    case OP_GT:
      
      limit = roll_expression(cur->right, FALSE);      
      tmp   = roll_expression(cur->left,  FALSE);
      while (tmp <= limit) {
        tmp = roll_expression(cur->left, FALSE);
      }
      sum = checked_sum( sum, tmp );
      
      break;
      
    case OP_GE:
      
      limit = roll_expression(cur->right, FALSE);      
      tmp   = roll_expression(cur->left,  FALSE);
      while (tmp < limit) {
        tmp = roll_expression(cur->left, FALSE);
      }
      sum = checked_sum( sum, tmp );
      
      break;
      
    case OP_LT:
      
      limit = roll_expression(cur->right, FALSE);      
      tmp   = roll_expression(cur->left,  FALSE);
      while (tmp >= limit) {
        tmp = roll_expression(cur->left, FALSE);
      }
      sum = checked_sum( sum, tmp );
      
      break;
      
    case OP_LE:
      
      limit = roll_expression(cur->right, FALSE);      
      tmp   = roll_expression(cur->left,  FALSE);
      while (tmp > limit) {
        tmp = roll_expression(cur->left, FALSE);
      }
      sum = checked_sum( sum, tmp );
      
      break;
      
    case OP_NE:
      
      limit = roll_expression(cur->right, FALSE);      
      tmp   = roll_expression(cur->left,  FALSE);
      while (tmp == limit) {
        tmp = roll_expression(cur->left, FALSE);
      }
      sum = checked_sum( sum, tmp );
      
      break;
      
    default :
      
      fprintf(stderr, "Implementation error: unkown IR node with code %i\n", cur->op);
      exit(EXIT_FAILURE);
      
    }

    return_value = checked_sum( return_value, sum);
    if (print == TRUE) {
      printf("%i\n", sum);
    }

    cur = cur->next;

  }

  
  return return_value;
  
}

#ifdef DEBUG

void print_node( struct ir_node * node) {

  switch (node->op) {
  case OP_NUMBER: printf("number (%i)", node->value); break;      
  case OP_DICE:   printf("dice"); break;
  case OP_PLUS:   printf("+"); break;
  case OP_MINUS:  printf("-"); break;
  case OP_TIMES:  printf("*"); break;
  case OP_DIV:    printf("/"); break;
  case OP_HIGH:   printf("high"); break;
  case OP_LOW:    printf("low"); break;
  case OP_GT:     printf(">"); break;
  case OP_GE:     printf(">="); break;
  case OP_LT:     printf("<"); break;
  case OP_LE:     printf("<="); break;
  case OP_NE:     printf("!="); break;
  case OP_REP:    printf("rep"); break;
  default :       printf("unknown node"); break;
  }
  
}

void print_tree( char * prefix, struct ir_node * node, int indent) {

  int i;
  
  printf("[%s] ", prefix);

  for (i = 0; i < indent; i++) {
    printf("  ");
  }

  print_node(node);

  printf("\n");

  if (node->left != NULL) {
    print_tree(prefix, node->left, indent+1);
  }

  if (node->right != NULL) {
    print_tree(prefix, node->right, indent+1);
  }
  
}
#endif
