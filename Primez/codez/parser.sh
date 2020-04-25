#!/bin/bash
parser(){
	echo $(echo "$data" | grep "$1" | sed 's/[^0-9.%]//g')
}

shower(){
	elapsed=$(parser Elapsed)
	ticks=$(parser Clockticks:)
	instretir=$(parser 'Instructions Retired:')
	retired=$(parser Retiring:)
	febound=$(parser 'Front-End Bound:')
	bebound=$(parser 'Back-End Bound:')
	membound=$(parser 'Memory Bound:')
	corbound=$(parser 'Core Bound:')

	echo "$elapsed $ticks $instretir $retired $febound $bebound $membound $corbound"
}


Mx=500000000
Md=250000000
Mn=2

declare -a arr=("element1" "element2" "element3")
declare -a codez=("03_erasto_domain.cpp" "04_erasto_dynamic_schedule.cpp" "07_erasto_functional.cpp")
declare -a minmax=("$Mn $Mx" "$Mn $Md" "$Md $Mx")
declare -a threadz=("1 2 4 8")


for code in "${codez[@]}"
do
	for mm in "${minmax[@]}"
	do
		echo '##############################'
		echo "code: $code; left, right: $mm"
		data=$(g++ -fopenmp $code && sudo ./vtune 2>/dev/null -collect uarch-exploration ./a.out $mm)
		shower
		echo '##############################'
	done
done
sudo rm -rf r0*
