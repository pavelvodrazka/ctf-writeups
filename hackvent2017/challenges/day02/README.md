# Day 02: Wishlist

*The fifth power of two*

Something happened to my wishlist, please help me.

[Get the Wishlist](files/Wishlist.txt "Wishlist.txt")

### Solution

Content of given file is without any doubts a Base64 encoded string. But it's quite long and it still looks like another Base64 string after decoding. So we need to do more iterations of Base decoding - probably 32 (*the fifth power of two*)? Let's see...

We can do this by hand using any online tool or use the following simple Scala program (source code can be found [here](../../src/main/scala/hackvent2017/Day02.scala)) to find the flag for us. 

```scala
var s = Source.fromURL("https://hackvent.hacking-lab.com/Wishlist.txt").mkString
while (!s.startsWith("HV17")) {
  s = ascii(b64Decode(s.replaceAll("\n", "")))
}
println(s)
```

After 32 iterations we'll get the result flag:

```
HV17-Th3F-1fth-Pow3-r0f2-is32
```