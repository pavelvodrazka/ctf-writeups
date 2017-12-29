#!/usr/bin/env python
# A library to work with CRC
#  (c) 2005 - Intrepid Software
#   Bas Westerbaan <bas.westerbaan@gmail.com>

# Note on reflecting:
#  Reflecting is pretty simple, reflecting the polynomial is just good enough.

from datamanipulation import *

class CrcProvider:
    # table
    # width
    # basePolynomial
    # reflected
    # initial
    # xorOut
    # polynomial
    # swapped
    # _hash

    def __init__(self, width, polynomial, reflected, initial, xorOut, swapped):
        self.width = width
        self.basePolynomial = polynomial
        self.reflected = reflected
        self.initial = initial
        self.xorOut = xorOut
        self.swapped = swapped

        if self.reflected:
            self.polynomial = ReflectNumber(self.basePolynomial,
                    self.width * 8)
        else:
            self.polynomial = self.basePolynomial

        self.table = self.generateTable()
        self.reset()

    # show crc table in hexadecimal
    def showTable(self):
        if len(self.table) > 0:
            r = '' + PadStringLeft(NumberToHexadecimal(self.table[0]), \
                self.width * 2, '0')
        else:
            r = ''
        for i in range(1, len(self.table)):
            r += ', ' + PadStringLeft(NumberToHexadecimal(self.table[i]), \
                self.width * 2, '0')
        r += ''
        print r

    # generates a crc table
    def generateTable(self):
        ret = []
        poly = ReflectNumber(self.basePolynomial, 32)
        for i in range(0, 256):
            entry = i
            for j in range(8, 0, -1):
                if entry & 1:
                    entry = Xor((entry >> 1), poly, self.width)
                else:
                    entry >>= 1
            if self.reflected:
                ret.append(entry)
            else:
                ret.append(ReflectNumber(entry))
        return ret

    def reset(self):
        self._hash = self.initial

    def getHash(self):
        if self.swapped:
            h = self.crcByteSwap(self._hash)
        else:
            h = self._hash
        return h ^ self.xorOut

    # does a crc byteswap as in the flhash
    def crcByteSwap(self, hash):
        if self.width != 4:
            raise Exception('Crc32 only supports byteswap')
        if self.reflected:
            raise Exception('byteswap is a dirty reflection, use one of them')
        h = (hash >> 24) | ((hash >> 8) & 0x0000ff00) | \
            ((hash << 24) & 4278190080) | ((hash << 8) & 0x00ff0000)
        return (h >> 2) | NumberFromHexadecimal('80000000')

    # update the hash with a string of data
    def update(self,s):
        for i in range(0, len(s)):
            self._hash = Xor(self._hash >> 8, self.table[Xor(ord(s[i]), \
                self._hash & 0xff,1)], self.width)

    # calculates the bytes neccessary to append to get from the current
    #  to the specified hash.
    # NB: SWAPPED ISN'T SUPPORTED
    # There are some commented out debug print's, which can be very
    #     usefull.
    # this algorithm is vaguely derived from Anarchriz's method.
    def patch(self, wanted):
        w = Xor(wanted, self.xorOut, self.width)
        lut = []
        for i in range(0,len(self.table)):
            lut.append(self.table[i])
        lut.sort()
        m = []
        r = ''
        for p in range(0, self.width):
            m.append((self._hash & (256**(p+1)-1)) >> (8 * p))
        for p in range(0, self.width):
            m.append((w & (256**(p+1)-1)) >> (8 * p))
        for p in range(self.width - 1, -1, -1):
            o = lut[m[p+self.width]]
            #pm(m)
            #print 's: ' + hex(m[p+self.width]) + ' v: ' + NumberToHexadecimal(o) + ' i: ' + hex(self.table.index(o))
            #for db in range(0,p):
            #    print hex(m[db])
            #print hex(m[p]) + " ^ " + hex(self.table.index(o)) + " -> " + hex(Xor(m[p],self.table.index(o),1))
            for q in range(0,self.width):
                v = (o & (256**(q+1)-1)) >> (8 * q)
            #    print hex(v) + " ^ " + hex(m[p+q+1]) + ' -> ' + hex(Xor(m[p+q+1],v,1))
                m[p+q+1] = Xor(m[p+q+1],v,1)
            m[p] = Xor(m[p],self.table.index(o),1)
            #for db in range(p+self.width,self.width*2-1):
            #    print hex(m[db])
        #pm(m)
        for p in range(0, self.width):
            r += chr(m[p])
        return r

    hash = property(getHash)

#def pm(m):
#    r = ''
#    for i in range(0,len(m)):
#        r += " " + PadStringLeft(NumberToHexadecimal(m[i]),2,'0')
#    print r

class Crc32Provider(CrcProvider):
    def __init__(self, width = 4, polynomial = 79764919, reflected = True,
        initial = 4294967295, xorOut = 4294967295, swapped = False):
        return CrcProvider.__init__(self, width, polynomial, reflected, \
            initial, xorOut, swapped)

class Crc16Provider(CrcProvider):
    def __init__(self, width = 2, polynomial = 32773, reflected = True,
        initial = 0, xorOut = 0, swapped = False):
        return CrcProvider.__init__(self, width, polynomial, reflected, \
            initial, xorOut, swapped)
class FlCrcProvider(CrcProvider):
    def __init__(self, width = 4, polynomial= 671105024, reflected = False,
        initial = 0, xorOut = 0, swapped = True):
        return CrcProvider.__init__(self, width, polynomial, reflected, \
            initial, xorOut, swapped)

# gets the binary representation of the number and turns it around.
#  algorithm could be more efficient.
# this function can be used to get a reflected polynomial to generate
#  a reversed crc table.
# The default width is 4 bytes, this is the extra '0' padding done to ensure 1
#  will become 2147483648 instead of 1.
def ReflectNumber(number, width = 32):
    b = PadStringLeft(NumberToBinary(number), width, '0')
    return NumberFromBinary(ReverseString(b))

if __name__ == '__main__':
    crc32 = Crc32Provider()
    print "We take a message which has the hash 0xdeadbeaf"
    # Thanks to path:
    #   http://blog.w-nz.com/archives/2005/07/15/reversing-crc/#comments
    crc32._hash = crc32.xorOut ^ NumberFromHexadecimal('deadbeaf')
    print "Required patch to make the hash 0x12345678:"
    p = crc32.patch(NumberFromHexadecimal('12345678'))
    print p
    print "Applying patch, resulting hash:"
    crc32.update(p)
    print NumberToHexadecimal(crc32.hash)
    print "It works ^_^"
