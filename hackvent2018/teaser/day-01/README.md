# Day -01: Xenon.elf

After solving the [previous](../day-02/README.md) teaser challenge I noticed that there was another [z.zip](files/z.zip) file left. But unlike the others this one was not protected by any password.

```
$ unzip z.zip 
Archive:  z.zip
  inflating: xenon.elf               
$ file xenon.elf 
xenon.elf: ELF 32-bit MSB executable, PowerPC or cisco 4500, version 1 (SYSV), statically linked, with debug_info, not stripped
```

It contained a Xbox 360 ELF binary named [xenon.elf](files/xenon.elf). Since I didn't find any usable PowerPC decompiler I had to settle for [dissasembled code](files/xenon.asm) I got from IDA.

Thankfully the easier version of this challenge added DWARF debugging data which helped me a lot! I was able to recognize [RC4 cipher](https://en.wikipedia.org/wiki/RC4) used in the program and verify it against [this](https://gist.github.com/rverton/a44fc8ca67ab9ec32089) implementation in C. Both functions `rc4_init` and `rc4_crypt` matched exactly.

Further static analysis of the code revealed 3 interesting variables:
- `hint`
- `ciphertext`
- `rc4_key`

I decided to start with the hint which seemed pretty easy.

```c
hint[0]  = 0x4920776973682049
hint[8]  = 0x2077617320612044
hint[16] = 0x65766B6974203A28
hint[24] = 0x00
```

Converted to ASCII:
> I wish I was a Devkit :(

Ciphertext was next.

```c
ciphertext[0]  = 0xDF6658C0
ciphertext[4]  = 0x5E93C8D4
ciphertext[8]  = 0xC4E95E36
ciphertext[12] = 0xB155144A
ciphertext[16] = 0xBE83C90A
ciphertext[20] = 0xDC2BC5F0
ciphertext[24] = 0x8FABBBAC
ciphertext[28] = 0x49DD0F01
ciphertext[32] = 0x97F6668B
ciphertext[36] = 0x07A0B443
```

Hexed string:

> DF6658C05E93C8D4C4E95E36B155144ABE83C90ADC2BC5F08FABBBAC49DD0F0197F6668B07A0B443

Now things got more complicated. The RC4 encryption key assembly was based on the return value of `xenon_secotp_read_line` function from the [libxenon](https://github.com/Free60Project/libxenon) library. Its [source code](https://github.com/Free60Project/libxenon/blob/master/libxenon/drivers/xenon_soc/xenon_secotp.c) revealed that it reads values from memory area beginning at `0x20020000`. I learned from the library documentation that this function reads so called [e-fuse sets](https://free60project.github.io/wiki/Fusesets.html) of the Xbox 360 CPU.


The function was called twice in total. The first call read value of e-fuse set #0: `0xC0FFFFFFFFFFFFFF`. The second call read value of e-fuse set #1 which differs for retail and devkit version of the console. With regard to the hint I used the devkit value: `0x0F0F0F0F0F0F0F0F`.

```asm
li        r4, -1
# ... snip ...
li        r3, 0
bl        xenon_secotp_read_line    # r3 = xenon_secotp_read_line(0) // 0xC0FFFFFFFFFFFFFF
mr        r8, r4                    # r8 = -1
insrdi    r8, r3, 32,0              # r8 = 0xC0FFFFFFFFFFFFFF
li        r3, 1                     # r3 = 1
# ... snip ...
bl        xenon_secotp_read_line    # r3 = xenon_secotp_read_line(1) // 0x0F0F0F0F0F0F0F0F
# ... snip ...
insrdi    r4, r3, 32,0              # r4 = 0x0F0F0F0F0F0F0F0F
```

The e-fuse set values were prepared in in registers `r8` and `r4`. Then the key assembly followed.

```asm
li        r27, 8                    # r27 = 8
mtctr     r27                       # ctr = 8
# ... snip ...
li        r9, 0                     # r9 = 0
# ... snip ...
loc_80002008:                       # do {
srawi     r7, r9, 1                 #   r7 = r9 / 2
addze     r7, r7                    #   ...
addi      r10, r1, 0x1A0+rc4_key    #   r10 = rc4_key
subfic    r7, r7, 7                 #   r7 = 7 - r7
slwi      r7, r7, 3                 #   r7 = r7 << 3
srd       r6, r8, r7                #   r6 = r8 >> r7 // low 7 bits of r7
srd       r7, r4, r7                #   r7 = r4 >> r7 // low 7 bits of r7
stbux     r6, r10, r9               #   rc4_key[r9] = r6; r10 = rc4_key + r9 // low 8 bits stored
addi      r9, r9, 2                 #   r9 = r9 + 2
stb       r7, 1(r10)                #   rc4_key[r9 + 1] = r7 // low 8 bits stored
bdnz      loc_80002008              # } while (--ctr != 0)
```

To get the key value I [rewrote](../../src/main/scala/hackvent2018/Teaser01.scala) the algorithm to Scala.

```scala
val fuses = Array(0xC0FFFFFFFFFFFFFFL, 0x0F0F0F0F0F0F0F0FL)

def assembleKey(): Array[Byte] = {
  val key: Array[Byte] = Array.ofDim(16)

  var r7 = 0L
  var r6 = 0L

  for (idx <- 0 until 16 by 2) {
    r7 = (7 - idx / 2) << 3

    r6 = fuses(0) >> (r7 & 0x7F)
    r7 = fuses(1) >> (r7 & 0x7F)

    key(idx) = (r6 & 0xFF).toByte
    key(idx + 1) = (r7 & 0xFF).toByte
  }

  key
}
```
 
RC4 encryption key: `0xC00FFF0FFF0FFF0FFF0FFF0FFF0FFF0F`

Then I used this [online tool](http://rc4.online-domain-tools.com/) to decrypt the hardcoded ciphertext using the key I assembled. Here is the decrypted plaintext message.

> SFYxOC1MSUJYLUVOT04tSVNTVC1JTExBLUxJVkU=

It was obviously a Base64 encoded string so I decoded it in commandline.

```
$ echo "SFYxOC1MSUJYLUVOT04tSVNTVC1JTExBLUxJVkU=" | base64 -d
HV18-LIBX-ENON-ISST-ILLA-LIVE
```

Flag: `HV18-LIBX-ENON-ISST-ILLA-LIVE`
