#!/bin/bash
parser(){
	echo $(echo "$data" | grep "$1" | sed 's/^[^:]*//g' | sed 's/[^0-9.%]//g')
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

	l1bound=$(parser 'L1 Bound:')
	l2bound=$(parser 'L2 Bound:')
	l3bound=$(parser 'L3 Bound:')
	drambound=$(parser 'DRAM Bound:')
	dtlbbound=$(parser 'DTLB Store Overhead:')


	echo "Elapsed $elapsed"
       	echo "Ticks $ticks"
      	echo "Instructions_Retired $instretir"
        echo "Retired $retired"
        echo "Front-End_bound $febound"
        echo "Bront-End_bound $bebound"
        echo "Memory_bound $memebound"
        echo "Core_bound $corbound"

        echo "L1_bound $l1bound"
        echo "L2_bound $l2bound"
        echo "L3_bound $l3bound"
        echo "DRAM_bound $drambound"
        echo "DTLB_bound $dtlbbound"
}

process(){
	declare -a minmax=("$Mn $Mx" "$Mn $Md" "$Md $Mx")
	for code in "${codez[@]}"
	do
		for mm in "${minmax[@]}"
		do
			for zz in "${threadz[@]}"
			do
				echo ''
				echo "code: $code; left, right: $mm, threads: $zz"
				data=$(g++ -Ofast -fopenmp $code && sudo ./vtune 2>/dev/null -collect uarch-exploration ./a.out $mm $zz)
				shower
				echo ''
			done
		done
	done
	sudo rm -rf r0*
}


Mx=500000000
Md=250000000
Mn=2

declare -a codez=("03_erasto_functional_static_schedule.cpp" "04_erasto_functional_handmade_scheduling.cpp" "05_erasto_functional_dynamic_schedule.cpp" "07_erasto_domain.cpp")
declare -a threadz=("1" "2" "4" "8")
process "$codez" "$threadz"

Mx=5000000
Md=2500000
declare -a codez=("08_sqrt_functional.cpp" "09_sqrt_domain.cpp")
process "$codez" "$threadz"

declare -a codez=("02_most_primitive.cpp")
declare -a threadz=("1")
process "$codez" "$threadz"

Mx=500000000
Md=250000000
declare -a codez=("01_erasto_single.cpp")
process "$codez" "$threadz"
