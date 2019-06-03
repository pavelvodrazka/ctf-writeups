package hackyeaster2019

import hackyeaster2019.tools.TheHuntMaze

object Egg27 extends App {

  val maze = new TheHuntMaze("bf42fa858de6db17c6daa54c4d912230")
  maze.init(None, None, None)
  maze.play()

}
