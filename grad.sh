#!/bin/bash

rm -f count
touch count

for i in {1..100..1}
do
if [ "$i" -lt 10 ]; then
lines=`wc -l < Layer_no_000"$i".dat`
fi

if [[ ( "$i" -ge 10 && "$i" -lt 100 ) ]]; then
lines=`wc -l < Layer_no_00"$i".dat`
fi

if [[ ( "$i" -ge 100 && "$i" -lt 1000 ) ]]; then
lines=`wc -l < Layer_no_0"$i".dat`
fi
echo $i"    "$lines >> count
echo $i"    "$lines

done
