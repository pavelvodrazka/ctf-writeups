# 19 - Virtual Hen

Virtual hen lays virtual eggs. But only with the correct password it is an Easter Egg!

[create_egg](files/create_egg)

### Solution

As usual the first thing I did was to search interesting strings in the binary. These were the only interesting ones I found.

```
$ strings create_egg | grep .\\+\\.c
deteapng.c
crtstuff.c
```

I kept them in my mind in hope they could help me later.

Then I decompiled the binary with IDA and tried to understand the [decompiled code](files/create_egg.decompiled.c) as much as possible.

The `main` function does basically these steps:

1. reads 15624 bytes from address offset `0x400A20` and stores it to `v3`
2. reads a password from stdin and stores it to `v11`
3. the password buffer is trimmed to the max length of 8 characters (`n` is set to 8)
4. each password character is then modified: `v11[i] = v11[i] & 0xDF | 0x40`
5. stores parts of the password into consequent part of memory pointed by `v13`
6. calls `d` function in cycle and passes `v13` together with 8 bytes long blocks of `v3` to it
7. the `d` function directly modifies the passed block of `v3`
8. writes 15624 bytes stored in `v3` to a file called `egg`

The `d` function does some xoring and shifts on passed bytes. It also contains two interesting number constants `0xC6EF3720` and `0x61C88647`.

I tried to google those constants which directed me to the wikipedia page about the [TEA cipher](https://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm). The reference code of decryption method looked almost identical to the decompiled code of function `d`. Bingo! Now it was clear that the program is using TEA cipher to decrypt the bytes of memory stored at `0x400A20` with keys derived from the provided password. 

Then I turned my attention back to the `main` method to search for potential weaknesses. I found two of them.

The modification of given password done in the fourth step significantly reduces the alphabet to only 32 possible characters. I wrote a simple Scala script to find them.

```scala
val alphabet = (' ' to '~').map(c => (c.toInt & 0xDF | 0x40).toChar).distinct
println(s"alphabet{${alphabet.size}}: ${alphabet.mkString}")
```

The result alphabet contains only uppercase letters and few special characters:

```
alphabet{32}: @ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_
```

The second weakness was found in the way how the decryption keys are generated in the fifth step:

```c
v13 = *v11;
v14 = *(int *)((char *)v11 + 4 % v4);
v15 = *(int *)((char *)v11 + 8 % v4);
v16 = *(int *)((char *)v11 + 0xC % v4);
``` 

The password buffer length stored in `v4` is equal to 8 and therefore `v13` is equal to `v15` and `v14` is equal to `v16`. This means that only 64-bit key is used instead of 128-bit as designed.

Unfortunately, I found no way to use these weaknesses other than the brute force attack. I recalled the `deteapng.c` string which made much more sense than before: *De-TEA-PNG*. The expected result of decryption is a PNG image!

I wrote a multi-threaded brute force [cracker](files/cracker.c) in C which tried to find a key which decrypts the first block of 8 bytes to the PNG magic number `89 50 4e 47 0d 0a 1a 0a`.

Now it was time to run it and wait. And wait and wait...

```
$ gcc -O3 -fwrapv -pthread -o cracker cracker.c
$ ./cracker
alphabet: ABCDEFGHIJKLMNOPQRSTUVWXYZ@[\]^_
alphabet size: 32
spawning 8 threads...
thread[00] - started
thread[03] - started
thread[01] - started
thread[02] - started
thread[04] - started
thread[05] - started
thread[06] - started
thread[07] - started
thread[01] - time:       16 secs  |  tried:      100 Mpws  |  speed:     6.25 Mpws/sec  |  current: ABC_LYIA
thread[03] - time:       16 secs  |  tried:      100 Mpws  |  speed:     6.25 Mpws/sec  |  current: ADC_LYIA
thread[02] - time:       16 secs  |  tried:      100 Mpws  |  speed:     6.25 Mpws/sec  |  current: ACC_LYIA
thread[07] - time:       16 secs  |  tried:      100 Mpws  |  speed:     6.25 Mpws/sec  |  current: AHC_LYIA
thread[00] - time:       16 secs  |  tried:      100 Mpws  |  speed:     6.25 Mpws/sec  |  current: AAC_LYIA
thread[04] - time:       16 secs  |  tried:      100 Mpws  |  speed:     6.25 Mpws/sec  |  current: AEC_LYIA
thread[05] - time:       16 secs  |  tried:      100 Mpws  |  speed:     6.25 Mpws/sec  |  current: AFC_LYIA
thread[06] - time:       16 secs  |  tried:      100 Mpws  |  speed:     6.25 Mpws/sec  |  current: AGC_LYIA

.... snip ....

thread[00] - terminated
thread[03] - terminated
thread[01] - terminated
thread[04] - terminated
thread[06] - terminated
thread[07] - terminated
thread[05] - terminated
thread[02] - found password: H@CKYEGG
thread[02] - terminated
```

It took around 90 minutes to crack it on my quadcore laptop. The password was:

```
H@CKYEGG
```

### Egg

![egg.png](files/egg.png "egg.png")