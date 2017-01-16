#!/bin/sh
# bld.sh

./utst.sh tst1.c >bld1.log 2>&1
egrep -v "^INFO:" <bld1.log >bld1.chk

# The following is hand-checked for correctness.
cat <<__EOF__ >bld1.ok
  UTST_ASSERT failed at tst1.c:37 (s1[1] == 'E')
  UTST_ASSERT failed at tst1.c:48 (s1[3] == 'L')
  UTST_RASSERT failed at tst1.c:73 (s1[6] == 'W')
utst: Test tst1_utst_1 FAIL: 3 failed of 7 asserts
utst: Test tst1_utst_2 PASS: 0 asserts
utst: FINALERROR: 1 failed of 2 tests, 3 failed of 7 total asserts
__EOF__

if diff bld1.chk bld1.ok >/dev/null; then echo "PASS"; rm bld1.chk bld1.ok
else echo "FAIL, diff bld1.chk bld1.ok"
fi

./utst.sh tst2.c >bld2.log 2>&1
egrep -v "^INFO:" <bld2.log >bld2.chk

# The following is hand-checked for correctness.
cat <<__EOF__ >bld2.ok
utst: Test tst2_utst_1 PASS: 4 asserts
utst: Test tst2_utst_2 PASS: 4 asserts
utst: FINALPASS: 2 tests, 8 total asserts
__EOF__

if diff bld2.chk bld2.ok >/dev/null; then echo "PASS"; rm bld2.chk bld2.ok
else echo "FAIL, diff bld2.chk bld2.ok"
fi

./utst.sh tst3.c >bld3.log 2>&1
egrep -v "^INFO:|^\./utst\.sh: line 80:.*Abort trap" <bld3.log >bld3.chk

# The following is hand-checked for correctness.
cat <<__EOF__ >bld3.ok
E_ASSERT failed at tst3.c:34 (utst->num_asserts == 1)
__EOF__

if diff bld3.chk bld3.ok >/dev/null; then echo "PASS"; rm bld3.chk bld3.ok
else echo "FAIL, diff bld3.chk bld3.ok"
fi
