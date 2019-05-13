# 11 - Memeory 2.0

We improved Memeory 1.0 and added an insane serverside component. So, no more CSS-tricks. **Muahahaha**.

Flagbounty for everyone who can solve 10 successive rounds. Time per round is 30 seconds and only 3 missclicks are allowed.

Good game.

![meme.png](files/meme.png "meme.png")

[Memeory2](http://whale.hacking-lab.com:1111/)

### Description

It was an enhanced version of [Memeory](../../../hackyeaster2018/challenges/egg04/README.md) from last year. This time a server-side component shuffled the images for each round so that the same image had different URL each round.

### Solution

Since I could not rely on image URLs I wrote a program which fetched and grouped images by their MD5 fingerprints. There was one tricky part however. It took me a while to realize that JS client used different image ids than the server (0-based vs 1-based indexing). Grrrr...  

```scala
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
```

The complete source code can be found [here](../../src/main/scala/hackyeaster2019/Egg11.scala).

Password: `1-m3m3-4-d4y-k33p5-7h3-d0c70r-4w4y`

### Egg

![egg.png](files/egg.png "egg.png")
