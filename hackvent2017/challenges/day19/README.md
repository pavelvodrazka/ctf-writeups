# Day 19: Cryptolocker Ransomware

*Pay the price, Thumper did it already!*

This flag has been taken for ransom. Transfer 10'000 Szabo to `0x1337C8b69bcb49d677D758cF541116af1F2759Ca` with your HACKvent username (case sensitive) in the transaction data to get your personal decryption key. To get points for this challenge, enter the key in the form below.

Disclaimer: No need to spend r34l m0n3y!


Enter your 32-byte decryption key here. Type it as 64 hexadecimal characters without 0x at the beginning.

| put your 64 hexadecimal characters here ... |
| ------------------------------------------- |

### Solution

The first step was to find given target address on [etherscan.io](https://etherscan.io/address/0x1337C8b69bcb49d677D758cF541116af1F2759Ca). 

It contains following [contract code](files/contract.hexed "contract.hexed").

```
0x6060604052600436106100405763ffffffff7c0100000000000000000000000000000000000000000000000000000000600035041663ea8796348114610154575b662386f26fc100003410610152577fec29ee18c83562d4f2e0ce62e38829741c2901da844c015385a94d8c9f03d486600260003660116000604051602001526040517f485631372d00000000000000000000000000000000000000000000000000000081526005810184848082843782019150508260ff167f0100000000000000000000000000000000000000000000000000000000000000028152600101935050505060206040518083038160008661646e5a03f1151561010157600080fd5b5050604051805190506040519081526040602082018190526011818301527f596f7572206b657920697320686572652e00000000000000000000000000000060608301526080909101905180910390a15b005b341561015f57600080fd5b61015260005473ffffffffffffffffffffffffffffffffffffffff9081169030163180156108fc0290604051600060405180830381858888f1935050505015156101a857600080fd5b5600a165627a7a7230582020304ba8cb5786445e5c47f840741111591a38057d40ac139568b31f9eaee3c70029
```

When you convert it to ASCII it contains text "*Your key is here*". This is definitely way to go! 

I looked at transactions list and found link to the [Thumper's transaction](https://etherscan.io/tx/0x6d5d42529ea3945df02a8cc8e6b16bd549b4cfced4e24e8f258e353a772995fb) mentioned in the description. It was easy to verify sender by converting transaction's input data `0x5468756d706572` from HEX to ASCII: `Thumper`.

Then I downloaded [geth](https://geth.ethereum.org) emulator (package including tools) and disassembled hexed contract code using following command.

```bash
$ ./geth/evm disasm contract.hexed > contract.opcodes
```

There were some missing opcodes in the result [contract.opcodes](files/contract.opcodes "contract.opcodes") but I simply ignored them.

This [document](http://gavwood.com/Paper.pdf) helped me to understand disassembled instructions to the point I was able to understand the contract and bypass the transaction value check by patching hexed contract OP@74 from `0x10` (LT) to `0x11` (GT). 

I borrowed input data from Thumper's transaction and prepared a simple bash script to debug contract.

```bash
#!/bin/bash

./geth/evm \
    --codefile contract-patched.hexed \
    --input "$1" \
    --sender 0xBaD67322a9fEb4DA8277262c04176493869Dc6 \
    --receiver 0x1337C8b69bcb49d677D758cF541116af1F2759Ca \
    --dump \
    --debug \
    run
```

When I ran the script with Thumper's input `5468756d706572` and got this result:

```bash
$ ./run.sh 5468756d706572
... output truncated ...
#### LOGS ####
LOG1: 1337c8b69bcb49d677d758cf541116af1f2759ca bn=0 txi=0
00000000  ec29ee18c83562d4f2e0ce62e38829741c2901da844c015385a94d8c9f03d486
00000000  98 80 cc cf e8 1a 07 5f  f0 d0 29 b4 35 1e f4 49  |......._..).5..I|
00000010  6a e4 52 19 9b 83 16 34  af 57 e5 95 14 66 34 9d  |j.R....4.W...f4.|
00000020  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 40  |...............@|
00000040  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000050  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 11  |................|
00000060  59 6f 75 72 20 6b 65 79  20 69 73 20 68 65 72 65  |Your key is here|
00000070  2e 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
```

Values from memory dump were identical to the values from [event log](https://etherscan.io/tx/0x6d5d42529ea3945df02a8cc8e6b16bd549b4cfced4e24e8f258e353a772995fb#eventlog) of the original Thumper's transaction. Hooray!

It was time to prepare input data for my own transaction by converting my username `pjslf` to HEX: `706a736c66`.

Then I ran the script again with my input data:

```bash
$ ./run.sh 706a736c66
... output truncated ...
#### LOGS ####
LOG1: 1337c8b69bcb49d677d758cf541116af1f2759ca bn=0 txi=0
00000000  ec29ee18c83562d4f2e0ce62e38829741c2901da844c015385a94d8c9f03d486
00000000  1a 9e 53 a1 13 de f7 f9  16 2b d1 23 f5 01 68 3d  |..S......+.#..h=|
00000010  0f cf 69 6a b0 87 7a bd  b3 ed e6 85 cf bb 78 fc  |..ij..z.......x.|
00000020  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 40  |...............@|
00000040  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000050  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 11  |................|
00000060  59 6f 75 72 20 6b 65 79  20 69 73 20 68 65 72 65  |Your key is here|
00000070  2e 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
```

The last step was to extract my personal decryption key from the memory dump:

```
1a9e53a113def7f9162bd123f501683d0fcf696ab0877abdb3ede685cfbb78fc
```

and submit it to the challenge's form to get the credit.