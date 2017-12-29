package hackvent2017

import java.awt.image.BufferedImage
import java.io.File
import java.net.URL
import javax.imageio.ImageIO

import com.google.zxing.client.j2se.BufferedImageLuminanceSource
import com.google.zxing.common.HybridBinarizer
import com.google.zxing.{BinaryBitmap, MultiFormatReader, NotFoundException}

object Day06 {

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

}
