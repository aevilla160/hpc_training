#!/bin/bash
#SBATCH --job-name=example_job_array
#SBATCH --output=log%x_%A_%a.out # Output file
#SBATCH --error=log%x_%A_%a.err # Error file
# The format of the job is jobname_jobID_taskID
#SBATCH --partition=short  # Short Partition
#SBATCH --nodes=1 # Number of nodes
#SBATCH --ntasks-per-node=1 # Number of tasks (processes)
# #SBATCH --cpus-per-task=1 # Number of CPU cores per task 
#SBATCH --mem=3G # Memory Allocation for each node
#SBATCH --time=0-00:15:00 # days-hours:minutes:seconds
#SBATCH --array=1-5

# Define arrays
MODEL=(test_model1.py test_model2.py test_model3.py test_model4.py test_model5.py)
INPUTS=(input1.csv input2.csv input3.csv input4.csv input5.csv)

# Get zero-based index
IDX=$((SLURM_ARRAY_TASK_ID - 1))

# Select corresponding script and input
SCRIPT=${MODEL[$IDX]}
INPUT=${INPUTS[$IDX]}

# Clean Logging format for debugging and tracking. 
echo "----------------------------------------"
echo " Job:     $SLURM_JOB_NAME"
echo " Task:    $SLURM_ARRAY_TASK_ID / $SLURM_ARRAY_TASK_COUNT"
echo " Script:  $SCRIPT"
echo " Input:   $INPUT"
echo " Host:    $(hostname)"
echo " Started: $(date)"
echo "----------------------------------------"
# Load environment and run
module load anaconda3
# conda activate <envname>  # Uncomment & change env name

# Run the Python script
python "$SCRIPT" --input "$INPUT"
EXIT_CODE=$?

# Log completion
echo "----------------------------------------"
echo " Finished: $(date)"
echo " Exit code: $EXIT_CODE"
echo "----------------------------------------"

exit $EXIT_CODE