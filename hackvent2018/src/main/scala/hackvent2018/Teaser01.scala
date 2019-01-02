package hackvent2018

object Teaser01 extends App {

  val fuses = Array(0xC0FFFFFFFFFFFFFFL, 0x0F0F0F0F0F0F0F0FL)

  val key = assembleKey()
  println("key: " + hex(key))

  def assembleKey(): Array[Byte] = {
    val key: Array[Byte] = Array.ofDim(16)

    var r7 = 0L
    var r6 = 0L

    for (idx <- 0 until 16 by 2) {
      r7 = (7 - idx / 2) << 3

      r6 = fuses(0) >> (r7 & 0x7F)
      r7 = fuses(1) >> (r7 & 0x7F)

      key(idx) = (r6 & 0xFF).toByte
      key(idx + 1) = (r7 & 0xFF).toByte
    }

    key
  }

}
