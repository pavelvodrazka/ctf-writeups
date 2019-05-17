#!/bin/bash

mount | grep -q $(pwd)/tmp || exit 0
sudo umount tmp
rm -rf tmp
