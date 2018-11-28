#!/bin/bash

make -C ../.
cp ../asm .
rm ./champs1/*.cor

sfiles=(./champs1/*)
original=(./original/*)
# for element in "${array[@]}"
# do
#     ./asm -p $element > m
#     diff m ./original/$element
# done

for ((i=0; i<${#sfiles[@]}; i++)) do
    ./asm -p ${sfiles[$i]} > m
    echo ${original[$i]}
    diff m ${original[$i]}
done


