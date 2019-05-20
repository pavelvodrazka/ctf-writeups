package hackyeaster2019

object Egg18 extends App {

  val alphabet = "01345HLXcdfr"

  val candidates = for (
    (p11, p21) <- Seq(('5', 'c'), ('f', 'L'), ('r', 'X'));
    p12 <- alphabet;
    p18 <- alphabet;
    p23 <- Seq('3', 'd')
  ) yield s"Th3P4r4d0X0${p11}${p12}H01${p12}${p23}${p18}54${p21}1${p23}"

  val password = candidates.find { passwd =>
    val checksum = passwd.substring(4).foldLeft((0, 0)) { (a, c) => (a._1 + c, a._2 ^ c) }
    checksum == (1352, 44)
  }.orNull

  println(password)

}
