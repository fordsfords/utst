#!/bin/sh
# bld.sh

./utst.sh utst.c >bld.log 2>&1

# The following is hand-checked for correctness.
cat <<__EOF__ >bld.ok
utst: function_name=utst_utst_1, num_asserts=4
  FAIL: assert 2: UTST_ASSERT failed at utst.c:30 (s1[1] == 'E')
  FAIL: assert 4: UTST_ASSERT failed at utst.c:41 (s1[3] == 'L')
utst: function_name=utst_utst_2, num_asserts=0
  PASS
__EOF__

egrep -v "^INFO:" <bld.log >bld.chk
if diff bld.chk bld.ok >/dev/null; then echo "PASS"; rm bld.chk bld.ok
else echo "FAIL, diff bld.chk bld.ok"
fi
