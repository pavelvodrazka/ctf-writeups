package hackyeaster2019

import org.apache.http.client.entity.UrlEncodedFormEntity
import org.apache.http.client.methods.{HttpGet, HttpPost}
import org.apache.http.impl.client.HttpClients
import org.apache.http.message.BasicNameValuePair
import org.apache.http.util.EntityUtils

import scala.collection.JavaConverters._

object Egg11 extends App {

  case class Round(page: String, images: Seq[Image])
  case class Image(id: Int, hash: String)

  val host = "http://whale.hacking-lab.com:1111"

  val http = HttpClients.createDefault()
  try {
    for (round <- 1 to 10) {
      println(s"Round $round...")
      solveRound(loadRound())
    }
    println(loadRound(false).page)
  } finally {
    http.close()
  }

  def solveRound(round: Round): Unit = {
    round.images
      .groupBy(_.hash)
      .map { case (_, pair) => (pair(0).id, pair(1).id) }
      .foreach(submitPair)
  }

  def submitPair(ids: (Int, Int)): Unit = {
    def param(name: String, value: Any) = new BasicNameValuePair(name, value.toString)
    val body = Seq(param("first", ids._1), param("second", ids._2))

    val request = new HttpPost(s"$host/solve")
    request.setEntity(new UrlEncodedFormEntity(body.asJava))

    http.execute(request).close()
  }

  def loadRound(loadImages: Boolean = true): Round = {
    val request = new HttpGet(host)
    val response = http.execute(request)

    val content = EntityUtils.toString(response.getEntity)
    val images = if (loadImages) (1 to 98).map(loadImage) else Seq.empty

    Round(content, images)
  }

  def loadImage(id: Int): Image = {
    val request = new HttpGet(s"$host/pic/$id")
    val response = http.execute(request)

    val bytes = EntityUtils.toByteArray(response.getEntity)
    val hash = md5hex(bytes)

    Image(id, hash)
  }

}
