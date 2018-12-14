# Day 14: Power in the shell

Seems to be an easy one ... or wait, what?

Encrypted flag:
> 2A4C9AA52257B56837369D5DD7019451C0EC04427EB95EB741D0273D55

[power.ps1](files/power.ps1)

### Solution

I looked at the PowerShell [script](files/power.ps1) and it really *seemed to be an easy one...*

```
. "$PSScriptRoot\flag.ps1" #thumbprint 1398ED7F59A62962D5A47DD0D32B71156DD6AF6B46BEA949976331B8E1

if ($PSVersionTable.PSVersion.Major -gt 2)
{
    $m = [System.Numerics.BigInteger]::Parse($flag, 'AllowHexSpecifier');
    $n = [System.Numerics.BigInteger]::Parse("0D8A7A45D9BE42BB3F03F710CF105628E8080F6105224612481908DC721", 'AllowHexSpecifier');
    $c = [System.Numerics.BigInteger]::ModPow($m, 1+1, $n)
    write-host "encrypted flag:" $c.ToString("X");
}
```

I saw `ModPow` and instantly thought that this was just another RSA cracking challenge like a year ago. In retrospect I would rather say I rushed myself into a rabbit hole.

I was convinced that it is RSA cipher so hard that I wasted literally hours trying to find a way how to calculate working private key, perform small public exponent attack etc. None of that worked. This was the point when I finally got to the second part of the challenge description saying *...or wait, what?!*

Luckily the fact that the public exponent and calculated ϕ(pq) are not coprimes brought me to this [discussion](https://crypto.stackexchange.com/questions/30240/can-e-2-be-used-in-unpadded-rsa). From there I learned that it was a different cryptosystem called [Rabin](https://en.wikipedia.org/wiki/Rabin_cryptosystem) which helped me to get back on the track.

I followed the description of [how decryption works](https://en.wikipedia.org/wiki/Rabin_cryptosystem#Decryption) and implemented it in Scala.

```scala
def decrypt(ciphertext: BigInt, privkey: (BigInt, BigInt)): Array[BigInt] = {
  val p = privkey._1
  val q = privkey._2
  val n = p * q

  // calculate mod square roots of ciphertext
  def modSqrt(num: BigInt, modulus: BigInt): BigInt = {
    assert(modulus.mod(4) == 3)
    num.modPow((modulus + 1) / 4, modulus)
  }
  val m_p = modSqrt(ciphertext, p)
  val m_q = modSqrt(ciphertext, q)

  // find y_p, y_q such that y_p * p + y_q * q = 1 using extended euclidean algorithm
  val (y_p, y_q) = EEA.calculate(p, q)

  // calculate four square root using chinese remainder theorem
  val r_pos = (y_p * p * m_q + y_q * q * m_p).mod(n)
  val r_neg = n - r_pos
  val s_pos = (y_p * p * m_q - y_q * q * m_p).mod(n)
  val s_neg = n - s_pos

  Array(r_pos, r_neg, s_pos, s_neg)
}
```

Then I factored given public exponent using [factordb](http://factordb.com) and put it together with given ciphertext and my Rabin implementation. 

```scala
val ciphertext = BigInt("2a4c9aa52257b56837369d5dd7019451c0ec04427eb95eb741d0273d55", 16)
val pubkey = BigInt("0d8a7a45d9be42bb3f03f710cf105628e8080f6105224612481908dc721", 16)

// privkey calculated as pubkey factorization (http://factordb.com was used)
val privkey = (
  BigInt("e18eca446d6262ef2ab68be73a233", 16),
  BigInt("f5e53fa015898d185d4cd84b7655b", 16)
)

val decrypted = decrypt(ciphertext, privkey)
val flag = decrypted.map(m => ascii(m.toByteArray)).find(_.startsWith("HV18-")).get

println(flag)
```

[Here](../../src/main/scala/hackvent2018/Day14.scala) is the complete source of that program. It worked like a charm.

And here is the decrypted flag.

```
HV18-DzKn-62Qz-dAab-fEou-ImjY
```
