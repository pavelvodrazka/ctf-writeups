# Day 13: Flappy's revenge

There were some rumors that you were cheating at our little game a few days ago ... like godmode, huh?

Well, show me that you can do it again - no cheating this time.

`telnet whale.hacking-lab.com 4242`

### Description

The game was exactly the same like the one few days ago but yet there was one small difference. You had to play it remotely using a telnet client.

### Solution

Since I already had my playing bot implemented I expected this challenge to be easy. But guess what. I was wrong...

My attempts to script the telnet client in Scala and Python failed terribly and since I wanted to avoid debugging the connection with Wireshark I desperately decided to play the game manually.

At the end it wasn't that hard and I got the flag but I still was not satisfied. So I forced myself to return back to beginning and do it the proper way!

I decided to script it in bash using the standard telnet client and [xdotool](https://github.com/jordansissel/xdotool) which can fake input from the keyboard.

First thing I did was a simple [Scala program](../../src/main/scala/hackvent2018/Day13.scala) which reused the logic of my previous bot to generate a bash script [control.sh](files/control.sh) responsible for keyboard inputs controlling the game. 

```scala
val path = Paths.get("hackvent2018/challenges/day13/files/control.sh")

val pw = new PrintWriter(path.toFile)
try {
  pw.println("#!/bin/bash")
  pw.println("sleep $DELAY") // initial delay
  
  for (frame <- 0 to 666) {
    if (shouldJump(frame)) {
      pw.println("xdotool key space") // press spacebar
    }
    pw.println("sleep $TICK") // wait until next frame
  }
} finally {
  pw.close()
}

Files.setPosixFilePermissions(path, PosixFilePermissions.fromString("rwxr-xr-x"))
```

This control script used two environment variables `DELAY` and `TICK` to make it easy to find the right framerate and initial start-up delay. This was responsibility of the second bash script [play.sh](files/play.sh).

```bash
#!/bin/bash

export DELAY=0.2
export TICK=0.2

./control.sh &
telnet whale.hacking-lab.com 4242

killall control.sh
```

It just spawned a background process generating keyboard events and then started a foreground process running the game in telnet client. 

This solution wasn't 100% accurate due to the variable telnet framerate and connection lags in general, but it managed to beat the game eventually!

Here is the flag.

```
HV18-9hYf-LSY1-hWdZ-496n-Mbda
```
