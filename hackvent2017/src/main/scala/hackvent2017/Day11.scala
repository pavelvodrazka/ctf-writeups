package hackvent2017

object Day11 {

  // c = (a * b) % p
  private val c = BigInt("423EDCDCDCD928DD43EAEEBFE210E694303C695C20F42A27F10284215E90", 16)
  private val p = BigInt("B1FF12FF85A3E45F722B01BF3135ED70A552251030B114B422E390471633", 16)
  private val b = BigInt("88589F79D4129AB83923722E4FB6DD5E20C88FDD283AE5724F6A3697DD97", 16)

  def main(args: Array[String]): Unit = {
    // mod inverse: (b * s) ≡ 1 (mod p)
    val s = b.modInverse(p)

    // a * b ≡ c (mod p)
    // a * b * s ≡ c * s (mod p)
    // a ≡ c * s (mod p)
    val a = (c * s) % p

    println(ascii(a.toByteArray.slice(0, 29)))
  }

}
