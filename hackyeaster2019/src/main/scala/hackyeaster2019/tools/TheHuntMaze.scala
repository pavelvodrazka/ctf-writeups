package hackyeaster2019.tools

import java.net.URI

import org.apache.http.client.methods.HttpGet
import org.apache.http.cookie.Cookie
import org.apache.http.impl.client.{BasicCookieStore, BasicResponseHandler, HttpClients}
import org.apache.http.impl.cookie.BasicClientCookie
import org.jline.terminal.TerminalBuilder

import scala.collection.JavaConverters._

class TheHuntMaze(val id: String) {

  private val host = URI.create("http://whale.hacking-lab.com:5337/")
  private val cookies = new BasicCookieStore()

  private val http = HttpClients.custom().setDefaultCookieStore(cookies).build()

  private val mapSize = (100, 50)
  private val mapArray = Array.fill(mapSize._2, mapSize._1)('░')

  private var currentPosition = Position(50, 25)
  private var pageContent = ""

  def init(position: Option[Position], session: Option[String], map: Option[String]): Unit = {
    loadPage(host)
    loadPage(host.resolve(id))

    initPosition(position)
    initSession(session)

    initMap(map)
    updateMap(currentPosition, ' ')
  }

  def play(): Unit = {
    val terminal = TerminalBuilder.builder()
      .dumb(true)
      .jna(true)
      .system(true)
      .build()

    terminal.enterRawMode
    val reader = terminal.reader

    while (true) {
      println(s"position:  $currentPosition")
      println(s"alert:     ${alert().getOrElse("")}")
      println(s"navigator: ${navigator().getOrElse("")}")
      println(s"challenge: ${challenge().getOrElse("")}")
      println(s"solved:    ${solved().mkString(", ")}")
      println(s"session:   ${cookies.getCookies.asScala.find(_.getName == "session").map(_.getValue).getOrElse("")}")
      println(map())

      print("> ")
      val command = reader.read.toChar
      command match {
        case 'q' => System.exit(0) // quit
        case 'p' => println(pageContent) // print page
        case 'w' => move(Directions.up)
        case 's' => move(Directions.down)
        case 'a' => move(Directions.left)
        case 'd' => move(Directions.right)
        case _ => println("unknown command")
      }
    }
  }

  private def move(direction: Direction): Unit = {
    val newPosition = currentPosition.move(direction)

    loadPage(host.resolve(s"move/${direction.x}/${direction.y}"))

    alert() match {
      case Some("Ouch! You would hit a wall.") => mapArray(newPosition.y)(newPosition.x) = '█'
      case _ =>
        updateMap(newPosition, if (challenge().isDefined) '¤' else ' ')
        currentPosition = newPosition
    }
  }

  private def loadPage(uri: URI): Unit = {
    pageContent = http.execute(new HttpGet(uri), new BasicResponseHandler())
  }

  private def sessionCookie(session: String): Cookie = {
    val cookie = new BasicClientCookie("session", session)
    cookie.setDomain(host.getHost)
    cookie.setPath("/")
    cookie
  }

  private def initPosition(initPosition: Option[Position]): Unit = {
    initPosition.foreach(pos => currentPosition = pos)
  }

  private def initSession(initSession: Option[String]): Unit = {
    initSession.foreach(id => cookies.addCookie(sessionCookie(id)))
  }

  private def initMap(initMap: Option[String]): Unit = {
    initMap.foreach { stored =>
      for ((row, y) <- stored.lines.zipWithIndex) {
        for ((block, x) <- row.zipWithIndex) {
          updateMap(Position(x, y), block)
        }
      }
    }
  }

  private def updateMap(position: Position, block: Char): Unit = {
    mapArray(position.y)(position.x) = block
  }

  private def navigator(): Option[String] = {
    val pattern = """<p>(.*?)</p>""".r
    pattern.findFirstMatchIn(pageContent).map(_.group(1))
  }

  private def alert(): Option[String] = {
    val pattern = """<div class="alert alert-warning">(.*?)</div>""".r
    pattern.findFirstMatchIn(pageContent).map(_.group(1))
  }

  private def challenge(): Option[String] = {
    val pattern = """(?s)<h3>(.*?)</h3>""".r
    pattern.findFirstMatchIn(pageContent).map(_.group(1))
  }

  private def solved(): List[String] = {
    val pattern = """<li class="tick">(.*?)</li>""".r
    pattern.findAllMatchIn(pageContent).map(_.group(1)).toList
  }

  private def map(): String = {
    mapArray.zipWithIndex.map { case (row, y) =>
      row.zipWithIndex.map { case (block, x) => if (currentPosition == Position(x, y)) '©' else block }.mkString
    }.mkString("\n")
  }

  private case class Position(x: Int, y: Int) {
    def move(direction: Direction): Position = Position(x + direction.x, y + direction.y)

    override def toString: String = s"[$x, $y]"
  }

  private object Directions {
    val up = Direction(0, -1)
    val down = Direction(0, 1)
    val left = Direction(-1, 0)
    val right = Direction(1, 0)
  }

  private case class Direction(x: Int, y: Int)

}
