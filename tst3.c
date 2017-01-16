/* tst3.c - c program to test the utst system */

#ifdef UTST
#include "utst.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define E_ASSERT(cond_expr) do {\
  if (!(cond_expr)) {\
    fprintf(stderr, "E_ASSERT failed at %s:%d (%s)\n",\
            __FILE__, __LINE__, #cond_expr);\
    fflush(stderr);\
    abort();\
} } while (0)

/*****************************************************************************/

#ifdef UTST

/* This unit test is actually testing the unit test framework.  Thus,
 * several of the following UTST_ASSERT calls are designed to fail.  It
 * uses an internal macro "E_ASSERT" to check conditions that must be
 * true for the selftest of UTST to succeed.  Note that on failure,
 * "E_ASSERT" aborts immediately.
 */

UTST_FUNCTION(tst3_utst_1)
{
  char *s1 = strdup("hello world");
  UTST_AASSERT(s1[0] == 'h');  /* should succeed */
  E_ASSERT(utst->num_asserts == 1);
  E_ASSERT(utst->error_array[0] == NULL);

  UTST_AASSERT(s1[1] == 'E');  /* should fail */
  E_ASSERT(utst->num_asserts == 2);
  E_ASSERT(utst->error_array[0] == NULL);
  E_ASSERT(utst->error_array[1] != NULL);

  UTST_ASSERT(utst, s1[2] == 'l');  /* should succeed */
  E_ASSERT(utst->num_asserts == 3);
  E_ASSERT(utst->error_array[0] == NULL);
  E_ASSERT(utst->error_array[1] != NULL);
  E_ASSERT(utst->error_array[2] == NULL);

  UTST_ASSERT(utst, s1[3] == 'L');  /* should fail */
  E_ASSERT(utst->num_asserts == 4);
  E_ASSERT(utst->error_array[0] == NULL);
  E_ASSERT(utst->error_array[1] != NULL);
  E_ASSERT(utst->error_array[2] == NULL);
  E_ASSERT(utst->error_array[3] != NULL);

  UTST_RASSERT(utst, s1[4] == 'o');  /* should succeed */
  E_ASSERT(utst->num_asserts == 5);
  E_ASSERT(utst->error_array[0] == NULL);
  E_ASSERT(utst->error_array[1] != NULL);
  E_ASSERT(utst->error_array[2] == NULL);
  E_ASSERT(utst->error_array[3] != NULL);
  E_ASSERT(utst->error_array[4] == NULL);

  UTST_RASSERT(utst, s1[5] == ' ');  /* should succeed */
  E_ASSERT(utst->num_asserts == 6);
  E_ASSERT(utst->error_array[0] == NULL);
  E_ASSERT(utst->error_array[1] != NULL);
  E_ASSERT(utst->error_array[2] == NULL);
  E_ASSERT(utst->error_array[3] != NULL);
  E_ASSERT(utst->error_array[4] == NULL);
  E_ASSERT(utst->error_array[5] == NULL);

  /* This one should fail and return. */
  UTST_RASSERT(utst, s1[6] == 'W');  /* should fail */
  E_ASSERT(0);  /* should not get here */

  free(s1);
}  /* tst3_utst_1 */


/* Test empty function */
UTST_FUNCTION(tst3_utst_2)
{
  E_ASSERT(0);  /* should not get here */
}  /* tst3_utst_2 */


#include "tst3.utst"

#endif  /* UTST */
