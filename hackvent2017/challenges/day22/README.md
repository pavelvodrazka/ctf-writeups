# Day 22: frozen flag

Todays flag is frozen. Its quite cold in santas house at the north pole.

Can you help him to unfreeze it?

[Get the frozen flag here ...](files/frozen_flag.zip "frozen_flag.zip")

### Solution

Ok, let's do the usual first steps to find out what we got.

```bash
$ unzip frozen_flag.zip 
Archive:  frozen_flag.zip
  inflating: HV17-flag               
  inflating: frozen.exe
$ file frozen.exe HV17-flag 
frozen.exe: PE32 executable (console) Intel 80386 (stripped to external PDB), for MS Windows
HV17-flag:  data
```

We have a [PE32 executable](files/frozen.exe "frozen.exe") and a [binary file](files/HV17-flag) which looks like encrypted version of the flag.

I used Krypto Analyzer from [PE iDentifier](https://www.aldeid.com/wiki/PEiD) to analyze given PE32 executable. This was the result:

```
ICE [long] :: 000086C0 :: 0040A0C0
        Referenced at 004014F5
        Referenced at 00401538
        Referenced at 00401581
        Referenced at 004015CA
```

At that point I understood why this challenge is called "*frozen flag*". It uses ICE block cipher.

I found very useful [page](http://www.darkside.com.au/ice/) about this cipher. I studied provided [C implementation](http://www.darkside.com.au/ice/ice.c) which helped me a lot with orientation in disassembled code from IDA. I renamed all the important functions in the pseudocde to make it more understandable.

```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char v4; // ST00_1
  void *v5; // esp
  char v6; // ST00_1
  void *v7; // esp
  char v8; // [esp+0h] [ebp-48h]
  char v9; // [esp+1h] [ebp-47h]
  char v10; // [esp+2h] [ebp-46h]
  char v11; // [esp+3h] [ebp-45h]
  char v12; // [esp+4h] [ebp-44h]
  char v13; // [esp+5h] [ebp-43h]
  char v14; // [esp+6h] [ebp-42h]
  char v15; // [esp+7h] [ebp-41h]
  FILE *v16; // [esp+8h] [ebp-40h]
  int v17; // [esp+Ch] [ebp-3Ch]
  void *v18; // [esp+10h] [ebp-38h]
  size_t v19; // [esp+14h] [ebp-34h]
  void *v20; // [esp+18h] [ebp-30h]
  size_t v21; // [esp+1Ch] [ebp-2Ch]
  size_t v22; // [esp+20h] [ebp-28h]
  FILE *v23; // [esp+24h] [ebp-24h]
  const char *v24; // [esp+28h] [ebp-20h]
  int i; // [esp+2Ch] [ebp-1Ch]
  int *v26; // [esp+38h] [ebp-10h]

  v26 = &argc;
  sub_402760();
  if ( argc == 1 )
    return -1;
  v8 = 'i';
  v9 = 'c';
  v10 = 'e';
  v11 = '-';
  v12 = 'c';
  v13 = 'o';
  v14 = 'l';
  v15 = 'd';
  v24 = "frozen water";
  v23 = fopen(argv[1], "rb");
  fseek(v23, 0, 2);
  v22 = ftell(v23);
  rewind(v23);
  v21 = v22 - 1;
  v5 = alloca(sub_4029C0(v4));
  v20 = &v8;
  v19 = v22 - 1;
  v7 = alloca(sub_4029C0(v6));
  v18 = &v8;
  fread(v20, v22, 1u, v23);
  fclose(v23);
  v17 = ice_key_create(1);
  sub_401B6A(v17, &v8);
  for ( i = 0; i < (signed int)v22; i += 8 )
    ice_key_encrypt(v17, (int)v20 + i, (int)v18 + i);
  v16 = fopen("HV17-flag", "wb");
  fwrite(v18, v22, 1u, v16);
  fclose(v16);
  return 0;
}
```

It was clear that given PE32 executable uses ICE cipher (level 1) to encrypt given input text. The password being used is `ice-cold`.

Then I took [Java implementation](http://www.darkside.com.au/ice/IceKey.java) from the same site and used it to decrypt given HV17-flag file. To do that I wrote a short program (source can be found [here](../../src/main/scala/hackvent2017/Day22.scala)).

```scala
val encrypted = Files.readAllBytes(Paths.get("hackvent2017/challenges/day22/files/HV17-flag"))
val key = "ice-cold"

val ice = new IceKey(1)
ice.set(key.getBytes)

val flag = encrypted.grouped(8).map { enc =>
  val dec = Array.ofDim[Byte](8)
  ice.decrypt(enc, dec)
  ascii(dec)
}.mkString

print(flag)
```

The decrypted flag was:

```
HV17-9VmF-xULb-fRVU-pvgb-KhZo
```