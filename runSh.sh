#PBS -l nodes=2:ppn=1
source /etc/bash.bashrc
mpirun percolation s .6 10 2 1