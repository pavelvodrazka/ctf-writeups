package hackyeaster2019

import hackyeaster2019.tools.TheHuntMaze

object Egg21 extends App {

  val maze = new TheHuntMaze("1804161a0dabfdcd26f7370136e0f766")
  maze.init(None, None, None)
  maze.play()

}
