# Day 07: Flappy.pl

Time for a little game. It's hardly obfuscated, i promise ... ;-)

[Get flappy](files/flappy.pl)

### Description

Flappy was a vertical-scrolling ASCII clone of Flappy Birds game written in Perl. Each pipe obstacle was made of one flag character. In order to get the flag you could either play the game to the end or hack its code.

### Solution

I had to decompile it first to be able to take a look at its source code.

```bash
$ perl -MO=Deparse flappy.pl > flappy-decompiled.pl
```

[Decompiled version](files/flappy-decompiled.pl) was a bit more readable. 

By commenting out two lines of code I created a [hacked version](files/flappy-decompiled-hacked.pl) which lacked any collision detection so I simply ran it a waited until the end to collect all the characters of the flag.

Because that wasn't funny enough I decided to write a [simple bot](files/flappy-decompiled-bot.pl) to play the game to the end without any hacks. To do that I changed implementation of `rk()` function responsible for reading pressed keys.

Then I simply collected the flag.

```
HV18-bMnF-racH-XdMC-xSJJ-I2fL
```
