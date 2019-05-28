package hackyeaster2019

import java.util.concurrent.TimeUnit

import javax.crypto.Cipher
import javax.crypto.spec.SecretKeySpec
import org.apache.commons.lang3.time.StopWatch

import scala.util.control.Breaks._

object Egg19 extends App {

  val encrypted = loadFromFile("hackyeaster2019/challenges/egg19/files/egg.encrypted")

  bruteforce("WITHCUDA").foreach { password =>
    println(s"password: $password")
    decrypt(password)
  }

  def decrypt(passwd: String): Unit = {
    val cipher = createCipher()
    val decrypted = decrypt(cipher, encrypted, createKey(passwd))
    saveToFile("hackyeaster2019/challenges/egg19/files/egg.png", decrypted)
  }

  def bruteforce(suffix: String): Option[String] = {
    val block = encrypted.take(16) // first block
    val expected = hex2bytes("89504e470d0a1a0a").tail // PNG header

    val alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

    var found: Option[String] = None
    breakable {
      for (p1 <- alphabet; p2 <- alphabet) {
        alphabet.par.foreach { p3 =>
          val watch = StopWatch.createStarted()

          val cipher = createCipher()
          val prefix = s"$p1$p2$p3"

          for (p4 <- alphabet; p5 <- alphabet; p6 <- alphabet; p7 <- alphabet; p8 <- alphabet) {
            val passwd = s"$prefix$p4$p5$p6$p7$p8$suffix"
            val decrypted = decrypt(cipher, block, createKey(passwd))

            if (expected.sameElements(decrypted.take(expected.length))) {
              found = Some(passwd)
            }

            if (found.nonEmpty) {
              break
            }
          }

          println(s"$prefix: searched in ${watch.getTime(TimeUnit.SECONDS)} seconds")
        }
      }
    }

    found
  }

  def createCipher(): Cipher = Cipher.getInstance("AES/ECB/NoPadding")

  def createKey(password: String): Array[Byte] = password.getBytes

  def decrypt(cipher: Cipher, encrypted: Array[Byte], key: Array[Byte]): Array[Byte] = {
    val keyspec = new SecretKeySpec(key, "AES")
    cipher.init(Cipher.DECRYPT_MODE, keyspec)
    cipher.doFinal(encrypted)
  }

}

