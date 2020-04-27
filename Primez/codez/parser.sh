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
	ecpu=$(parser 'Effective CPU Utilization:')


	echo "Elapsed $elapsed"
       	echo "Ticks $ticks"
      	echo "Instructions_Retired $instretir"
        echo "Retired $retired"
        echo "Front-End_bound $febound"
        echo "Bront-End_bound $bebound"
        echo "Memory_bound $membound"
        echo "Core_bound $corbound"

        echo "L1_bound $l1bound"
        echo "L2_bound $l2bound"
        echo "L3_bound $l3bound"
        echo "DRAM_bound $drambound"
        echo "DTLB_bound $dtlbbound"
	echo "Effective_Cpu $ecpu"
}

process(){
	declare -a minmax=("$Mn $Mx") # "$Mn $Md" "$Md $Mx")
	for code in "${codez[@]}"
	do
		for mm in "${minmax[@]}"
		do
			for zz in "${threadz[@]}"
			do
				echo ''
				echo "code: $code"
				echo "left_right: $mm"
				echo "threads: $zz"
				data=$(icpc -fopenmp $code && sudo ./vtune 2>/dev/null -collect uarch-exploration ./a.out $mm $zz)
				shower
				echo ''
			done
		done
	done
	sudo rm -rf r0*
}


Mx=1000000000
Md=500000000
Mn=2
source /opt/intel/bin/compilervars.sh intel64
#"09_sqrt_domain.cpp"
declare -a codez=("03_erasto_functional_static_schedule.cpp" "04_erasto_functional_handmade_scheduling.cpp" "05_erasto_functional_dynamic_schedule.cpp")
declare -a threadz=("4")
process "$codez" "$threadz"

declare -a codez=("08_erasto_super_domain.cpp"  "07_erasto_domain.cpp")
process "$codez" "$threadz"



declare -a codez=("08_erasto_super_domain.cpp"  "07_erasto_domain.cpp")
declare -a threadz=("1" "2" "4")
process "$codez" "$threadz"
Mx=10000000
process "$codez" "$threadz"

declare -a codez=("02_most_primitive.cpp")
declare -a threadz=("1")
process "$codez" "$threadz"

Mx=1000000000
Md=500000000
declare -a codez=("01_erasto_single.cpp")
process "$codez" "$threadz"
