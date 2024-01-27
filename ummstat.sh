 #! /bin/bash
 
if [[ $# -eq 0 ]]; then
        echo "usage $0 <umm-out-file>"
        exit -1
fi

sed -n '/PartId/,$p' $1 | grep -v "^2048" > umm.out
cat umm.out |  awk '{print $2}' | sort -n | uniq | grep -v PartId | grep -v "^$" > umm.mid
while read line; do
        echo -n "mid = $line, sum = "
        cmd='BEGIN{sum=0}{if($2=='"$line"'){sum += $7;}} END{ print sum;}'
        #echo $cmd
        cat umm.out | awk "$cmd"
done < umm.mid
