#!/bin/bash

declare -a dir=("build" "install/bin" "install/bin/Tests") 
# echo "${arr[0]}"
declare -a subdir=("Debug" "Release" "RelWithDebInfo" "MinSizeRel")

for i in "${dir[@]}"
do
   
    for j in "${subdir[@]}"
    do

        mkdir -p "$i/$j"
 
    done
   
done
