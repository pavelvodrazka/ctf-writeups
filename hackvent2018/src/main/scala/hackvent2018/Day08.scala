package hackvent2018

import java.awt.Color
import java.awt.image.BufferedImage
import java.nio.file.{Path, Paths}
import java.util

import javax.imageio.ImageIO
import org.apache.http.Consts
import org.apache.http.client.entity.UrlEncodedFormEntity
import org.apache.http.client.methods.HttpPost
import org.apache.http.impl.client.{BasicResponseHandler, HttpClients}
import org.apache.http.message.BasicNameValuePair
import spray.json._

object Day08 extends App {

  object InputJsonProtocol extends DefaultJsonProtocol {
    implicit val responseFormat: RootJsonFormat[Response] = jsonFormat3(Response)
  }

  import InputJsonProtocol._

  type Code = Array[Array[Boolean]]

  case class Response(results: Map[String, String], date: Long, time: String)

  val image = loadImage(Paths.get("hackvent2018/challenges/day08/files/4dv3ntSn4il-crop.png"))
  assert(image.getWidth == image.getHeight)

  val qrCodeSize = 25
  val qrPixelSize = image.getWidth / qrCodeSize
  val qrPixelCenterOffset = qrPixelSize / 2

  val encoded = readCode(image)
  val decoded = decodeCode(encoded)

  val solution = decoded.find(c => (c(0).slice(0, 7) ++ c(0).slice(qrCodeSize - 7, qrCodeSize)).forall(_ == true))
  solution.foreach(displayCode)

  def readCode(image: BufferedImage): Code = {
    val pixels = Array.ofDim[Boolean](qrCodeSize, qrCodeSize)
    for (y <- 0 until qrCodeSize) {
      for (x <- 0 until qrCodeSize) {
        val posx = qrPixelCenterOffset + x * qrPixelSize
        val posy = qrPixelCenterOffset + y * qrPixelSize
        val rgb = image.getRGB(posx, posy)
        pixels(y)(x) = rgb == Color.BLACK.getRGB
      }
    }
    pixels
  }

  def decodeCode(code: Code): Seq[Code] = {
    val http = HttpClients.createDefault()
    try {
      val ciphertext = code.map(line => line.map(if (_) '1' else '0').mkString).mkString

      val form = new util.ArrayList[BasicNameValuePair]
      form.add(new BasicNameValuePair("tool", "spiral-cipher"))
      form.add(new BasicNameValuePair("ciphertext", ciphertext))
      form.add(new BasicNameValuePair("writing_mode", "outward"))
      form.add(new BasicNameValuePair("punctuation", "1"))

      val req = new HttpPost("https://www.dcode.fr/api/")
      req.setEntity(new UrlEncodedFormEntity(form, Consts.UTF_8))

      val resp = http.execute(req, new BasicResponseHandler()).parseJson.convertTo[Response]
      val plaintexts = resp.results.values.toList

      plaintexts.map(_.grouped(qrCodeSize).map(_.map(_ == '1').toArray).toArray)
    } finally {
      http.close()
    }
  }

  def displayCode(code: Code): Unit = {
    println(code.map(_.map(if (_) "██" else "  ").mkString).mkString("\n"))
  }

  def loadImage(path: Path): BufferedImage = ImageIO.read(path.toFile)

}
