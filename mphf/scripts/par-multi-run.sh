set -x

NUM=$1
VAR=$2
LIM=$3
LBL=$4
CORE=16

for ((i = 0 ; i < $CORE ; i++))
do
  multi-run.sh $NUM $VAR $LIM $i &
done
wait
cat log/mphf-$NUM-$VAR-*.log > log/mphf-$NUM-$VAR-$LBL.log
wc log/mphf-$NUM-$VAR-$LBL.log
aws s3 cp log/mphf-$NUM-$VAR-$LBL.log s3://529174233500-us-east-2-mphf
