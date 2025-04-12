#!/bin/sh

PROGRAM=$1
shift

NUM_CALLS=`LD_PRELOAD=./ld_alloc_counter.so $PROGRAM $@ 99>&1 1>/dev/null | wc -c`
echo "Need to test $NUM_CALLS allocations for" $PROGRAM $@
NUM_CRASHES=0
for IDX in `seq 0 $NUM_CALLS`; do
    # check for failing due to a signal (segv/abrt/...)
    ALLOC_FAIL=${IDX} LD_PRELOAD=./ld_alloc.so $PROGRAM $@ >/dev/null 2>&1
    expr $? "==" "139" >/dev/null && {
	echo "Crash at allocation #${IDX}"
	coredumpctl info --no-pager
	NUM_CRASHES=`expr "$NUM_CRASHES" "+" "1"`
    }
done
echo "NUM_CRASHES:$NUM_CRASHES"

exit $NUM_CRASHES
