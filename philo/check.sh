n=200
tt_die=130
tt_eat=60
tt_sleep=60
make
./philo $n $tt_die $tt_eat $tt_sleep > log
DEAD=`cat log | tail -1 | awk '{print $3}'`
cat log | grep " $((($DEAD + n - 2) % n + 1)) "
cat log | grep " $((($DEAD + n) % n + 1)) "
cat log | grep " $DEAD "