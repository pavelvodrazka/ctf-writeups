#!/usr/bin/env python

import base64, sys

def x(t): return ''.join([ chr(ord(t[i]) ^ [0x66, 0x66, 0x66, 0x13, 0x37, 0x42, 0x69, 0x33, 0x01, 0x13] [i % 10]) for i in range(len(t)) ])

def decode(cmd): return x(base64.b64decode(cmd))
def encode(cmd): return base64.b64encode(x(cmd))

prefix = '@muffiniks #hackvent http://hackvent.hacking-lab.com  MUFFIN_BOTNET:'
suffix = ':MUFFIN_BOTNET'

cmd = str(sys.argv[1])

print(prefix + encode(cmd) + suffix)
