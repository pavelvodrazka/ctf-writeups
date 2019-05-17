#!/bin/bash

mkdir -p tmp
mount | grep -q $(pwd)/tmp || mount -t tmpfs -o mode=01777,size=50m tmpfs tmp
cp attack_whitebox.py ../../Deadpool/deadpool_dfa.py tmp
cp ../../JeanGrey/phoenixAES/phoenixAES/__init__.py tmp/phoenixAES.py
cp ../../WhiteBox tmp
cp ../../WhiteBox tmp/WhiteBox.gold
cd tmp
./attack_whitebox.py
