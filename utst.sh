#!/bin/sh
# utst.sh

V=1.0

echo "INFO: utst.sh: utst, V=$V"
echo "INFO: utst.sh: Creating utst.h"
cat <<__EOF__ >utst.h
/* utst.h - this file is automatically generated by utst.sh, V=$V */

#ifndef UTST_H
#define UTST_H

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>

struct utst_s;  typedef struct utst_s utst_t;

struct utst_s {
  char *function_name;
  int num_asserts;
  char **error_array;
};

#define UTST_FUNCTION(fname) void fname(utst_t *utst)

#define UTST_ASSERT(utst,cond_expr) do {\
  ++ utst->num_asserts; \
  utst->error_array = (char **)realloc(utst->error_array,\
                                       utst->num_asserts * sizeof(char *));\
  if (cond_expr) {\
    utst->error_array[utst->num_asserts - 1] = NULL;\
  } else {\
    asprintf(&(utst->error_array[utst->num_asserts - 1]),\
             "UTST_ASSERT failed at %s:%d (%s)",\
             __FILE__, __LINE__, #cond_expr);\
  }\
} while (0)

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif  /* UTST_H */
__EOF__

for F in $*; do :
  f=`basename $F .c`
  echo "INFO: utst.sh: Creating $f.utst"
  cat <<__EOF__ >$f.utst
/* $f.utst - this file is automatically generated by utst.sh, V=$V */

void utst_new(utst_t **utst_p, char *function_name)
{
  utst_t *utst = (utst_t *)malloc(sizeof(utst_t));
  utst->function_name = strdup(function_name);
  utst->num_asserts = 0;
  utst->error_array = (char **)malloc(sizeof(char *));
  utst->error_array[0] = NULL;

  *utst_p = utst;
}  /* utst_new */

void utst_dump(utst_t *utst)
{
  printf("utst: function_name=%s, num_asserts=%d\n",
         utst->function_name, utst->num_asserts);
  int num_fails = 0;
  int i;
  for (i = 0; i < utst->num_asserts; ++i) {
    if (utst->error_array[i] != NULL) {
      ++ num_fails;
      printf("  FAIL: assert %d: %s\n",
             i+1, utst->error_array[i]);
    }  /* if error_array[i] */
  }  /* for i */
  if (num_fails == 0) {
    printf("  PASS\n");
  }
}  /* utst_dump */

void utst_delete(utst_t *utst)
{
  int i;
  for (i = 0; i < utst->num_asserts; i++) {
    if (utst->error_array[i] != NULL) {
      free(utst->error_array[i]);
    }
  }
  free(utst->error_array);
  free(utst->function_name);
  free(utst);
}  /* utst_delete */

int main(int argc, char **argv)
{
  utst_t *utst = NULL;
__EOF__

  FUNCTS=`sed -n <$F 's/^[    ]*UTST_FUNCTION(\([^)]*\)).*$/\1/p'`
  for FUNCT in $FUNCTS; do :
    cat <<__EOF__ >>$f.utst

  utst_new(&utst, "$FUNCT");
  $FUNCT(utst);
  utst_dump(utst);
  utst_delete(utst);
__EOF__
  done

  cat <<__EOF__ >>$f.utst
  return 0;
}  /* main */
__EOF__

  echo "INFO: utst.sh: building $f.c"
  if [ -f "utst_bld.sh" ]; then :
    ./utst_bld.sh -o $f $f.c
    GCC_STATUS=$?
  else :
    gcc -O0 -g -D UTST -o $f $f.c
    GCC_STATUS=$?
  fi
  if [ $GCC_STATUS -eq 0 ]; then :
    echo "INFO: utst.sh: Running $f"
    ./$f
  fi
done
