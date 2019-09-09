#!/bin/bash

PROJECT_DIR=/home/s1412595/Desktop/SummerProject2019/MG5_aMC_v2_6_6

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

check_dir(){

	if [[ -d $1 ]]
		then
			echo -e "\nDirectory $1 already exists.\n"

			answer="_"
			answer2="_"
			until [[ "$answer" =~ ^[Yy](es)?$|^[Nn](o)?$  ]]
			do
				cat <<- EOT
					Do you want to use the process described
					in the chosen directory?

					If yes, $1/bin/generate_events will be run.
					If no, you will be asked whether to abort or to
					recreate the directory.
				EOT

				read answer
			done

			if [[ "$answer" =~ ^[Yy](es)?$ ]];
				then
					echo "process in $1 will be run"
					return 1
				else

					until [[ "$answer2" =~ ^[Yy](es)?$|^[Nn](o)?$  ]]
					do
						read -p "Do you want to recreate the directory $1? " answer2
					done

					if [[ "$answer2" =~ ^[Yy](es)?$ ]];
					 then
					 		echo "$1 will be recreated"
						 	return 2
						else
							echo "ABORT!!!"
							return -1
					fi
			fi
		else
			echo "The folder does not exist"
			return 0
	fi
}




prepare_script_default(){
	case_var=-999

	clear
	cat <<- EOT
		Process to be run:
			1) Case 1 (from paper)
			2) Case 2 (from paper)
			3) p p > phi+ phi-

	EOT

	# select case
	until [[ $case_var =~ ^[1-3]+$ ]]; do
		read case_var
	done

	echo -en "import model DM
					define nn = nn1 nn2 nn3
					define nn~ = nn1~ nn2~ nn3~
					" > $script_name

	if [[ $case_var -eq 1 ]];then
		cat >> $script_name <<- EOF
			generate p p > ~chi+ ~chi-, ~chi+ > phi+ ~psi
			add process p p > ~chi+ ~chi-, ~chi- > phi- ~psi~
		EOF
	elif [[ $case_var -eq 2 ]]; then
		cat >> $script_name <<- EOF
			generate p p > ~chi+ ~chi-, (~chi+ > phi+ ~psi, phi+ > nn l+)
			add process p p > ~chi+ ~chi-, (~chi- > phi- ~psi~, phi- > nn~ l-)
		EOF
	elif [[ $case_var -eq 3 ]]; then
		cat >> $script_name <<- EOF
			generate p p > phi+ phi-
		EOF
	fi

	if [[ -n "$out_dir" ]]; then
		echo "output $out_dir" >> $script_name
	fi

	cat >> $script_name <<- EOF
		launch $out_dir
		#detector=delphes
		shower=off
		detector=off
		analysis=off
		0
		set nevents 10000
		set ebeam1 7000.0
		set ebeam2 7000.0
		0
	EOF
}



run(){

	if [ $1 == "old" ]; then
		dir_name=$(zenity --file-selection --directory)
		case $? in
			0) echo "\"$dir_name\" selected";;

			*?) echo -e "\n\nNo valid directory was selected."
				 enter
				 return 1;;
		esac

		$dir_name/bin/generate_events

		enter
		return 0
	fi



	read -p "Name of output dir (empty for mg5 default): " out_dir

	check_dir $out_dir
	case $? in
		0) echo "Directory $out_dir will be created during simulation"
				;;
		1) echo "The process detailed in $out_dir will be executed (TO BE IMPLEMENTED)"
				;;
		2) rm -rf $out_dir
			 echo "$out_dir was removed. It will be recreated during simulationss"
				;;
		-1) echo "Run aborted"; return 1
				;;
		esac




  if [ $1 == "default" ];then
		script_name="tmp_script.txt"
    prepare_script_default out_dir
  elif [ $1 == "script" ]; then


		eval `resize`
	  a="If an output directory that already exists is specified, MG5 will ask"
		a="$a whether to recreate it. If 'yes' is provided, the directory WILL BE"
		a="$a DESTROYED and recreated. If 'no' is provided, the program will be aborted.\n"
		a="$a The 'yes'/'no' answer has to be provided between the 'output' command and the 'launch' program.\n"
		a="$a Please, be careful with the 'output' command.\n"
		a="$a If the output command is omitted, a default	directory will instead be created."

		zenity --warning --text="$a" --width=600 --height=100

		script_name=$(zenity --file-selection)
		case $? in
			0) echo "\"$script_name\" selected";;

			*?) echo -e "\n\nNo valid file was selected."
				 enter
				 return 1;;
		esac
	elif [ $1 == "new" ]; then
		read -p "Input script file name to create: " script_name

		cat >> $script_name  <<- EOF
			# You are in a Vim editor instance.
			# Write your script in this file.
			#
			# Follow https://answers.launchpad.net/mg5amcnlo/+faq/2186
			# to learn how to write a script for MadGraph5
			# An outline is provided below

			import model DM
			define nn = nn1 nn2 nn3
			define nn~ = nn1~ nn2~ nn3~

			# generate p p > ~chi+ ~chi- (example, input here process to be generated)
			# add process p p > phi+ phi- (example, add multiple processes with this command)

			#output <name of output dir> (leave name blank or omit command for MG5 default)

			# !!! WARNING
			# If an output directory that already exists is specified, MG5 will ask
			# whether to recreate it. If 'yes' is provided, the directory WILL BE
			# DESTROYED and recreated. If 'no' is provided, the program will be aborted.
			# The 'yes'/'no' answer has to be provided between the 'output' command and
			# the 'launch' program

			launch

			#shower=pythia or shower=off
			#detector=delphes or detector=off (delphes implies shower=pythia)
			madanalysis=off

			0

			# CARDS (modify cards content here)

			set nevents 1000
			set ebeam1 7000
			set ebeam2 7000

			0

		EOF

		vim $script_name

  fi

	./bin/mg5_aMC $script_name

	if [ $script_name == "tmp_script.txt" ]; then
		rm tmp_script.txt
	fi

  enter
}

program_on=true

while [ 1 ]; do
selection=-999
until [[ "$selection" =~ ^[0-5]+$|^q$ ]]; do
clear
echo -en "Select action:
1) Change benchmark parameters;
2) Run a default process (see './menu.sh -h' for details);
3) Run from existing script;
4) Write script and run;
5) Generate process from an existing directory;

0|q) Exit program

Selection: "

read selection
done


case $selection in
  0|q)  exit 0
      ;;
  1)  benchmark_change
      ;;
  2)  run default
      ;;
  3)  run script
      ;;
	4)	run new
			;;
	5)	run old
			;;
esac

done
