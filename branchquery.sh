setupATLAS -q
lsetup "root 6.32.02-x86_64-el9-gcc13-opt"
g++ -o ListBranchesInTree ListBranchesInTree.cpp `root-config --cflags --libs`
./ListBranchesInTree <inp_ntuple>.root vars.txt
