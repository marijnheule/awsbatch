NUM=$1
VAR=$2
LOG=log/tmp$$.log
SEED=$3
DIR=/tmp
CNF=mphf-$NUM-$VAR-$SEED

echo $SEED
encode $NUM $VAR $SEED > $DIR/cnf/$CNF.cnf
echo "a 0" > $DIR/cubes/$CNF.cubes

march_cu $DIR/cnf/$CNF.cnf -d 15 -o $DIR/cubes/$CNF.cubes > $LOG
cat $LOG | grep "seconds"
echo "p inccnf" > $DIR/cnf/$CNF.icnf
cat $DIR/cnf/$CNF.cnf | grep -v c >> $DIR/cnf/$CNF.icnf
cat $DIR/cubes/$CNF.cubes >> $DIR/cnf/$CNF.icnf
rm  $DIR/cubes/$CNF.cubes
iglucose $DIR/cnf/$CNF.icnf -verb=0 > $LOG
rm $DIR/cnf/$CNF.cnf $DIR/cnf/$CNF.icnf

cat $LOG | grep -v -e "^v " -e "remaining"
# cat $LOG | grep "CPU"
cat $LOG | grep "^v "  | tr "\n" " " | sed 's|v||g' | sed 's|-[0-9]*|-|g' | \
  sed 's|[1-9][0-9]* |+|g' | sed 's| ||g' | sed 's|0|\n|' | sed 's|-|0|g' | sed 's|+|1|g' | decode $NUM $SEED
rm $LOG
