# Name: Yi Qian Goh
# Date: April 4, 2024
# Title: Lab1 - step1.sh
# Description: This is a given sample shell program that computes the area of a rectangle.

#!/bin/sh
echo Executing $0
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "ygoh2" ] #use your username instead of salagtash
then
    echo "Now you can proceed!"
else
    echo "Check who logged in!"
    exit 1
fi
response="Yes"
while [ $response != "No" ]
do
    echo "Enter height of rectangle: "
    read height
    echo "Enter width of rectangle: "
    read width
    area=`expr $height \* $width`
    echo "The area of the rectangle is $area"
    echo "Would you like to repeat for another rectangle [Yes/No]?"
    read response
done
