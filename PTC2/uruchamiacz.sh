i=2
declare -a lst=(2 4 8)

while [  $i -le 6 ]
do
	for j in "${lst[@]}"
	do
		gcc -fopenmp ./pi$i.c && ./a.out $j
	done

	i=$((i+1))	
done
