#!/bin/bash -x

echo "Construyendo el proyecto"
make clean && make

echo "Ejecutando el proyecto"
time mpirun --hostfile maquinas.txt ./dist/openmpi-cpp /media/compartida/puntajes.csv