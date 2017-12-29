package hackvent2017

import scala.io.Source

object Day02 {

  def main(args: Array[String]): Unit = {
    var s = Source.fromFile("hackvent2017/challenges/day02/files/Wishlist.txt").mkString
    while (!s.startsWith("HV17")) {
      s = ascii(b64Decode(s.replaceAll("\n", "")))
    }
    println(s)
  }

}
