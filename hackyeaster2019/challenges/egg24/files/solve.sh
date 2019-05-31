#!/bin/bash

while true; do
    wget http://whale.hacking-lab.com:3555/ --load-cookies cookies.txt --save-cookies cookies.txt --keep-session-cookies -O /dev/null 2>/dev/null
    wget http://whale.hacking-lab.com:3555/picture --load-cookies cookies.txt -O capteg-input.jpg 2>/dev/null

    found=$(./count_eggs.py capteg-input.jpg show)
    echo "Found: ${found}"

    echo -n "Correction: "
    read correction

    total=$(($found + $correction))
    echo "Total: ${total}"

    response=$(wget http://whale.hacking-lab.com:3555/verify --load-cookies cookies.txt --post-data "s=${total}" -O - 2>/dev/null)
    echo "Response: ${response}"
done
