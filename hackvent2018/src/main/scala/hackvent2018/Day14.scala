package hackvent2018

object Day14 extends App {

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

  // rabin cipher
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

  // extended euclidean algorithm
  object EEA {

    def calculate(a: BigInt, b: BigInt): (BigInt, BigInt) = {
      calculate(Iteration(a, b, 1, 0, 0, 1))
    }

    private def calculate(i: Iteration): (BigInt, BigInt) = {
      if (i.rPrime != 0) {
        val d = i.r / i.rPrime
        calculate(Iteration(
          i.rPrime, i.r - d * i.rPrime,
          i.xPrime, i.x - d * i.xPrime,
          i.yPrime, i.y - d * i.yPrime))
      } else {
        (i.x, i.y)
      }
    }

    private case class Iteration(
      r: BigInt, rPrime: BigInt,
      x: BigInt, xPrime: BigInt,
      y: BigInt, yPrime: BigInt
    )

  }

}
