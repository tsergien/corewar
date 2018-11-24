#!/bin/bash

make -C ../.
cp ../asm .

RED='\033[0;31m'
NC='\033[0m'

rm ./champs1/*.cor
sfiles=(./champs1/*)
RED='\033[0;31m'    
SET='\033[0m'
BLUE='\033[0;34m'
DARKGRAY='\033[1;30m'



for element in "${sfiles[@]}"
do
    echo -e "${RED}$element${SET}\n"
    echo -e "${BLUE}my:${SET} "
    ./asm $element
    echo -e "${DARKGRAY}original:${SET} "
    ./org_asm $element
done
rm ./champs1/*.cor