package hackyeaster2018

object Egg10 {

  def main(args: Array[String]): Unit = {
    val egg = hexbytes("7034353577307264355f3472335f6330306c")
    val signs = List(
      "7034353577307264355f052d066b15035433",
      "70343535773072105d6c6b05032d0f546f4c",
      "7034353577307264355f3406033b5749114c"
    ).map(hexbytes)

    val xored = signs.map(xor(_, egg))
    print(xored.map(ascii).mkString("\n"))
  }

  private def xor(x: Array[Byte], y: Array[Byte]): Array[Byte] = {
    assert(x.length == y.length)
    x.indices.map(i => (x(i) ^ y(i)).toByte).toArray
  }

}
