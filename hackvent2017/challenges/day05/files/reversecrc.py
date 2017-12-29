#!/usr/bin/env python
# A library to reverse CRC
#  (c) 2005 - Intrepid Software
#   Bas Westerbaan <bas.westerbaan@gmail.com>

import sys
from crc import *

hash = int(sys.argv[1], 16)
crc = Crc32Provider()
base = ''
chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 '
depth = 0

print "CRC Reverser v0.01"
print " (c) 2005 - Bas Westerbaan <bas.westerbaan@gmail.com>"
print "  Intrepid Software"
print ""
print "Reversing the hash " + PadStringLeft(NumberToHexadecimal(hash), crc.width, '0')

while True:
    print "Depth " + str(depth + 4)
    base = []

    for i in range(0,depth):
        base.append(0)

    while True:
        baseString = ''
        for i in range(0,depth):
            baseString += chars[base[i]]

        crc.reset()
        crc.update(baseString)
        patch = crc.patch(hash)

        clean = True

        try:
            for i in range(0, len(patch)):
                chars.index(patch[i])
        except ValueError:
            clean = False

        if clean:
            print baseString + patch

        i = 0

        while i < depth and base[i] == len(chars)-1:
            base[i] = 0
            i += 1

        if i == depth:
            break
        base[i] += 1

    depth += 1
