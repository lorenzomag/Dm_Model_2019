#!/bin/bash

script_name="tmp_script.txt"

enter(){
	echo -e "\n\n"
	read -s -p "Press enter to go back to main menu"
}



# changes UFO files to match requested benchmark point parameters
benchmark_change(){

	param_file="./models/DM/parameters.py"

	clear
	BP=-999

	# selects BP
	cat <<- EOF
		Which benchmark is to be selected?
		    MPsi   Mphi   MChi   y_1        case
		1)    56    165    473   7.53e-13      1
		2)   101     77    613   1.18e-13      1
		3)    33    192    113   0.0168        2
		4)    99    188    195   1.38          2
		5)    83    127    143   2.25          2
		6)    73    199    137   5.06          2
	EOF

	# until $BP is integer between 1 and 6, do
	until [[ $BP =~ ^[1-6]+$ ]]; do

		read -s -n 1 BP

	done

	# populating BP_array with benchmark point parameters
	var_array=({MPsi} {Mphi} {MChi} y_1)
	case $BP in
		1) BP_array=(56 165 473 7.53e-13);;
		2) BP_array=(101 77 613 1.18e-13);;
		3) BP_array=(33 192 113 0.0168);;
		4) BP_array=(99 188 195 1.38);;
		5) BP_array=(83 127 143 2.25);;
		6) BP_array=(73 199 137 5.06);;
	esac

	echo -e "\nSetting parameters for Benchmark Point $BP\n"
	echo "Modified file: $param_file"

	for i in {0..3}; do

		str_var=$(grep -B1 "${var_array[$i]}" $param_file |
		head -1 | sed -e 's/^[ \t]*//')
		linenum_var=$(grep -n -B1 "${var_array[$i]}" $param_file |
		head -1 | cut -f 1 -d "-")

		echo "Modifield ${var_array[$i]} at line $linenum_var to $str_var"

		sed -i -e "${linenum_var}s/$str_var/value = ${BP_array[$i]},/" $param_file
	done
	enter
}






prepare_script_default(){
	case_var=-999

	read -p "Name of output dir (empty for mg5 default): " out_dir

	clear
	cat <<- EOT
		Process to be run:
			1) Case 1
			2) Case 2
			3) p p > phi+ phi-
	EOT

	# select case
	until [[ $case_var =~ ^[1-2]+$ ]]; do
		read case_var
	done

	echo "import model DM" > $script_name

	cat >> $script_name <<- EOF
		generate p p > ~chi+ ~chi-, ~chi+ > phi+ ~psi
		add process p p > ~chi+ ~chi-, ~chi- > phi- ~psi~
	EOF

	if [[ -n "$out_dir" ]]; then
		echo "output $out_dir" >> $script_name
	fi

	cat >> $script_name <<- EOF
		launch $out_dir
		detector=delphes
		analysis=off
		0
		set nevents 10
		set ebeam1 7000.0
		set ebeam2 7000.0
		0
	EOF
}

run(){
  if [ $1 == "default" ];then
    prepare_script_default
  else
    read -p "Input script file name: " inFile
  fi

	./bin/mg5_aMC $script_name

  enter
}
