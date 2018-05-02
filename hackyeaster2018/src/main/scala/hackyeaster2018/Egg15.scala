package hackyeaster2018

import scala.io.Source

object Egg15 {

  def main(args: Array[String]): Unit = {
    val deck = Source.fromFile("hackyeaster2018/challenges/egg15/files/deck").getLines.toList
    val converted = deck.map(convert).grouped(13).map(_.mkString(" ")).toList
    saveToFile("hackyeaster2018/challenges/egg15/files/deck-converted", converted)
  }

  private def convert(card: String): String = {
    val suit = card.substring(0, 1).toUpperCase
    val number = card.substring(1).toUpperCase

    suit match {
      case "J" =>
        val num = if (number == "R") "A" else "B"
        s"*$num"
      case _ =>
        val num = if (number == "A") "1" else number
        s"$num$suit"
    }
  }

}
