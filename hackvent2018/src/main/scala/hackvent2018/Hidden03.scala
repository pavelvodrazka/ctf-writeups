package hackvent2018

object Hidden03 extends App {

  val ciphertext = BigInt("1398ed7f59a62962d5a47dd0d32b71156dd6af6b46bea949976331b8e1", 16)
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

  // decrypt the flag
  val flag = decrypt(ciphertext, privkey)
  println(flag)

  // rsa decryption
  private def decrypt(ciphertext: BigInt, key: BigInt): String = ascii(ciphertext.modPow(key, modulus).toByteArray)

}
