#!/bin/bash

printf "Select the options: \n 1. ABP news \n 2. Republic World \n 3. Zee News"

printf "\n\nEnter: "

read OPT

echo "Playing..."

case $OPT in
	1) 
		mpv https://www.youtube.com/watch?v=nyd-xznCpJc
	;;
	2) 
		mpv https://www.youtube.com/watch?v=Px1lFQXKD4w
	;;
	3) 
		mpv https://www.youtube.com/watch?v=pXTvorHxThQ
	;;
esac
