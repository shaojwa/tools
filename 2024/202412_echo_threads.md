```
thread=$(ps -Tlp $(pidof dse) | grep 'Processer_\(2[5-9]\|3[0-9]\|40\)'| grep -v "00:00:00" | awk '{print $5}')
echo $threads | wc -l // returns 1
echo "$threads" | wc -l // returns 16
```
