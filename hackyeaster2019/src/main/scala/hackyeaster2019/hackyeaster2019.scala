import java.io.{ByteArrayInputStream, ByteArrayOutputStream, IOException}
import java.net.{URLDecoder, URLEncoder}
import java.nio.file.{Files, Paths}
import java.security.MessageDigest
import java.util.Base64
import java.util.zip.GZIPInputStream

import org.apache.commons.compress.utils.IOUtils

import scala.collection.JavaConverters._

package object hackyeaster2019 {

  /* -- base64 -- */

  def b64enc(bytes: Array[Byte]): String = Base64.getEncoder.encodeToString(bytes)
  def b64dec(str: String): Array[Byte] = Base64.getDecoder.decode(str)

  /* -- bytes -- */

  def bin2bytes(bin: String): Array[Byte] = BigInt(bin, 2).toByteArray
  def oct2bytes(oct: String): Array[Byte] = BigInt(oct, 8).toByteArray
  def dec2bytes(dec: String): Array[Byte] = BigInt(dec, 10).toByteArray
  def hex2bytes(hex: String): Array[Byte] = BigInt(hex, 16).toByteArray
  def str2bytes(str: String): Array[Byte] = str.getBytes

  /* -- hexadecimal -- */

  def hex(n: Byte): String = "%02x".format(n)
  def hex(n: Array[Byte]): String = n.map(hex).mkString
  def hex(n: Int): String = n.toHexString
  def hex(n: Int, p: Int): String = s"%0${p}x".format(n)
  def hex(n: Long): String = n.toHexString
  def hex(n: Long, p: Int): String = s"%0${p}x".format(n)
  def hex(n: BigInt): String = n.toString(16)
  def hex(n: BigInt, p: Int): String = s"%0${p}x".format(n)

  /* -- octal -- */

  def oct(n: Byte): String = "%03o".format(n)
  def oct(n: Array[Byte]): String = n.map(oct).mkString
  def oct(n: Int): String = n.toOctalString
  def oct(n: Int, p: Int): String = s"%0${p}o".format(n)
  def oct(n: Long): String = n.toOctalString
  def oct(n: Long, p: Int): String = s"%0${p}o".format(n)
  def oct(n: BigInt): String = n.toString(8)
  def oct(n: BigInt, p: Int): String = s"%0${p}o".format(n)

  /* -- binary -- */

  def bin(n: Byte): String = bin(n.toInt & 0xff, 8)
  def bin(n: Array[Byte]): String = n.map(bin).mkString
  def bin(n: Int): String = n.toBinaryString
  def bin(n: Int, p: Int): String = s"%${p}s".format(bin(n)).replace(' ', '0')
  def bin(n: Long): String = n.toBinaryString
  def bin(n: Long, p: Int): String = s"%${p}s".format(bin(n)).replace(' ', '0')
  def bin(n: BigInt): String = n.toString(2)
  def bin(n: BigInt, p: Int): String = s"%${p}s".format(bin(n)).replace(' ', '0')

  /* -- ascii -- */

  def ascii(n: Int): Char = n.toChar
  def ascii(n: Byte): Char = (n.toInt & 0xff).toChar
  def ascii(n: Array[Byte]): String = n.map(ascii).mkString

  /* -- hashes -- */

  private val md5digest = MessageDigest.getInstance("MD5")
  def md5(text: String): Array[Byte] = md5(text.getBytes)
  def md5(bytes: Array[Byte]): Array[Byte] = md5digest.digest(bytes)
  def md5hex(text: String): String = hex(md5(text))
  def md5hex(bytes: Array[Byte]): String = hex(md5(bytes))

  private val sha1digest = MessageDigest.getInstance("SHA1")
  def sha1(text: String): Array[Byte] = sha1(text.getBytes)
  def sha1(bytes: Array[Byte]): Array[Byte] = sha1digest.digest(bytes)
  def sha1hex(text: String): String = hex(sha1(text))
  def sha1hex(bytes: Array[Byte]): String = hex(sha1(bytes))

  private val sha256digest = MessageDigest.getInstance("SHA-256")
  def sha256(text: String): Array[Byte] = sha256(text.getBytes)
  def sha256(bytes: Array[Byte]): Array[Byte] = sha256digest.digest(bytes)
  def sha256hex(text: String): String = hex(sha256(text))
  def sha256hex(bytes: Array[Byte]): String = hex(sha256(bytes))

  /* -- files -- */

  def loadFromFile(path: String): Array[Byte] = Files.readAllBytes(Paths.get(path))
  def saveToFile(path: String, content: Array[Byte]): Unit = Files.write(Paths.get(path), content)
  def saveToFile(path: String, lines: Iterable[String]): Unit = Files.write(Paths.get(path), lines.asJava)

  /* -- url -- */

  def urlencode(text: String): String = URLEncoder.encode(text, "UTF-8").replaceAll("\\+", "%20")
  def urldecode(text: String): String = URLDecoder.decode(text.replaceAll("%20", "\\+"), "UTF-8")

  /* -- compression -- */

  def gunzip(bytes: Array[Byte]): Array[Byte] = {
    val out = new ByteArrayOutputStream
    try
      IOUtils.copy(new GZIPInputStream(new ByteArrayInputStream(bytes)), out)
    catch {
      case e: IOException => throw new RuntimeException(e)
    }
    out.toByteArray
  }

  /* -- math -- */

  def gcd(a: Int, b: Int): Int = if (b == 0) a.abs else gcd(b, a % b)
  def gcd(a: BigInt, b: BigInt): BigInt = a.gcd(b)

  def lcm(a: Int, b: Int): Int = (a * b).abs / gcd(a, b)
  def lcm(a: BigInt, b: BigInt): BigInt = (a * b).abs / gcd(a, b)

}
