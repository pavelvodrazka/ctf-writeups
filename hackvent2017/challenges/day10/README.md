# Day 10: Just play the game

*Haven't you ever been bored at school?*

Santa is in trouble. He's elves are busy playing TicTacToe. Beat them and help Sata to save christmas!

`nc challenges.hackvent.hacking-lab.com 1037`

### Solution

I really enjoyed this one! After beating the game manually I decided to write a Scala program (source code can be found [here](../../src/main/scala/hackvent2017/Day10.scala)) which could beat the AI on the other side.

```scala
def main(args: Array[String]): Unit = {
  val nc = NetCat.open("challenges.hackvent.hacking-lab.com", 1037)
  try {
    // start game
    nc.read
    nc.writeln("")

    // play game
    var finished = false
    while (!finished) {
      val msg = nc.read
      if (msg.contains("HV17")) {
        println(msg.split('\n').find(_.startsWith("HV17")).get)
        finished = true
      } else if (msg.contains("Congratulations you won!")) {
        println(msg.split('\n').find(_.startsWith("Congratulations")).get)
        nc.writeln("")
      } else if (msg.contains("There is no winner")) {
        println("There is no winner")
        nc.writeln("")
      } else if (msg.endsWith("Field: ")) {
        val field = parseField(msg)
        val move = field match {
          case "*********" => 1
          case "X***O****" => 9
          case "X*O*O***X" => 7
          case "X*O*O*XOX" => 4
          case "XOO*O*X*X" => 4
          case "XO**O***X" => 8
          case "XO*******" => 7
          case "XO**O*OXX" => 3
          case "XOX*OOOXX" => 4
          case "XO*O**X**" => 5
          case "XOO*O**XX" => 7
          case "XO*OX*X*O" => 3
          case "XOXOO*OXX" => 6
          case "XOO***X**" => 4
          case "XOOOX*X**" => 9
          case _ => throw new IllegalArgumentException("Unexpected field: " + field)
        }
        nc.writeln(move.toString)
      }
    }
  } finally {
    nc.close
  }
}

private def parseField(field: String): String = {
  val lines = field.split('\n')
  (11 to 5 by -3).map(i => lines(lines.length - i).replaceAll("[ |]", "")).mkString
}
```

You will get the flag as a reward for beating the game.

```
HV17-y0ue-kn0w-7h4t-g4me-sure
```