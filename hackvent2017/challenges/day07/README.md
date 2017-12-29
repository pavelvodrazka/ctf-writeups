# Day 07: i know ...

*... what you did last xmas*

We were able to steal a file from santas computer. We are sure, he prepared a gift and there are traces for it in this file.

Please help us to recover it: [Download](files/SANTA.FILE "SANTA.FILE")

### Solution

Let's take a look what we got.

```
$ file SANTA.FILE 
SANTA.FILE: Zip archive data, at least v1.0 to extract
$ unzip SANTA.FILE 
Archive:  SANTA.FILE
  inflating: SANTA.IMA
$ file SANTA.IMA 
SANTA.IMA: DOS/MBR boot sector, code offset 0x58+2, OEM-ID "WINIMAGE", sectors/cluster 4, root entries 16, sectors 3360 (volumes <=32 MB), sectors/FAT 3, sectors/track 21, serial number 0x2b523d5, label: "           ", FAT (12 bit), followed by FAT
```

It is a ZIP archive containing file [SANTA.IMA](files/SANTA.IMA "SANTA.IMA") which is a disk image.

I feel lucky so let's try to use `strings` instead of mounting it.

```
$ strings SANTA.IMA | grep HV17
Y*C:\Hackvent\HV17-UCyz-0yEU-d90O-vSqS-Sd64.exe
```

Not exactly intended way to solve the challenge but it worked ;)

The recovered flag is:

```
HV17-UCyz-0yEU-d90O-vSqS-Sd64
```