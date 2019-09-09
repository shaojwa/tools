    -r // 使用扩展正则表达式
    sed [range][!]{command} file
    range=begin,and
    begin,end=1,^,$,/pattern/
    range=null all
    Hold Space
    Pattern Space
    sed '1,4s/my/your/2g' file
    sed 's/my/[&]/g' file
    sed 'N;s/\n/,/' file
    sed '4a haha' file
    sed '4i huhu' file
    sed '/my/i hehe' file
    sed '2c replace second line' file
    sed '/my/c replease line having my' file
    sed '/my/d' file
    sed '/my/p' file
    sed '/dog/,/fish/p' fil
    sed -n '/my/p' file
    sed '4,5{/This/d}' file
    sed '4,5{/This/{/dog/d}}' file
    sed '!G;h;$!d' file
    sed '4,5{/This/d}' file
