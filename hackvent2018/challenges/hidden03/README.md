# Hidden 03

I discovered this hidden flag while I was mistakenly trying to solve daily [challenge 14](../day14/README.md) by cracking it like it used RSA cipher inside.

Since the public exponent value of `1+1` has no modular inverse I used the most commonly used value of `65537` instead. Now I was able to calculate matching private key. For more detailed explanation of how it's done take a look at [this wikipedia page](https://en.wikipedia.org/wiki/RSA_%28cryptosystem%29#Key_generation).

```scala
val modulus = BigInt("0d8a7a45d9be42bb3f03f710cf105628e8080f6105224612481908dc721", 16)
val pubkey = BigInt("65537") // guessed

// modulus = p * q (factorized using http://factordb.com)
val p = BigInt("73197682537506302133452713613304371")
val q = BigInt("79797652691134123797009598697137499")

// calculate phi
val phi = lcm(p - 1, q - 1)
assert(pubkey.gcd(phi) == 1, "pubkey and phi are not coprimes!")

// privkey * pubkey ≡ 1 (mod phi)
val privkey = pubkey.modInverse(phi)
```

I tried to decrypt the given ciphertext `2a4c9aa52257b56837369d5dd7019451c0ec04427eb95eb741d0273d55` but the result was gibberish. As a last resort I tried to use the value of `flag.ps1`'s thumbprint defined on the first line of the PowerShell [script](../day14/files/power.ps1) instead. 

```scala
val ciphertext = BigInt("1398ed7f59a62962d5a47dd0d32b71156dd6af6b46bea949976331b8e1", 16)

// decrypt the flag
val flag = decrypt(ciphertext, privkey)
println(flag)

// rsa decryption
private def decrypt(ciphertext: BigInt, key: BigInt): String = ascii(ciphertext.modPow(key, modulus).toByteArray)
```

To my surprise it worked! Complete source code of the program can be found [here](../../src/main/scala/hackvent2018/Hidden03.scala). 

Here's the hidden flag.

```
HV18-fn8o-Az1a-cbpG-6gJd-sPkU
```
