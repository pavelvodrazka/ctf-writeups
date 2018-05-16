# 18 - Egg Factory

Make the egg factory write a secret word!

Then enter it into the Egg-o-Matic below, uppercase and underscores only.

[A.8xp](files/A.8xp)

### Solution

The first thing was to identify the file.

```bash
$ file A.8xp
A.8xp: TI-83+ Graphing Calculator (program)
```

Next logical step was to get some TI-83+ emulator to run the code. I found [TilEm](http://lpg.ticalc.org/prj_tilem/) which worked pretty good.

I ran the program which gave me this prompt:

```
EggFactory v0.3
Status: Dev
ENTER CREDENTIALS:
   1. USERNAME
   2. PASSWORD
------------------
> 
```

I played a bit with it and then I decided to decompile the program to figure out what was going on inside. To do it I used this [online tool](https://www.cemetech.net/sc/).

I spent some time with the decompiled [source code](files/A.8xp.source) and a TI-83+ programming manual trying to understand it. I used *Disp* debug messages a lot!

The first interesting finding was that there was a hidden conditional branch which was triggered by any input other than 1 and 2. This branch was responsible for some drawing but its code was dependant on the password value.

I had to find the right password to get the right drawing from it. Working with the emulator was not comfortable enough so I rewrote the code to a Scala [program](../../src/main/scala/hackyeaster2018/Egg18.scala).

Encoding used for username was obvious - it was the ROT13 cipher. The right username was therefore `BUNNYADMIN_12128290`. It was a bit harder with password. I was too lazy to identify it so I decided to bruteforce it instead. The right password was `283`. 

I ran the program in emulator again, entered the expected password and let it to draw the message. Unfortunately it displayed only a part of it and I had to find a way how to zoom out or scroll to the right to see it all. I had some difficulties with the emulator with this stage, but I eventually managed it.

![solution.png](files/solution.png "solution.png")

The password was:

```
WOW_N1CE_HAX
```

### Egg

![egg.png](files/egg.png "egg.png")