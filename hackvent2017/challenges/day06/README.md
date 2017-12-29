# Day 06: Santa's journey

*Make sure Santa visits every country*

Follow Santa Claus as he makes his journey around the world.

[Link](http://challenges.hackvent.hacking-lab.com:4200/)

### Solution

Page is serving QR codes continually changing with each request. I tried to decode few codes and all of them contained name of some state. I assume there is a QR code with flag hidden somewhere so it will be like finding needle in a haystack. 

We can try to catch the flag by hand using a web browser and some mobile app for reading QR codes, but I'm too lazy for this so I wrote a simple Scala program (source code can be found [here](../../src/main/scala/hackvent2017/Day06.scala)) to catch it for me. 


```scala
private val url = new URL("http://challenges.hackvent.hacking-lab.com:4200")

def main(args: Array[String]): Unit = {
  var found = false
  while (!found) {
    val qrcode = download()
    val text = decodeQRCode(qrcode)
    if (text.exists(_.startsWith("HV17"))) {
      println(s"found flag: ${text.get}")
      save(qrcode, "/tmp/qrcode-flag.png")
      found = true
    }
  }
}

private def download(): BufferedImage = ImageIO.read(url)

private def save(image: BufferedImage, path: String): Unit = ImageIO.write(image, "png", new File(path))

private def decodeQRCode(qrcode: BufferedImage): Option[String] = {
  val source = new BufferedImageLuminanceSource(qrcode)
  val bitmap = new BinaryBitmap(new HybridBinarizer(source))
  try {
    Some(new MultiFormatReader().decode(bitmap).getText)
  } catch {
    case e: NotFoundException => None
  }
}
```

Flag was found after a few seconds of run.

![qrcode-flag.png](files/qrcode-flag.png "QR code flag")

```
HV17-eCFw-J4xX-buy3-8pzG-kd3M
```