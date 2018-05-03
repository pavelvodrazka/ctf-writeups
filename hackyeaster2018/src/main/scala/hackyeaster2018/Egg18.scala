package hackyeaster2018

object Egg18 {

  def main(args: Array[String]): Unit = {
    assert(username("BUNNYADMIN_12128290") == "OHAALNQZVA_12128290")

    val passwd = Stream.from(0).find(n => password(n.toString) == 9191).get
    println(s"password is: $passwd")


  }

  private def username(name: String): String = {
    var Str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" * 2
    var Str2 = name
    var Str3 = ":"
    var A = Int.MinValue

    for (p <- 0 until Str2.length) {
      A = Str1.indexOf(Str2.charAt(p))
      if (A >= 0) {
        Str3 = Str3 + Str1.charAt(A + 13) // ROT13
      } else {
        Str3 = Str3 + Str2.charAt(p)
      }
    }

    Str3.substring(1, 1 + Str2.length)
  }

  private def password(passwd: String): Int = {
    var C = 1
    var N = 8956d
    var M = expr(passwd)
    var E = 0

    while (N > 0 || M > 0) {
      N = int(N) / 2
      M = int(M) / 2
      E = E + C * xor(fPart(N), fPart(M))
      C = C * 2
    }

    E
  }

  private def expr(str: String): Double = str.toDouble
  private def int(n: Double): Double = n.floor
  private def fPart(n: Double): Double = n - n.toInt
  private def xor(a: Double, b: Double): Int = if (a == b) 0 else 1

}
