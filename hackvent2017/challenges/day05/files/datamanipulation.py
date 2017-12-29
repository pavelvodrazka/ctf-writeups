#!/usr/bin/env python
# A library with misc. data manipulation functions
#  (c) 2005 - Intrepid Software
#   Bas Westerbaan <bas.westerbaan@gmail.com>

hexChars = '0123456789abcdef'

# xors two numbers with a specific width
def Xor(x,y,w):
    r = 0
    for p in range(0, w):
        pp = 256 ** p
        ppm = pp * 256 - 1
        r += (((ppm & x) >> (p * 8)) ^ ((ppm & y) >> (p * 8))) << p * 8
    return r

#def TestXor(x,y,w):
#    print PadStringLeft(NumberToBinary(x),w*8,'0')
#    print PadStringLeft(NumberToBinary(y),w*8,'0')
#    print PadStringLeft(NumberToBinary(Xor(x,y,w)),w*8,'0')


# returns a binary string representation of a number.
def NumberToBinary(n):
    p = 0   # current position
    pp = 1  # position to the second power, default: 2 ** 0
    r = ''  # return
    while n >= pp:
        if n & pp:
            r += '1'
        else:
            r += '0'
        p += 1
        pp = 2 ** p # cache power
    return ReverseString(r)

# returns a hexadecimal representation of a number.
def NumberToHexadecimal(n):
    p   = 0  # current position
    ppm = 15 # next position to the sixteenth power minus 1, default: 16 ** 1
             #  used as Mask
    pp  = 1  # cirremtposition to the sixteenth power, default: 16 ** 0
    r  = ''  # return
    while n >= pp:
        v = (n & ppm) >> (p * 4)
        r += hexChars[v]
        p += 1
        pp = 16 ** p
        ppm = pp * 16  - 1  # 16 ** (p + 1) - 1
    return ReverseString(r)

# return the number represented by a hexadecimal string
def NumberFromHexadecimal(s):
    s = s.lower()
    r = 0
    p = 0
    for i in range(len(s) - 1, -1, -1):
        r += hexChars.index(s[i]) * 16 ** p
        p += 1
    return r

# returns the number represented by a binary string
def NumberFromBinary(s):
    r = 0
    p = 0
    for i in range(len(s) - 1, -1, -1):
        if s[i] == '1':
            r += 2 ** p
        p += 1
    return r

# reverses a string (not very efficiently, maybe should use generator)
def ReverseString(s):
    r = ''
    for i in range(len(s) - 1, -1, -1):
        r += s[i]
    return r

# pads a string 's' on the left with 'c' until it has the length 'l'
def PadStringLeft(s, l, c):
    r = s
    while len(r) < l:
        r = c + r
    return r

# idem, but now on the right
def PadStringRight(s, l, c):
    r = s
    while len(r) < l:
        r += c
    return r
