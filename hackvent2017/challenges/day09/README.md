# Day 09: JSONion

... is not really an onion. Peel it and find the flag.

[Download](files/JSONion.zip "JSONion.zip")

### Solution

I followed the instructions and started to manually peel one onion layer after another. Each JSON layer contained `op` attribute which indicates what operation needs to be applied to the layer content to get the underlaying layer. 

I quickly realized that the onion is too big and I should write a program to automate the peeling process. The program had to deal with following operations:

* **map**: simple char substitution `mapFrom[i]` -> `mapTo[i]`
* **gzip**: gunzip content
* **b64**: base64 decode content
* **nul**: nothing
* **xor**: XOR masking `content[i] ^ mask`
* **rev**: reverse content string
* **flag**: print content (flag)

I ended up with following Scala program (source code can be found [here](../../src/main/scala/hackvent2017/Day09.scala)).

```scala
case class MapLayer(op: String, mapTo: String, content: String, mapFrom: String)
case class XorLayer(op: String, content: String, mask: String)
case class SimpleLayer(op: String, content: String)

def main(args: Array[String]): Unit = {
  var queue = List(Source.fromFile("hackvent2017/challenges/day09/files/jsonion.json").mkString)
  while (queue.nonEmpty) {
    queue = queue.flatMap { str =>
      val elements = str.parseJson.asInstanceOf[JsArray].elements
      elements.map { el =>
        val str = el.compactPrint
        val op = getLayerType(str)
        op match {
          case "map" => unwrapMapLayer(str)
          case "gzip" => unwrapGzipLayer(str)
          case "b64" => unwrapB64Layer(str)
          case "nul" => unwrapNulLayer(str)
          case "xor" => unwrapXorLayer(str)
          case "rev" => unwrapRevLayer(str)
          case "flag" => unwrapFlagLayer(str)
          case _ => throw new IllegalArgumentException(s"unknown layer type: $op")
        }
      }
    }.flatten
  }
}

private val opPattern = "\"op\":\"([^\"]+)\"".r
private def getLayerType(str: String): String = opPattern.findFirstMatchIn(str).map(m => m.group(1)).get

private def unwrapMapLayer(str: String): Option[String] = {
  val layer = str.parseJson.convertTo[MapLayer]
  Some(layer.content.map(c => layer.mapTo(layer.mapFrom.indexOf(c))))
}

private def unwrapGzipLayer(str: String): Option[String] = {
  val layer = str.parseJson.convertTo[SimpleLayer]
  Some(ascii(gunzip(b64Decode(layer.content))))
}

private def unwrapB64Layer(str: String): Option[String] = {
  val layer = str.parseJson.convertTo[SimpleLayer]
  Some(ascii(b64Decode(layer.content)))
}

private def unwrapNulLayer(str: String): Option[String] = {
  val layer = str.parseJson.convertTo[SimpleLayer]
  Some(layer.content)
}

private def unwrapXorLayer(str: String): Option[String] = {
  val layer = str.parseJson.convertTo[XorLayer]
  val mask = b64Decode(layer.mask)(0)
  val content = b64Decode(layer.content)
  Some(ascii(content.map(b => (b ^ mask).toByte)))
}

private def unwrapRevLayer(str: String): Option[String] = {
  val layer = str.parseJson.convertTo[SimpleLayer]
  Some(layer.content.reverse.toString)
}

private def unwrapFlagLayer(str: String): Option[String] = {
  val layer = str.parseJson.convertTo[SimpleLayer]
  println(s"found flag: ${layer.content}")
  None
}
```

When you run this program you get the following output. The first line contains a fake flag and the other the real one.

```
found flag: THIS-ISNO-THEF-LAGR-EALL-Y...
found flag: HV17-Ip11-9CaB-JvCf-d5Nq-ffyi
```
