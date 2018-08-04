#!/bin/bash

MODE=$1

for ((N=16384;N<67108865;N=N*2))
do
    ./Ejer$MODE $N
done
