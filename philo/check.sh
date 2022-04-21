n=100
tt_die=210
tt_eat=100
tt_sleep=100
make
./philo $n $tt_die $tt_eat $tt_sleep > log
DEAD=`cat log | tail -1 | awk '{print $2}'`
cat log | grep " $((($DEAD + n - 2) % n + 1)) "
cat log | grep " $((($DEAD + n) % n + 1)) "
cat log | grep " $DEAD "