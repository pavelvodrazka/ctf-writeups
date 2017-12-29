# Day 05: Only one hint

*OK, 2nd hint: Its XOR not MOD*

Here is your flag:

```
0x69355f71
0xc2c8c11c
0xdf45873c
0x9d26aaff
0xb1b827f4
0x97d1acf4
```

and the one and only hint:

```
0xFE8F9017 XOR 0x13371337
```

### Solution

Let's evaluate the hint expression first.

```
0xFE8F9017 XOR 0x13371337 = 0xEDB88320
```

When you search the result using Google you find a Wikipedia page about Cyclic Redundancy Check and quickly find out, that it's reversed representation of CRC-32. To get the flag we need to reverse given CRC-32 checksums.

I found a handy Python [script](files/reversecrc.py "reversecrc.py") to reverse CRC-32 [here](https://blog.affien.com/archives/2005/07/15/reversing-crc/ "Reversing CRC") and slightly modified it to fit my needs.

The rest is straightforward since we know the expected flag format. We have to reverse each checksum to a 4-characters long string.

```
0x69355f71 = crc32('HV17')
0xc2c8c11c = crc32('7pKs')
0xdf45873c = crc32('whyz')
0x9d26aaff = crc32('o6wF')
0xb1b827f4 = crc32('h4rp')
0x97d1acf4 = crc32('Qlt6')
```

The last step is to join all the parts together using hyphens and the result flag is:

```
HV17-7pKs-whyz-o6wF-h4rp-Qlt6
```