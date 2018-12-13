#!/bin/bash

export DELAY=0.18
export TICK=0.2

./control.sh &
telnet whale.hacking-lab.com 4242

killall control.sh
