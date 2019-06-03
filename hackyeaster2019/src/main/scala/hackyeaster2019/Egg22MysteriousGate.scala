package hackyeaster2019

object Egg22MysteriousGate extends App {

  def h(s: String): Int = s.foldLeft(0)((a, b) => a * 31 + b)

  def bruteforce(): Option[Array[Int]] = {
    val range = -9 to 9

    for (n0 <- range; n1 <- range; n2 <- range; n3 <- range; n4 <- range; n5 <- range; n6 <- range; n7 <- range) {
      val s = s"$n0$n1$n2$n3$n4$n5$n6$n7"
      if (h(s) == -502491864) {
        return Some(Array(n0, n1, n2, n3, n4, n5, n6, n7))
      }
    }

    None
  }

  bruteforce().foreach(pins => println(s"pins: ${pins.mkString(", ")}"))

}
