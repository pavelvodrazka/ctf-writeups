package hackyeaster2019

import java.net.URI

import org.apache.http.client.methods.HttpGet
import org.apache.http.client.utils.URIBuilder
import org.apache.http.cookie.Cookie
import org.apache.http.impl.client.{BasicCookieStore, BasicResponseHandler, HttpClients}
import org.apache.http.impl.cookie.BasicClientCookie

import spray.json._

import scala.collection.JavaConverters._

object Egg21CLC32 extends App {

  object InputJsonProtocol extends DefaultJsonProtocol {
    implicit val outFormat: RootJsonFormat[Out] = jsonFormat5(Out)
    implicit val inFormat: RootJsonFormat[In] = jsonFormat6(In)
    implicit val dataFormat: RootJsonFormat[Data] = jsonFormat1(Data)
    implicit val responseFormat: RootJsonFormat[Response] = jsonFormat1(Response)
  }

  import InputJsonProtocol._

  case class Response(data: Data)
  case class Data(In: In)
  case class In(see: String, hear: String, taste: String, smell: String, touch: String, Out: Out)
  case class Out(see: String, hear: String, taste: String, smell: String, touch: String)

  val host = URI.create("http://whale.hacking-lab.com:5337/")
  val session = "z.mmp/QD5A74ECRyI7HDKvQXi+gXOCQnSdlnmSwqnb6DM/VK7gA3PZcshSqwQPNDD61ZQwwRBB1v3a683a4Fizf+jYBr1kuwNl9P0Z2sBbuIbt50JFi8j2b1St8U4kJMX5SDlOt/Wbb8znEjjMXWr55xJ3VZiULuhOgLGGNsJffiQLJCMv3t9VyAZK9bslPYEgJZq33ubbdwGx0yNTeE7vDqI+kiq6U5VmI6J6c6zME6l8qgClvv9zL/dBlEFLcsY7+8c/XI6q3n997wRATRc0cZPktSuYL8Yv+c9DZivC2NlOhitaJmhRCFDgw3L8iZvPvO9te+MHdBGeE54vLJUdkCSur7YCDd2yDIDM8p6sDs56vg33pOHJ1O19ZGVyYnRc9VsEhrkndWC5UW/O+a2ypFHzQaCx36zDKuKd7POtyPVukBCT+jLS/2ajTb3MbwyC8ScaSrB+UbPviJ5v7T6jeRwaX8AYRjpGpyItsOZwy1wQ8hW9awpyhG3d05qCbxcOduTiOsCE1NnEc3SD36BpXVz2TTVH9sxzIZdGxZ94RWzIz41HvanVRLbnd8cxCgYOzxrWr3GuPs6Mh6B8yC9w953D6qx1M6/Y859eYGVCqwk7odlPMlkhpVfrhqSaepqdGZN4rQWiVnI6g5VY3hxA9qJJJLilRHcQDPCIVcu9YE6LSZv34ixMvj1tvVCjNtr8j3Rn9A0xB0QNSMiwJp5yg75Q+kRW7ZmL2cVTdtndk1RYiVhtPMgcZpBGKmcaFzXlPmmNiz7U78ljEzKiOSqQcZRG2vamyrsQOLfQ4NmZiBq5BYHzy7qAeN0/vHldiakohe7w4XCnINjRupSxOnmbyHlbNjFmCqvEJXsdg9FeLCCYe6zY6s3g1j0ayIeh2e+ELaqLAPASx1AULP+XmLKBLRhGvPGljykhujZGS6Igwkgo+8Nex0IBMleWTckI.0wrhk8mL964ocsGC8zv3cQ==.8dTdd+q64r9eJXDBKam+0g=="

  val cookies = new BasicCookieStore()
  cookies.addCookie(sessionCookie(session))

  val http = HttpClients.custom().setDefaultCookieStore(cookies).build()

  val query =
    """
      |{
      |  In {
      |    see
      |    hear
      |    taste
      |    smell
      |    touch
      |    Out {
      |      see
      |      hear
      |      taste
      |      smell
      |      touch
      |    }
      |  }
      |}
    """.stripMargin

  loadPage(resetURI())

  var word = ""
  while (word.length < 4) {
    val response = loadPage(liveURI(query)).parseJson.convertTo[Response]
    println(response.data)

    val next = findNextLetter(response.data)
    next.foreach { letter =>
      word += letter
      println(s"   found: $letter -> $word")
    }
  }

  println(s"   session: ${getSession()}")

  def findNextLetter(data: Data): Option[String] = {
    val in = data.In
    val out = in.Out

    def findNextLetter(letters: List[String]): Option[String] =
      letters.groupBy(identity).mapValues(_.size).find(_._2 >= 3).map(_._1)

    val inLetter = findNextLetter(lettersOf(in))
    val outLetter = findNextLetter(lettersOf(out))

    inLetter.orElse(outLetter)
  }

  def lettersOf(in: In) = List(in.see, in.hear, in.taste, in.smell, in.touch)
  def lettersOf(out: Out) = List(out.see, out.hear, out.taste, out.smell, out.touch)

  def resetURI(): URI = new URIBuilder(host)
    .addParameter("new", "live")
    .build()

  def liveURI(query: String): URI = new URIBuilder(host)
    .setPath("/live/a/life")
    .addParameter("query", query)
    .build()

  def loadPage(uri: URI): String = {
    http.execute(new HttpGet(uri), new BasicResponseHandler())
  }

  def getSession(): String = cookies.getCookies.asScala.find(_.getName == "session").map(_.getValue).getOrElse("")

  def sessionCookie(session: String): Cookie = {
    val cookie = new BasicClientCookie("session", session)
    cookie.setDomain(host.getHost)
    cookie.setPath("/")
    cookie
  }

}
