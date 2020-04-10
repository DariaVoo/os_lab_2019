#!/bin/bash

count=$1
for ((i = 1; i <= count; i++))
do
    rm ${i}
done

