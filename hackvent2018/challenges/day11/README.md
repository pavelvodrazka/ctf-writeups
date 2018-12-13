# Day 11: Crypt-o-Math 3.0

Last year's challenge was too easy? Try to solve this one, you h4x0r!

```
c = (a * b) % p
c=0x7E65D68F84862CEA3FCC15B966767CCAED530B87FC4061517A1497A03D2
p=0xDD8E05FF296C792D2855DB6B5331AF9D112876B41D43F73CEF3AC7425F9
b=0x7BBE3A50F28B2BA511A860A0A32AD71D4B5B93A8AE295E83350E68B57E5
```

finding "a" will give you the flag.

### Solution

The solution was the same as last year except for one additional step at the very end.

We have to solve the following congruence equation to get the flag.

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

Such congruence equation has by definition infinite number of solutions `a + n * p`. To get the flag we have to find suitable integer value of `n`.

I wrote a really short Scala program (complete source code can be found [here](../../src/main/scala/hackvent2018/Day11.scala)) to do the math.

```scala
// c = (a * b) % p
val c = BigInt("7E65D68F84862CEA3FCC15B966767CCAED530B87FC4061517A1497A03D2", 16)
val p = BigInt("DD8E05FF296C792D2855DB6B5331AF9D112876B41D43F73CEF3AC7425F9", 16)
val b = BigInt("7BBE3A50F28B2BA511A860A0A32AD71D4B5B93A8AE295E83350E68B57E5", 16)

assert(b.gcd(p) == 1, "`b` and `p` are not coprimes!")

// mod inverse: (b * s) ≡ 1 (mod p)
val s = b.modInverse(p)

// a * b ≡ c (mod p)
// a * b * s ≡ c * s (mod p)
// a ≡ c * s (mod p)
val a = (c * s) % p

// flag = a + (n * p)
val flag = Stream.from(1).map { n =>
  val solution = a + (n * p)
  ascii(solution.toByteArray.slice(0, 29))
}.find(_.startsWith("HV18-")).get
```

This is the result for `n = 1337`.

```
HV18-xLvY-TeNT-YgEh-wBuL-bFfz
```
