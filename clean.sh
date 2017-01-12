#!/bin/sh
# clean.sh

rm -rf bld.err bld.log bld.chk bld.ok utst *.dSYM utst.h utst.utst clean.tmp sample sample.utst

/bin/ls -1 -a | egrep -v "^\.$|^\.\.$|^bld\.sh$|^utst\.c$|^utst\.sh|^README\.md$|^LICENSE$|^clean\.sh$|^sample\.c$|^clean\.tmp$" >clean.tmp
CLEAN=`wc -l <clean.tmp`
if [ $CLEAN -eq 0 ]; then rm clean.tmp
else :
  echo "Unknown files:"
  cat clean.tmp
  echo "To delete, enter 'rm -rf \`cat clean.tmp\`'"
fi
