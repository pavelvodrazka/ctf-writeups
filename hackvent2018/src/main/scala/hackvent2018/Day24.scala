package hackvent2018

import java.nio.file.attribute.BasicFileAttributes
import java.nio.file.{Files, Paths}

import hackvent2018.day24.Cipher3
import tools.QR

object Day24 extends App {

  val pngMagicNum = Array(0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a).map(_.toByte)

  val redPill = decryptRedPill("hackvent2018/challenges/day24/files/redpill/flag_encrypted")
  val bluePill = decryptBluePill("hackvent2018/challenges/day24/files/bluepill/flag_encrypted")

  val merged = redPill.zip(bluePill).map({ case (red, blue) => (red | blue).toByte })
  storeBytes("hackvent2018/challenges/day24/files/flag.png", merged)

  val flag = QR.decode("hackvent2018/challenges/day24/files/flag.png").get
  println(s"flag: $flag")

  def decryptRedPill(file: String): Array[Byte] = {
    val serial = RedPill.crackSerial(file)
    println(s"red pill serial: $serial")

    RedPill.decrypt(loadBytes(file), serial)
  }

  def decryptBluePill(file: String): Array[Byte] = {
    val iv = BluePill.crackIV(file)
    println(s"blue pill iv: ${hex(iv)}")

    BluePill.decrypt(loadBytes(file), iv)
  }

  object RedPill {

    def crackSerial(encfile: String): String = {
      val expected = loadBytes(encfile).slice(0, 4)
      def formatSerial(i: Int): String = new StringBuilder("%08d".format(i)).insert(2, '-').insert(6, '-').toString()

      Stream.from(0).take(100000000).find(i => {
        val encrypted = encrypt(pngMagicNum, formatSerial(i))
        encrypted.sameElements(expected)
      }).map(formatSerial).get
    }

    def encrypt(data: Array[Byte], serial: String): Array[Byte] = crypt(encode(data), serial)
    def decrypt(data: Array[Byte], serial: String): Array[Byte] = decode(crypt(data, serial))

    def crypt(encoded: Array[Byte], serial: String): Array[Byte] = {
      val iv = generateIV(serial)
      val key = generateKey(serial)
      rabbitCrypt(encoded, iv, key)
    }

    def generateIV(serial: String): Array[Byte] = str2bytes(serial.replace("-", ""))

    def generateKey(serial: String): Array[Byte] = {
      val iv = generateIV(serial)
      val key = iv ++ iv
      key
    }

    def encode(msg: Array[Byte]): Array[Byte] = {
      val encoded = new Array[Byte]((msg.length + 1) / 2)
      for (i <- encoded.indices) {
        encoded(i) = (msg(2 * i) << 4 | msg(2 * i + 1) & 0xF).toByte
      }
      encoded
    }

    def decode(msg: Array[Byte]): Array[Byte] = {
      val decoded = new Array[Byte](msg.length * 2)
      for (i <- msg.indices) {
        decoded(2 * i) = ((msg(i) & 0xF0) >> 4).toByte
        decoded(2 * i + 1) = (msg(i) & 0xF).toByte
      }
      decoded
    }

  }

  object BluePill {

    private val key = Array(0x87, 0x05, 0x89, 0xCD, 0xA8, 0x75, 0x62, 0xEF, 0x38, 0x45, 0xFF, 0xD1, 0x41, 0x37, 0x54, 0xD5).map(_.toByte)

    def crackIV(encfile: String): Array[Byte] = {
      val expected = loadBytes(encfile).slice(0, 4)
      def generateIV(t: Long): Array[Byte] = BigInt(t).toByteArray.reverse

      Stream.iterate(filetime(encfile))(_ - 10000).find(t => {
        val encrypted = encrypt(pngMagicNum, generateIV(t))
        encrypted.sameElements(expected)
      }).map(generateIV).get
    }

    def encrypt(data: Array[Byte], iv: Array[Byte]): Array[Byte] = crypt(encode(data), iv)
    def decrypt(data: Array[Byte], iv: Array[Byte]): Array[Byte] = decode(crypt(data, iv))

    def crypt(encoded: Array[Byte], iv: Array[Byte]): Array[Byte] = rabbitCrypt(encoded, iv, key)

    def encode(msg: Array[Byte]): Array[Byte] = {
      val encoded = new Array[Byte]((msg.length + 1) / 2)
      for (i <- encoded.indices) {
        encoded(i) = (msg(2 * i) & 0xF0 | msg(2 * i + 1) >> 4).toByte
      }
      encoded
    }

    def decode(msg: Array[Byte]): Array[Byte] = {
      val decoded = new Array[Byte](msg.length * 2)
      for (i <- msg.indices) {
        decoded(2 * i) = (msg(i) & 0xF0).toByte
        decoded(2 * i + 1) = (msg(i) << 4).toByte
      }
      decoded
    }

    def filetime(file: String): Long = {
      val FILETIME_EPOCH_DIFF = 11644473600000L
      val FILETIME_ONE_MILLISECOND = 10 * 1000
      val createdMillis = Files.readAttributes(Paths.get(file), classOf[BasicFileAttributes]).creationTime().toMillis
      (createdMillis + FILETIME_EPOCH_DIFF) * FILETIME_ONE_MILLISECOND
    }

  }

  def rabbitCrypt(data: Array[Byte], iv: Array[Byte], key: Array[Byte]): Array[Byte] = {
    val cipher = new Cipher3
    cipher.setupKey(key)
    cipher.setupIV(iv)
    cipher.crypt(data)
  }

  def loadBytes(file: String): Array[Byte] = Files.readAllBytes(Paths.get(file))
  def storeBytes(file: String, bytes: Array[Byte]): Unit = Files.write(Paths.get(file), bytes)

}
