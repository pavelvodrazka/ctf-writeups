# 17 - New Egg Design

Thumper is looking for a new design for his eggs. He tried several **filters** with his graphics program, but unfortunately the QR codes got unreadable. Can you help him?!

![eggdesign.png](files/eggdesign.png "eggdesign.png")

No Easter egg here. Enter the flag directly on the flag page.

### Solution

The hint was clear - to use a filter. Unluckily I misunderstood it from the beginning. I thought that the electrical circuit was a clue to use high-pass filter so I opened Gimp and ran directly into a rabbit hole.

Later I learned about [PNG filters](https://www.w3.org/TR/PNG/#9Filters). I searched for "*PNG filters steganography*" and found this [write-up](https://github.com/ctfs/write-ups-2015/tree/master/confidence-ctf-teaser-2015/stegano/a-png-tale-200) of CONFidence CTF Teaser. It described a way how to retrieve message hidden in bytes of PNG filter types. The solution expected the image to have a single IDAT chunk so as the first step I merged all the IDAT chunks of the source image into a single one using [TweakPNG](http://entropymine.com/jason/tweakpng/) tool.

Then I modified the Python script from the write-up to fit my [modified image](files/eggdesign-idat.png).

```python
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
```

It decompressed the IDAT chunk and converted the filter type byte of each block into a single binary bit. The result binary value was simply converted to ASCII.
 
```
$ ./extract_flag.py eggdesign-idat.png
Congratulation, here is your flag: he19-TKii-2aVa-cKJo-9QCj
```

### Flag

```
he19-TKii-2aVa-cKJo-9QCj
```
