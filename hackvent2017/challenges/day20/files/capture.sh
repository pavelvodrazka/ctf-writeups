#!/bin/bash

found="0"
name="$1"

echo "searching for $1 ..."
while [ $found -eq 0 ]; do
    #echo "searching..."
    if [ -f "/tmp/$name" ]; then
        cp "/tmp/$name" "$name"
        echo "FOUND!"
        found="1"
    fi
done
