NUM=$1
VAR=$2
LIM=$3
IDX=$4

for ((i = 0 ; i < $LIM ; i++))
do
  RND=$RANDOM$RANDOM
  CnC-run.sh $NUM $VAR $RND | grep -e "solution" -e "perfect" -e "ERROR" -e "CPU" -e "seconds" > log/mphf-$NUM-$VAR-$RND.log
#  run.sh $NUM $VAR $RND | grep -e "UNSAT" -e "perfect" -e "ERROR" -e "real" > log/mphf-$NUM-$VAR-$RND.log
done
# aws s3 cp log/mphf-$NUM-$VAR-$$-$IDX.log s3://529174233500-us-east-2-s3test
