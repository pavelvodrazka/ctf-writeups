package hackvent2018

import javax.crypto.Cipher
import javax.crypto.spec.SecretKeySpec

object Day15 extends App {

  val ciphertext = b64dec("xQ34V+MHmhC8V88KyU66q0DE4QeOxAbp1EGy9tlpkLw=")
  val seed = hex2bytes("7551415c2d6e4d403d31776c1e624e21")

  val plaintext = aesDecrypt(ciphertext, calculateKey(seed))
  val flag = ascii(plaintext.slice(0, 29))
  println(flag)

  def calculateKey(seed: Array[Byte]): Array[Byte] = {
    seed.zipWithIndex.map { case (b, i) =>
      if (i == 0) 120
      else b + 3
    }.map(_.toByte)
  }

  def aesDecrypt(bytes: Array[Byte], key: Array[Byte]): Array[Byte] = {
    val keyspec = new SecretKeySpec(key, "AES")
    val cipher = Cipher.getInstance("AES/ECB/NoPadding")
    cipher.init(Cipher.DECRYPT_MODE, keyspec)
    cipher.doFinal(bytes)
  }

}
