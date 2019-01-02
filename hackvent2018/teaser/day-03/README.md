# Day -03: Quickresponse.txt

I once again checked the 39A25.rar archive found in the [PDF](../day-10/files/ZOoxjUSe1OVB7OPoVrsX.pdf) but this time I was more careful and used advanced list options.

```
$ unrar lta _ZOoxjUSe1OVB7OPoVrsX.pdf.extracted/39A25.rar 
UNRAR 5.61 beta 1 freeware      Copyright (c) 1993-2018 Alexander Roshal

Archive: _ZOoxjUSe1OVB7OPoVrsX.pdf.extracted/39A25.rar
Details: RAR 4

...

        Name: STM
        Type: NTFS alternate data stream
      Target: :quickresponse.txt
        Size: 625
 Packed size: 142
       Ratio: 22%
       mtime: 2018-12-03 02:15:08,000000000
  Attributes: .B
       CRC32: 993E3536
     Host OS: Windows
 Compression: RAR 3.0(v29) -m3 -md=64K

...
```

It revealed a NTFS alternate data stream which contained a file named [quickresponse.txt](files/quickresponse.txt) hidden in the archive. Linux version of RAR was unable to extract it so I had to use WinRAR under Wine.

```
$ cat quickresponse.txt
1111111000001110001111111100000101010100110100000110111010000010111010111011011101011111010001011101101110100100010110101110110000010110000101010000011111111010101010101111111000
```

BIN to ASCII conversion didn't work but I noticed that the file contained exactly 625 = 25^2 digits so it could be a binary QR code. I made a simple string replacement which did the job.

```
  ██████████████          ██████      ██████████████
  ██          ██  ██  ██  ██    ████  ██          ██
  ██  ██████  ██          ██  ██████  ██  ██████  ██
  ██  ██████  ██  ██████████  ██      ██  ██████  ██
  ██  ██████  ██    ██      ██  ████  ██  ██████  ██
  ██          ██  ████        ██  ██  ██          ██
  ██████████████  ██  ██  ██  ██  ██  ██████████████
                    ████    ██  ████
  ██████████  ████████  ██████  ██  ██  ██  ██  ██
    ██      ██  ████  ██      ██  ████    ██████
  ██  ██████  ██  ██  ██      ██    ████      ██████
  ██████████    ████      ██  ██████████  ██  ██  ██
  ████        ██████████████  ████████  ████      ██
  ██  ██    ██          ██████      ████  ████    ██
  ██  ██      ██    ██████    ██    ██  ██      ██
  ██  ██    ██      ██    ████████  ████████  ██████
  ██  ██████  ████    ██  ██    ████████████      ██
                  ██    ██  ██    ██      ████  ██
  ██████████████  ██████      ██████  ██  ████    ██
  ██          ██    ████    ████████      ██    ██
  ██  ██████  ██  ██  ██      ██  ██████████      ██
  ██  ██████  ██  ████  ████████        ██    ██  ██
  ██  ██████  ██  ██    ████  ██  ██    ████      ██
  ██          ██  ██          ██      ████  ████
  ██████████████  ██    ████        ████          ██
```

Flag: `HV18-Idwn-whWd-9sNS-ScwC-XjSR`
