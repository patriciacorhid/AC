#!/bin/bash

MODE=$1

for ((N=65536;N<67108865;N=N*2))
do
    ./SumaVectoresC_$MODE $N
done
