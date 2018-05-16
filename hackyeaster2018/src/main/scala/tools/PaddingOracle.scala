package tools

object PaddingOracle {

  private val DEFAULT_BLOCK_SIZE = 16

  def apply(oracle: Array[Byte] => Boolean): PaddingOracle = apply(oracle, DEFAULT_BLOCK_SIZE)
  def apply(oracle: Array[Byte] => Boolean, blocksize: Int): PaddingOracle = new PaddingOracle(oracle, blocksize)

}

class PaddingOracle(oracle: Array[Byte] => Boolean, blocksize: Int) {

  // byte guesses optimized for text messages
  private val guesses = (
    (32 to 32) ++ // space
    (97 to 122) ++ (65 to 90) ++ // letters
    (48 to 57) ++ // numbers
    (33 to 47) ++ (58 to 64) ++ (91 to 96) ++ (123 to 127) ++ (1 to 31) ++ // special characters
    (-128 to 0) // non-ascii
  ).map(_.toByte)

  def decrypt(ciphertext: Array[Byte]): Array[Byte] = {
    assert(ciphertext.length % blocksize == 0)

    val blockscnt = ciphertext.length / blocksize
    val plaintext = Array.ofDim[Byte]((blockscnt - 1) * blocksize) // remove initial vector

    for (blockno <- 1 until blockscnt) {
      val decrypted = decryptOneBlock(ciphertext, blockno)
      Array.copy(decrypted, 0, plaintext, (blockno - 1) * blocksize, blocksize)
    }

    plaintext
  }

  private def decryptOneBlock(ciphertext: Array[Byte], blockno: Int): Array[Byte] = {
    val iv = Array.ofDim[Byte](blocksize)
    val block = Array.ofDim[Byte](blocksize)
    val plain = Array.fill[Byte](blocksize)(0)

    Array.copy(ciphertext, (blockno - 1) * blocksize, iv, 0, blocksize)
    Array.copy(ciphertext, blockno * blocksize, block, 0, blocksize)

    println(s"block $blockno:")
    if (!recursiveBlockAttack(iv, block, plain, 1)) {
      throw new RuntimeException("failed")
    }

    plain
  }

  private def recursiveBlockAttack(iv: Array[Byte], block: Array[Byte], decrypted: Array[Byte], attacksize: Int): Boolean = {
    val r = iv ++ block

    // prepare padding
    val pad = attacksize.toByte
    for (i <- blocksize - attacksize + 1 until blocksize) {
      r(i) = (iv(i) ^ decrypted(i) ^ pad).toByte
    }

    // attack one byte, try all possible values
    val attackidx = blocksize - attacksize
    for (b <- guesses) {
      r(attackidx) = (iv(attackidx) ^ b ^ pad).toByte

      if (oracle(r)) {
        decrypted(attackidx) = b
        println(ascii(decrypted))

        if (attacksize == blocksize) {
          return true; // success
        } else if (recursiveBlockAttack(iv, block, decrypted, attacksize + 1)) {
          return true; // recursive success
        }

        // our guess wasn't correct. for example, we may have stumbled upon 02 02 when we thought we had found 01.
        decrypted(attackidx) = 0 // cleanup bad finding
      }
    }

    false
  }

  private def ascii(n: Byte): Char = (n.toInt & 0xff).toChar
  private def ascii(n: Array[Byte]): String = n.map(ascii).mkString

}
