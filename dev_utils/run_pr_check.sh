#!/bin/bash

GREEN="\033[1;32m"
YELLOW="\033[1;33m"
CYAN="\033[1;36m"
RED="\033[1;31m"
RESET="\033[0m"

NORM=`(norminette | grep Error | wc -l)`
error=$(norminette | grep Error)
if [ "$NORM" = 0 ] ; then
	echo -e "$YELLOW ###############################################################$RESET"
	echo -e "$YELLOW ####################$RESET$CYAN Norminette:$RESET$GREEN OK$RESET $YELLOW ##########################$RESET"
	echo -e "$YELLOW ###############################################################$RESET"
else
	echo -e "$RED ###############################################################$RESET"
	echo -e "$CYAN Norminette:$RESET$RED KO$RESET"
	echo -e "$YELLOW$error$RESET"
	echo -e "$RED ###############################################################$RESET"
	exit 1
fi

echo -e "$CYAN ###############################################################$RESET"
echo -e "$CYAN ############################$RESET$GREEN make $RESET$CYAN ############################$RESET"
echo -e "$CYAN ###############################################################$RESET"
make
echo "I'm the infile file" > infile

>output_minishell; >output_shell; diff output_minishell output_shell

< infile ls -l | wc -l >> output_shell
< infile cat /etc/passwd | grep -v "#" | wc -l >> output_shell
< infile cat | grep name | grep -E a$ | wc -l >> output_shell
< infile cat | grep -i a | grep -E e$ >> output_shell
< infile cat | grep -v a | grep -E s$ >> output_shell
< infile cat | grep -i s | sort | head -n 3 | uniq | tail -5 | wc -l >> output_shell
< infile cat | grep -i s | head -n 3 | sort | uniq | tail -5 >> output_shell
echo -e "$CYAN ###############################################################$RESET"
echo -e "$CYAN ######################$RESET$GREEN minishell program $RESET$CYAN ######################$RESET"
echo -e "$CYAN ###############################################################$RESET"
./minishell <<EOF
< infile ls -l | wc -l >> output_minishell
< infile cat /etc/passwd | grep -v "#" | wc -l >> output_minishell
< infile cat | grep name | grep -E a$ | wc -l >> output_minishell
< infile cat | grep -i a | grep -E e$ >> output_minishell
< infile cat | grep -v a | grep -E s$ >> output_minishell
< infile cat | grep -i s | sort | head -n 3 | uniq | tail -5 | wc -l >> output_minishell
< infile cat | grep -i s | head -n 3 | sort | uniq | tail -5 >> output_minishell
exit
EOF
echo -e "$CYAN ###############################################################$RESET"
echo -e "$CYAN #######################$RESET$GREEN make clean $RESET$CYAN ##########################$RESET"
echo -e "$CYAN ###############################################################$RESET"

COMPARE=`(diff output_minishell output_shell | wc -c)`
error=$(diff output_minishell output_shell)

rm output_minishell output_shell infile
make fclean_all
echo -e "$CYAN ###############################################################$RESET"
echo -e "$CYAN ###############################################################$RESET"

if [ "$COMPARE" = 0 ] ; then
	echo -e "$YELLOW ###############################################################$RESET"
	echo -e "$YELLOW ######################$RESET $CYAN Test:$RESET$GREEN OK$RESET $YELLOW #############################$RESET"
	echo -e "$YELLOW ###############################################################$RESET"
else
	echo -e "$RED ###############################################################$RESET"
	echo -e "$YELLOW$error$RESET"
	echo -e "$RED ###############################################################$RESET"
	exit 1
fi