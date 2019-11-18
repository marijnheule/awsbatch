NUM=$1
VAR=$2
LOG=log/tmp$$.log
SEED=$3

echo $SEED
encode $NUM $VAR $SEED | cadical > $LOG 
cat $LOG | grep "real"
cat $LOG | grep "^v "  | tr "\n" " " | sed 's|v||g' | sed 's|-[0-9]*|-|g' | \
  sed 's|[1-9][0-9]* |+|g' | sed 's| ||g' | sed 's|0|\n|' | sed 's|-|0|g' | sed 's|+|1|g' | decode $NUM $SEED
rm $LOG
