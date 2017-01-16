/* tst2.c - c program to test the utst system */

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

UTST_FUNCTION(tst2_utst_1)
{
  char *s1 = strdup("hello world");
  UTST_ASSERT(utst, s1[0] == 'h');  /* should succeed */
  E_ASSERT(utst->num_asserts == 1);
  E_ASSERT(utst->error_array[0] == NULL);

  UTST_ASSERT(utst, s1[2] == 'l');  /* should succeed */
  E_ASSERT(utst->num_asserts == 2);
  E_ASSERT(utst->error_array[0] == NULL);
  E_ASSERT(utst->error_array[1] == NULL);

  UTST_RASSERT(utst, s1[4] == 'o');  /* should succeed */
  E_ASSERT(utst->num_asserts == 3);
  E_ASSERT(utst->error_array[0] == NULL);
  E_ASSERT(utst->error_array[1] == NULL);
  E_ASSERT(utst->error_array[2] == NULL);

  UTST_RASSERT(utst, s1[5] == ' ');  /* should succeed */
  E_ASSERT(utst->num_asserts == 4);
  E_ASSERT(utst->error_array[0] == NULL);
  E_ASSERT(utst->error_array[1] == NULL);
  E_ASSERT(utst->error_array[2] == NULL);
  E_ASSERT(utst->error_array[3] == NULL);

  free(s1);
}  /* tst2_utst_1 */


/* Test empty function */
UTST_FUNCTION(tst2_utst_2)
{
  char *s1 = strdup("hello world");
  UTST_ASSERT(utst, s1[0] == 'h');  /* should succeed */
  E_ASSERT(utst->num_asserts == 1);
  E_ASSERT(utst->error_array[0] == NULL);

  UTST_ASSERT(utst, s1[2] == 'l');  /* should succeed */
  E_ASSERT(utst->num_asserts == 2);
  E_ASSERT(utst->error_array[0] == NULL);
  E_ASSERT(utst->error_array[1] == NULL);

  UTST_RASSERT(utst, s1[4] == 'o');  /* should succeed */
  E_ASSERT(utst->num_asserts == 3);
  E_ASSERT(utst->error_array[0] == NULL);
  E_ASSERT(utst->error_array[1] == NULL);
  E_ASSERT(utst->error_array[2] == NULL);

  UTST_RASSERT(utst, s1[5] == ' ');  /* should succeed */
  E_ASSERT(utst->num_asserts == 4);
  E_ASSERT(utst->error_array[0] == NULL);
  E_ASSERT(utst->error_array[1] == NULL);
  E_ASSERT(utst->error_array[2] == NULL);
  E_ASSERT(utst->error_array[3] == NULL);

  free(s1);
}  /* tst2_utst_2 */


#include "tst2.utst"

#endif  /* UTST */
