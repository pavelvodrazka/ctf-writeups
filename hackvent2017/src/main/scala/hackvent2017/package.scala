import java.security.MessageDigest
import java.util.Base64

import org.apache.commons.compress.utils.IOUtils
import java.io._
import java.net.{InetAddress, Socket}
import java.nio.file.{Files, Paths}
import java.util.zip.GZIPInputStream

import scala.collection.mutable.ArrayBuffer

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

  /* -- netcat -- */

  object NetCat {
    def open(host: String, port: Int): NetCat = new NetCat(host, port)
  }

  class NetCat(host: String, port: Int) {

    private val socket = new Socket(InetAddress.getByName(host), port)

    private val in = new BufferedReader(new InputStreamReader(socket.getInputStream))
    private val out = new PrintStream(socket.getOutputStream, true)

    private val buffer = Array.ofDim[Char](1024)

    private var trace = false

    def trace(value: Boolean): Unit = trace = value

    def read: String = {
      val data = ArrayBuffer.empty[Char]
      do {
        val length = in.read(buffer)
        data ++= buffer.slice(0, length)
      } while (in.ready())

      val msg = data.mkString
      if (trace) print(msg)
      msg
    }

    def writeln(msg: String): Unit = {
      out.println(msg)
      if (trace) println(msg)
    }

    def write(msg: String): Unit = {
      out.print(msg)
      if (trace) print(msg)
    }

    def write(msg: Array[Byte]): Unit = {
      out.print(msg)
      if (trace) print(msg)
    }

    def close(): Unit = socket.close()

  }

  /* -- time -- */

  def time(fun: () => Any): Long = {
    val started = System.currentTimeMillis
    fun()
    val ended = System.currentTimeMillis
    (ended - started) / 1000
  }

}
