#!/usr/bin/env python

import urllib2
import base64
import time

xor_key = [0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF]

def xor(target): return ''.join([chr(ord(target[i])^xor_key[i%len(xor_key)]) for i in range(len(target))])

nonce = ''

try:
    nonce = urllib2.urlopen(base64.b64decode('aHR0cDovL2NoYWxsZW5nZXMuaGFja3ZlbnQuaGFja2luZy1sYWIuY29tOjgwODEvP25vbmNl')).read()
    nonce = base64.b64decode(nonce)
    nonce = xor(nonce)
    nonce = base64.b64encode(nonce)
    print('nonce: ' + nonce)
except: pass

time.sleep(2)

try:
    resp = urllib2.urlopen(base64.b64decode('aHR0cDovL2NoYWxsZW5nZXMuaGFja3ZlbnQuaGFja2luZy1sYWIuY29tOjgwODEvP25vbmNl'), data='nonce=' + nonce).read()
    print('resp: ' + resp)
except:
    pass
