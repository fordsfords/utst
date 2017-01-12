/* sample.c - Demonstration program for utst unit test framework. */

/* The following is standard at or near top of all programs that use utst. */
#ifdef UTST
#include "utst.h"
/* You can add more inlcudes here that only your unit test code needs. */
#include <string.h>
#endif

/* These are the includes that your "product" code needs. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Here is your "product" code.  Unit tests are later. */


/* Function to add ".txt" to the end of a file name. */
/* Returns 0 for OK. */
int addtxt(char *filename)
{
  if (filename == NULL)
    return -1;  /* Error, no filename supplied */
  if (*filename == '\0')
    return -2;  /* Error, zero-length filename supplied */

  int i = 0;
  while (filename[i] != '\0')  /* Find the end of the string. */
    i++;

  char *txt = ".txt";  /* Start at beginning of ".txt" string. */
  while (*txt != '\0') {
    filename[i] = *txt;
    i++;
    txt++;
  }

  /* Hmm ... what am I forgetting? */

  return 0;  /* success */
}  /* addtxt */


/*****************************************************************************
 * Now for the unit test code.
 *****************************************************************************/

/* Only compile unit test code if testing. */

#ifdef UTST

UTST_FUNCTION(addtxt_err_tests)
{
  int err;

  /* Verify error checking */
  err = addtxt(NULL);
  UTST_ASSERT(utst, err == -1);

  err = addtxt("");
  UTST_ASSERT(utst, err == -2);
}  /* addtxt_err_tests */


char file1[13];
char file2[13];
char file3[13];
UTST_FUNCTION(addtxt_ok_tests)
{
  int err;

  /* Check full name. */
  strcpy(file2, "12345678");
  err = addtxt(file2);
  UTST_ASSERT(utst, err == 0);
  UTST_ASSERT(utst, strcmp(file2, "12345678.txt") == 0);

  /* Check short name. */
  strcpy(file2, "A");
  err = addtxt(file2);
  UTST_ASSERT(utst, err == 0);
  /* The fillowing test will fail.  Do you know why? */
  UTST_ASSERT(utst, strcmp(file2, "A.txt") == 0);

  /* Even the best unit test framework can't detect poor design.  Note
   * that you don't tell addtxt() how big the buffer is.  This call
   * overflows file2, but unless the unit test is specifically written
   * to check for buffer overflow, it goes undetected.  */
  strcpy(file2, "123456789");
  err = addtxt(file2);
  UTST_ASSERT(utst, err == 0);
  UTST_ASSERT(utst, strcmp(file2, "123456789.txt") == 0);
}  /* addtxt_ok_tests */


/* This is standard, and must reflect this file's name. */
#include "sample.utst"

#endif  /* UTST */
