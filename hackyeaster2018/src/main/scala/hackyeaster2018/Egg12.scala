package hackyeaster2018

object Egg12 {

  def main(args: Array[String]): Unit = {
    var hash = "genesis"
    var count = 100000

    while (count > 0) {
      hash = sha1hex(hash + String.valueOf(count))
      count -= 1
    }

    println(s"https://hackyeaster.hacking-lab.com/hackyeaster/images/eggs/$hash.png")
  }

}
