package hackyeaster2019

import hackyeaster2019.tools.TheHuntMaze

object Egg22 extends App {

  val maze = new TheHuntMaze("7fde33818c41a1089088aa35b301afd9")
  maze.init(None, None, None)
  maze.play()

}
