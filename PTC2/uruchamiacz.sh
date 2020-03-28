
nparser(){
	echo $(echo "$s" | grep $1 | sed 's/[^:]*: \(.*\)/\1/g')
}
parser(){
	echo $(echo "$s" | grep $1 | sed 's/[^0-9.]//g')
}
merger(){
	xz=1
	rs=""
	while [ $xz -lt 6 ]
	do
		rs="$rs ${!xz} & "
		xz=$((xz+1))
	done
	rs="$rs ${!xz} \\\\\ \\\hline\n"
	echo "$rs"
}


i=2
declare -a lst=(2 4 8)
m="\\\begin{tabular}{| l | l | l | l | l | l |}\n\\\hline\nKod & Wątki & Rzeczywisty czas obliczeń & Czas użycia procesorów & Przysp. & Pi \\\\\ \\\hline\n"

s=$(gcc -fopenmp ./pi_s.c && ./a.out)
time=$(parser przetwarzania)
pi=$(parser PI)

m="$m $(merger ./pi_s.c 1 $time $time - $pi)"

while [  $i -le 6 ]
do
	for j in "${lst[@]}"
	do
		s=$(gcc -fopenmp ./pi$i.c && ./a.out $j)
		
		sumt=$(parser Suma)
		real=$(parser Rzeczywisty)
		pi=$(parser PI)
		name=$(nparser Nazwa)
		przysp=$(echo "$time/$real" | bc -l | head -c 10)

		m="$m $(merger $name $j $real $sumt $przysp $pi)"
	done

	i=$((i+1))	
done

m="$m\n\\\end{tabular}\n"

m=$(echo "$m" | sed 's _ \\_  g')
printf "$m"
