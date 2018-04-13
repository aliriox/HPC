#!/bin/bash
#
#SBATCH --gres=gpu:1
#SBATCH --job-name=matrizCuda
#SBATCH --output=res-matrizCuda.out
#SBATCH --account=cgiraldo
#SBATCH --ntasks=2
#SBATCH --cpus-per-task=1
#SBATCH --time=10:00
#SBATCH --mem-per-cpu=100

./matrizCuda m1.txt m2.txt