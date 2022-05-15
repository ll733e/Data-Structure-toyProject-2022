DIR="$( cd "$( dirname "$0" )" && pwd -P )"
cd $DIR

start=`gdate +%s.%N`

for var in 1
do
    ./Node.out "BOOK CODE : $RANDOM$var" "$RANDOM" "$((($RANDOM * $RANDOM * 87654345)))" "$((($RANDOM) % 30 + 1990))"
    wait
done

finish=`gdate +%s.%N`
diff=$( echo "$finish - $start" | bc -l )

echo "프로그램 작동 시간 0$diff 초"

