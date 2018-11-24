
element="test.s"

RED='\033[0;31m'    
SET='\033[0m'
BLUE='\033[0;34m'
DARKGRAY='\033[1;30m'

# echo "${BLUE}my:${SET}\n"
./asm $element > my
# echo "${DARKGRAY}original:${SET}\n"
./org_asm $element > org
diff my org

# # echo "\n\n\n${BLUE}my:${SET}\n"
# ./asm -p $element > my
# # echo "${DARKGRAY}original:${SET}\n"
# ./org_asm -a $element > org
# diff my org