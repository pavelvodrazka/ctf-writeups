package tools

import java.awt.image.BufferedImage
import java.io.File

import com.google.zxing.client.j2se.BufferedImageLuminanceSource
import com.google.zxing.common.HybridBinarizer
import com.google.zxing.{BinaryBitmap, MultiFormatReader}
import javax.imageio.ImageIO

import scala.util.{Success, Try}

object QR {

  def decode(file: String): Option[String] = decode(ImageIO.read(new File(file)))

  def decode(image: BufferedImage): Option[String] = {
    val source = new BufferedImageLuminanceSource(image)
    val bitmap = new BinaryBitmap(new HybridBinarizer(source))

    Try(new MultiFormatReader().decode(bitmap).getText) match {
      case Success(value) => Some(value)
      case _ => None
    }
  }

}
