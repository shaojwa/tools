#! /bin/bash

if [[ $# -eq 0 ]]; then
        echo "usage $0 <umm.out> | client | stat | both"
        exit -1
fi

if [[ "$1" == "client" || "$1" == "both"  ]]; then
cmd_client >umm.out <<EOF
mem part show
mem part show mdonline
exit
EOF
if [[ "$1" == "client" ]]; then
        exit -1;
fi
fi

if [[ "$1" == "stat" || "$1" == "both"  ]]; then
        umm_out=umm.out
else
        umm_out="$1"
fi



sed -n '/PartId/,$p' $umm_out | grep -v "^2048" > umm.tmp
cat umm.tmp |  awk '{print $2}' | sort -n | uniq | grep -v PartId | grep -v "^$" > umm.mid
> umm.done
while read line; do
        echo -n "mid = $line, sum = " |& tee -a umm.done
        cmd='BEGIN{sum=0}{if($2=='"$line"'){sum += $7;}} END{ print sum;}'
        #echo $cmd
        cat umm.tmp | awk "$cmd" |& tee -a umm.done
done < umm.mid
