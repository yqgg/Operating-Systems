# Name: Yi Qian Goh
# Date: April 4, 2024
# Title: Lab1 – step3
# Description: This program takes a user input as the radius of a circle. This program then computes the area of a circle with the given radius.

#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "ygoh2" ]
then
    echo "Now you can proceed!"
else
    echo "Check who logged in!"
    exit 1
fi
response="Yes"
while [ $response != "No" ]
do
    echo "Enter radius of circle: "
    read radius
    PI=3.14159
    area=$(echo "$PI * $radius * $radius" | bc)
    echo "The area of the circle is $area"
    echo "Would you like to repeat for another circle [Yes/No]?"
    read response
done
