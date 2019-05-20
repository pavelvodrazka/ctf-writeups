#!/usr/bin/env python2

import sys
import zlib
from binascii import unhexlify
from struct import unpack

# returns [position, size, type, data, crc]
def get_chunk(buf, pos):
    size = unpack('!I', buf[pos:pos + 4])[0]
    return [
        pos,  # chunk position
        buf[pos:pos + 4],  # chunk size
        buf[pos + 4:pos + 8],  # chunk type
        buf[pos + 8:pos + 8 + size],  # chunk data
        buf[pos + 8 + size:pos + 12 + size]  # chunk crc
    ]

png = open(sys.argv[1]).read()

pos = 8
chunks = []
for i in range(8):
    chunks.append(get_chunk(png, pos))
    pos += unpack('!I', chunks[i][1])[0] + 12

# decompressed data length = height x (width * 4 + 1)
decompressed = zlib.decompress(chunks[6][3])
height = unpack('!I', (chunks[0][3][4:8]))[0]
width = unpack('!I', (chunks[0][3][:4]))[0]
block_size = width * 4 + 1

filterbits = ''
for i in range(0, len(decompressed), block_size):
    bit = unpack(str(block_size) + 'c', decompressed[i:i + block_size])[0]
    if bit == '\x00':
        filterbits += '0'
    elif bit == '\x01':
        filterbits += '1'

flag = ''
filterbits_chunks = [filterbits[i:i + 8] for i in xrange(0, len(filterbits), 8)]
for x in filterbits_chunks:
    if x == '00000000': break
    flag += unhexlify('%x' % int('0b' + str(x), 2))

print(flag)
