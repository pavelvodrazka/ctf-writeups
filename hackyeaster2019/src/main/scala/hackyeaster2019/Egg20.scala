package hackyeaster2019

import java.awt.Color
import java.awt.image.BufferedImage
import java.nio.file.Paths

import javax.imageio.ImageIO

object Egg20 extends App {

  val scrambled = ImageIO.read(Paths.get("hackyeaster2019/challenges/egg20/files/egg-scrambled.png").toFile)

  val pixels = pixelsOf(scrambled)
  val ordered = pixels.sortBy(_.find(c => c.getAlpha == 0 && c.getRed > 0).map(_.getRed).getOrElse(0))

  val shifted = ordered.map { row =>
    def shiftedComponent(extract: Color => Int): Array[Int] = {
      val n = row.indexWhere(c => c.getAlpha == 0 && (extract(c) > 0 || (c.getRGB == 0)))
      shiftLeft(row, n).filter(_.getAlpha > 0).map(extract)
    }

    val red = shiftedComponent(_.getRed)
    val green = shiftedComponent(_.getGreen)
    val blue = shiftedComponent(_.getBlue)

    (red, green, blue).zipped.map { case (r, g, b) => new Color(r, g, b) }
  }

  ImageIO.write(imageOf(shifted), "png", Paths.get("hackyeaster2019/challenges/egg20/files/egg.png").toFile)

  def shiftLeft(row: Array[Color], n: Int) = {
    assert(n >= 0 && n < row.length)
    row.slice(n, row.length) ++ row.slice(0, n)
  }

  def pixelsOf(image: BufferedImage): Array[Array[Color]] = {
    val width = image.getWidth
    val height = image.getHeight

    val pixels = Array.ofDim[Color](height, width)
    for (y <- 0 until height) {
      for (x <- 0 until width) {
        pixels(y)(x) = new Color(image.getRGB(x, y), true)
      }
    }

    pixels
  }

  def imageOf(pixels: Array[Array[Color]]): BufferedImage = {
    val height = pixels.length
    val width = pixels.head.length

    val image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB)
    for (y <- 0 until height) {
      for (x <- 0 until width) {
        image.setRGB(x, y, pixels(y)(x).getRGB)
      }
    }

    image
  }

}
