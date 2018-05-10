package hackyeaster2018

import java.io.PrintWriter
import java.net.URI

import org.apache.http.client.config.{CookieSpecs, RequestConfig}
import org.apache.http.client.methods.{HttpGet, HttpPost}
import org.apache.http.client.protocol.HttpClientContext
import org.apache.http.cookie.Cookie
import org.apache.http.entity.{ContentType, StringEntity}
import org.apache.http.impl.client.{BasicCookieStore, BasicResponseHandler, HttpClients}
import org.apache.http.impl.cookie.BasicClientCookie
import spray.json._

import scala.collection.JavaConverters._
import scala.io.Source

object Egg23 {

  object InputJsonProtocol extends DefaultJsonProtocol {
    implicit val visitorFormat = jsonFormat9(Visitor)
    implicit val assignmentFormat = jsonFormat2(Assignment)
  }

  import InputJsonProtocol._

  case class Visitor(sp00n: Int, n4m3: String, t41l: Int, w31ght: Int, c0l0r: String, ag3: Int, l3ngth: Int, g00d: Boolean, g3nd3r: String)
  case class Assignment(attributes: Array[String], data: Array[Array[JsValue]])

  private val http = HttpClients.custom()
    .setDefaultRequestConfig(RequestConfig.custom().setCookieSpec(CookieSpecs.STANDARD).build())
    .build()

  private val gatewayUri = URI.create("http://whale.hacking-lab.com:2222")
  private val trainUri = gatewayUri.resolve("/train")
  private val assignmentUri = gatewayUri.resolve("/gate")
  private val predictionUri = gatewayUri.resolve("/predict")
  private val rewardUri = gatewayUri.resolve("/reward")

  def main(args: Array[String]): Unit = {
    //println("downloading train data...")
    //downloadTrainData(10000, "/tmp/train_data.txt")

    println("downloading assignment data...")
    val sessionid = downloadAssignment("/tmp/assignment.txt")
    val assignment = loadAssignment("/tmp/assignment.txt")

    println("calculating predictions...")
    val prediction = predictAssignment(assignment)

    println("submitting predictions...")
    val result = submitPrediction(prediction, sessionid)
    if (!result.contains("reward for this shift at /reward")) {
      throw new RuntimeException(result)
    }

    println("getting reward...")
    val reward = getReward(sessionid)

    println("saving reward...")
    saveReward(reward, "hackyeaster2018/challenges/egg23/files/egg.png")
  }

  private def predictAssignment(assignment: Assignment): Array[Int] = {
    val order = assignment.attributes.map(b => ascii(b64Decode(b))).zipWithIndex.toMap
    assignment.data.map { d =>
      val sp00n = d(order("sp00n")).convertTo[Int]
      val t41l = d(order("t41l")).convertTo[Int]
      val w31ght = d(order("w31ght")).convertTo[Int]
      val c0l0r = d(order("c0l0r")).convertTo[String]

      val predictions = List(predictBySp00n(sp00n), predictByT41l(t41l), predictByW31ght(w31ght), predictByC0l0r(c0l0r)).flatten
      if (predictions.head) 1 else 0
    }
  }

  private def predictBySp00n(sp00n: Int): Option[Boolean] =
    sp00n match {
      case i if i >= 12 => Some(false)
      case i if i <= 9 => Some(true)
      case _ => None
    }

  private def predictByT41l(t41l: Int): Option[Boolean] =
    t41l match {
      case i if i <= 9 => Some(true)
      case _ => None
    }

  private def predictByW31ght(w31ght: Int): Option[Boolean] =
    w31ght match {
      case i if i >= 3 => Some(true)
      case 2 => Some(false)
      case _ => None
    }

  private def predictByC0l0r(c0l0r: String): Option[Boolean] =
    c0l0r match {
      case "blue" | "green" | "grey" | "purple" | "white" => Some(true)
      case "black" => Some(false)
      case _ => None
    }

  private def submitPrediction(prediction: Array[Int], sessionid: String): String = {
    val request = new HttpPost(predictionUri)
    request.setEntity(new StringEntity(prediction.mkString("[", ",", "]"), ContentType.APPLICATION_JSON))
    val context = HttpClientContext.create()
    context.setCookieStore(new BasicCookieStore())
    context.getCookieStore.addCookie(sessionCookie(sessionid))
    http.execute(request, new BasicResponseHandler(), context)
  }

  private def getReward(sessionid: String): String = {
    val request = new HttpGet(rewardUri)
    val context = HttpClientContext.create()
    context.setCookieStore(new BasicCookieStore())
    context.getCookieStore.addCookie(sessionCookie(sessionid))
    val response = http.execute(request, new BasicResponseHandler(), context)
    val reward = response.lines.find(_.contains("img")).get
    reward.substring(reward.indexOf('"') + 1, reward.lastIndexOf('"'))
  }

  private def saveReward(reward: String, path: String): Unit = {
    val encoded = reward.substring(reward.indexOf(',') + 1)
    val decoded = b64Decode(encoded)
    saveToFile(path, decoded)
  }

  private def downloadAssignment(dest: String): String = {
    val writer = new PrintWriter(dest)
    try {
      val request = new HttpGet(assignmentUri)
      val context = HttpClientContext.create()
      val assignment = http.execute(request, new BasicResponseHandler(), context)
      writer.println(assignment)
      context.getCookieStore.getCookies.asScala.find(_.getName == "session_id").map(_.getValue).get
    } finally {
      writer.close()
    }
  }

  private def loadAssignment(path: String): Assignment =
    Source.fromFile(path).mkString.parseJson.convertTo[Assignment]

  private def downloadTrainData(size: Int, dest: String): Unit = {
    val writer = new PrintWriter(dest)
    try {
      val request = new HttpGet(trainUri)
      for (i <- 0 until size) {
        val data = http.execute(request, new BasicResponseHandler())
        writer.println(data)
      }
    } finally {
      writer.close()
    }
  }

  private def loadTrainData(path: String): Seq[Visitor] =
    Source.fromFile(path).getLines().map(_.parseJson.convertTo[Visitor]).toSeq

  private def sessionCookie(sessionid: String): Cookie = {
    val cookie = new BasicClientCookie("session_id", sessionid)
    cookie.setDomain(gatewayUri.getHost)
    cookie.setPath("/")
    cookie
  }

}
