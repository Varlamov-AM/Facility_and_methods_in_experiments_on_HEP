ls /cvmfs/geant4.cern.ch &> /dev/null
ls /cvmfs/sft.cern.ch &> /dev/null

# Setup CMAKE v3.4
export PATH=/nfs/lfi.mipt.su/data/mikhail/sw/Geant4/cmake-3.16.4-Linux-x86_64/bin:$PATH

# Setup g++
source /cvmfs/sft.cern.ch/lcg/releases/gcc/4.9.3/x86_64-slc6/setup.sh

# Setup either ROOT v.5 or v.6
#source /cvmfs/sft.cern.ch/lcg/releases/ROOT/6.04.16-71ca3/x86_64-slc6-gcc49-opt/bin/thisroot.sh
source /cvmfs/sft.cern.ch/lcg/external/ROOT/5.34.23/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh

# Setup GEANT4
source /cvmfs/sft.cern.ch/lcg/releases/Geant4/10.01.p02-81fbd/x86_64-slc6-gcc49-opt/bin/geant4.sh

# need to help CMAKE indentify compiler
cmake -DCMAKE_CXX_COMPILER=$(which g++) -DCMAKE_C_COMPILER=$(which gcc) ..

# make works perfect
make CXX=$(which g++) CC=$(which gcc)
