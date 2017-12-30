package hackvent2017

import scala.io.Source

object Day15 {

  def main(args: Array[String]): Unit = {
    val accounts = Source.fromFile("hackvent2017/challenges/day15/files/accounts.csv").getLines.drop(1).map(csvToAccount).toList
    val thumpers = accounts.filter(_.prename == "Thumper").filter(_.state == "active")
    val flagPattern = "(HV17(-[\\w]{4}){5})".r

    for (account <- thumpers) {
      val link = s"http://challenges.hackvent.hacking-lab.com:3958/gallery/${hash(account)}"
      val html = Source.fromURL(link).mkString
      val flag = flagPattern.findFirstIn(html)
      if (flag.isDefined) {
        println(s"gallery: ${link}")
        println(s"flag: ${flag.get}")
      }
    }
  }

  private def hash(account: Account): String = hash(account.email)
  private def hash(text: String): String = b64Encode(sha256(text)).replaceAll("[\\+=/]", "")

  case class Account(id: Int, prename: String, name: String, address: String, zip: String, city: String, email: String, crmId: String, memberType: String, pictureCount: Int, galleryCount: Int, mbUsed: Int, logCorrelationId: String, advertisingId: String, state: String)
  private def csvToAccount(line: String): Account = {
    val cells = line.split(',')
    Account(cells(0).toInt, cells(1), cells(2), cells(3), cells(4), cells(5), cells(6), cells(7), cells(8), cells(9).toInt, cells(10).toInt, cells(11).toInt, cells(12), cells(13), cells(14))
  }

}
