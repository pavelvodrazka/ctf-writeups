import java.io._
import java.net._
import java.nio.file.{Files, Paths}
import java.security.MessageDigest
import java.util.Base64
import java.util.zip.GZIPInputStream

import org.apache.commons.compress.utils.IOUtils

package object hackvent2017 {

  private val md5digest = MessageDigest.getInstance("MD5")
  private val sha1digest = MessageDigest.getInstance("SHA1")
  private val sha256digest = MessageDigest.getInstance("SHA-256")

  /* -- base 64 -- */

  def b64Encode(bytes: Array[Byte]): String = Base64.getEncoder.encodeToString(bytes)
  def b64Decode(str: String): Array[Byte] = Base64.getDecoder.decode(str)

  /* -- bin / oct / dec / hex -- */

  def bin(n: Byte): String = bin(n.toInt & 0xff)
  def bin(n: Int): String = bin(n, 8)
  def bin(n: Int, p: Int): String = s"%${p}s".format(Integer.toBinaryString(n)).replace(' ', '0')

  def hex(n: Byte): String = hex(n.toInt & 0xff)
  def hex(n: Array[Byte]): String = n.map(hex).mkString
  def hex(n: Int): String = hex(n, 2)
  def hex(n: Int, p: Int): String = s"%${p}s".format(Integer.toHexString(n)).replace(' ', '0')

  def dec(n: Byte): String = dec(n.toInt & 0xff)
  def dec(n: Int): String = dec(n, 3)
  def dec(n: Int, p: Int): String = s"%${p}s".format(Integer.toString(n))

  def oct(n: Byte): String = oct(n.toInt & 0xff)
  def oct(n: Int): String = oct(n, 3)
  def oct(n: Int, p: Int): String = s"%${p}s".format(Integer.toOctalString(n)).replace(' ', '0')

  /* -- files -- */

  def saveToFile(path: String, content: Array[Byte]): Unit = Files.write(Paths.get(path), content)

  /* -- hashes -- */

  def md5(text: String): Array[Byte] = md5digest.digest(text.getBytes)
  def md5hex(text: String): String = hex(md5(text))

  def sha1(text: String): Array[Byte] = sha1digest.digest(text.getBytes)
  def sha1hex(text: String): String = hex(sha1(text))

  def sha256(text: String): Array[Byte] = sha256digest.digest(text.getBytes)
  def sha256hex(text: String): String = hex(sha1(text))

  /* -- ascii -- */

  def ascii(n: Int): Char = n.toChar
  def ascii(n: Byte): Char = (n.toInt & 0xff).toChar
  def ascii(n: Array[Byte]): String = n.map(ascii).mkString

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

  def gcd(a: Int, b: Int): Int = if (b==0) a.abs else gcd(b, a % b)
  def lcm(a: Int, b: Int): Int = (a * b).abs / gcd(a,b)

  def gcd(a: BigInt, b: BigInt): BigInt = if (b==0) a.abs else gcd(b, a.mod(b))
  def lcm(a: BigInt, b: BigInt): BigInt = (a * b).abs / gcd(a,b)

  /* -- time -- */

  def time(fun: () => Any): Long = {
    val started = System.currentTimeMillis
    fun()
    val ended = System.currentTimeMillis
    (ended - started) / 1000
  }

}
