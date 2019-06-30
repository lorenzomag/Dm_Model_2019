#!/bin/sh
if [ ! $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=/home/s1412595/Desktop/SummerProject2019/MG5_aMC_v2_6_6/HEPTools/hepmc/lib
fi
if [ $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/s1412595/Desktop/SummerProject2019/MG5_aMC_v2_6_6/HEPTools/hepmc/lib
fi
export PYTHIA8DATA=${PYTHIA8_HOME}/xmldoc
