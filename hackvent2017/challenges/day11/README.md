# Day 11: Crypt-o-Math 2.0

So you bruteforced last years math lessions? This time you cant escape!

```
c = (a * b) % p
c=0x559C8077EE6C7990AF727955B744425D3CC2D4D7D0E46F015C8958B34783
p=0x9451A6D9C114898235148F1BC7AA32901DCAE445BC3C08BA6325968F92DB
b=0xCDB5E946CB9913616FA257418590EBCACB76FD4840FA90DE0FA78F095873
```

find "a" to get your flag.

### Solution

We have to solve the following modular equation to get the flag.

```
a * b ≡ c (mod p)
```

To do that we need to calculate `s` as modular multiplicative inverse of `b`. It has the following property.

```
b * s ≡ 1 (mod p)
```

Now we can multiple both sides of equation by `s`.

```
a * b * s ≡ c * s (mod p)
```

The equation can be then simplified and `a` can be calculated like this.

```
a ≡ c * s (mod p)
```

I wrote a really short Scala program (source code can be found [here](../../src/main/scala/hackvent2017/Day11.scala)) to do the math.

```scala
private val c = BigInt("423EDCDCDCD928DD43EAEEBFE210E694303C695C20F42A27F10284215E90", 16)
private val p = BigInt("B1FF12FF85A3E45F722B01BF3135ED70A552251030B114B422E390471633", 16)
private val b = BigInt("88589F79D4129AB83923722E4FB6DD5E20C88FDD283AE5724F6A3697DD97", 16)

def main(args: Array[String]): Unit = {
  val s = b.modInverse(p)
  val a = (c * s) % p
  println(ascii(a.toByteArray.slice(0, 29)))
}
```

This is its output.

```
HV17-XtDw-0DzO-YRgB-2b2e-UWNz
```