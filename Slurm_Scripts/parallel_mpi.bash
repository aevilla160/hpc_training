#!/bin/bash
#SBATCH --nodes=1  #asked for 1 node
#SBATCH --ntasks=36 #asked for 36 cores
#SBATCH --partition test  #this job will submit to test partition
#SBATCH --mem=96G  #Asks for 96G of total memory
#SBATCH --time=0-00:15:00 # 15 minutes
#SBATCH --output=mpiexample%j.log  #the output information will put into mpiexample%j.log file
#SBATCH --job-name=mpitest  #the job name
#SBATCH --export=ALL

whoami
#module load the global openmpi and Anaconda3
module load anaconda3

#source activate 
# Ensures we start in our home directory
# Pip installs mpi4py to use MPI with Python
#pip install mpi4py
#For the CPP version we first begin with compiling the cpp binary where mpic++ is our compiler
mpic++ -o ../MPI/mpitest ../MPI/mpitest.cpp

#Then we execute the binary using mpirun and using 36 workers or processes.
# each worker will be a CPU core
mpirun -np 36 ../MPI/mpitest


# ----------- Python Version Below ----------
# For the Python Version
# mpiexec -n 36 python script.py
