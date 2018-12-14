package hackvent2018

object Day11 extends App {

  // c = (a * b) % p
  val c = BigInt("7E65D68F84862CEA3FCC15B966767CCAED530B87FC4061517A1497A03D2", 16)
  val p = BigInt("DD8E05FF296C792D2855DB6B5331AF9D112876B41D43F73CEF3AC7425F9", 16)
  val b = BigInt("7BBE3A50F28B2BA511A860A0A32AD71D4B5B93A8AE295E83350E68B57E5", 16)

  assert(gcd(b, p) == 1, "`b` and `p` are not coprimes!")

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

  println(flag)

}

