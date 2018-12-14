import java.util.Base64

package object hackvent2018 {

  /* -- base64 -- */

  def b64enc(bytes: Array[Byte]): String = Base64.getEncoder.encodeToString(bytes)
  def b64dec(str: String): Array[Byte] = Base64.getDecoder.decode(str)

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

  /* -- math -- */

  def gcd(a: Int, b: Int): Int = if (b == 0) a.abs else gcd(b, a % b)
  def gcd(a: BigInt, b: BigInt): BigInt = a.gcd(b)

  def lcm(a: Int, b: Int): Int = (a * b).abs / gcd(a, b)
  def lcm(a: BigInt, b: BigInt): BigInt = (a * b).abs / gcd(a, b)

}
