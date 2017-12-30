package hackvent2017

object Day14 {

  private val encrypted = "7A9FDCA5BB061D0D638BE1442586F3488B536399BA05A14FCAE3F0A2E5F268F2F3142D1956769497AE677A12E4D44EC727E255B391005B9ADCF53B4A74FFC34C"

  // discovered by decompiling the binary
  private val modulus = BigInt("F66EB887F2B8A620FD03C7D0633791CB4804739CE7FE001C81E6E02783737CA21DB2A0D8AF2D10B200006D10737A0872C667AD142F90407132EFABF8E5D6BD51", 16)
  private val pubkey = BigInt("65537")

  def main(args: Array[String]): Unit = {
    // modulus = p * q
    // factorization of modulus (in decimal) done by http://factordb.com/index.php?query=12906717464348092265956410210860282684261200239649314436822666616460740520052403025774625130601134473716449192270880280937288228652858915015044165744901457
    val p = BigInt("18132985757038135691")
    val q = BigInt("711781150511215724435363874088486910075853913118425049972912826148221297483065007967192431613422409694054064755658564243721555532535827")

    // calculate phi
    val phi = lcm(p - 1, q - 1)

    // privkey * pubkey ≡ 1 (mod phi)
    val privkey = pubkey.modInverse(phi)

    println(decrypt(encrypted, privkey))
  }

  // RSA encryption: ciphertext = plaintext ^ key % modulus
  private def encrypt(plaintext: String, key: BigInt): String = {
    val base = BigInt(plaintext.getBytes)
    base.modPow(key, modulus).toString(16)
  }

  // RSA decryption: plaintext = ciphertext ^ key % modulus
  private def decrypt(ciphertext: String, key: BigInt): String = {
    val base = BigInt(ciphertext, 16)
    ascii(base.modPow(key, modulus).toByteArray)
  }

}
