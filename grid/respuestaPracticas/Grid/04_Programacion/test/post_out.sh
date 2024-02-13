area=0
for id in 1 2 3; do
        rm aux.txt
        tail -1 miStdout_${id} >> aux.txt
        valor=`sed -e 's/it =//' aux.txt`
        echo val=${valor}
        area=$(awk '{print $1+$2}' <<<"${area} ${valor}")

done
echo 'area = ' ${area}
rm aux.txt
