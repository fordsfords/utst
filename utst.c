/* utst.c - c program to test the utst system */

#ifdef UTST
#include "utst.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_ASSERT(cond_expr) do {\
  if (!(cond_expr)) {\
    fprintf(stderr, "ERR_ASSERT failed at %s:%d (%s)\n",\
            __FILE__, __LINE__, #cond_expr);\
    fflush(stderr);\
    abort();\
} } while (0)

/*****************************************************************************/

#ifdef UTST

UTST_FUNCTION(utst_utst_1)
{
  char *s1 = strdup("hello");
  UTST_ASSERT(utst, s1[0] == 'h');
  ERR_ASSERT(utst->num_asserts == 1);
  ERR_ASSERT(utst->error_array[0] == NULL);

  UTST_ASSERT(utst, s1[1] == 'E');
  ERR_ASSERT(utst->num_asserts == 2);
  ERR_ASSERT(utst->error_array[0] == NULL);
  ERR_ASSERT(utst->error_array[1] != NULL);

  UTST_ASSERT(utst, s1[2] == 'l');
  ERR_ASSERT(utst->num_asserts == 3);
  ERR_ASSERT(utst->error_array[0] == NULL);
  ERR_ASSERT(utst->error_array[1] != NULL);
  ERR_ASSERT(utst->error_array[2] == NULL);

  UTST_ASSERT(utst, s1[3] == 'L');
  ERR_ASSERT(utst->num_asserts == 4);
  ERR_ASSERT(utst->error_array[0] == NULL);
  ERR_ASSERT(utst->error_array[1] != NULL);
  ERR_ASSERT(utst->error_array[2] == NULL);
  ERR_ASSERT(utst->error_array[3] != NULL);

  free(s1);
}  /* utst_utst_1 */


/* Test empty function */
UTST_FUNCTION(utst_utst_2)
{
}  /* utst_utst_2 */


#include "utst.utst"

#endif  /* UTST */
