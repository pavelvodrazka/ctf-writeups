package hackyeaster2019

import java.awt.Color
import java.awt.image.BufferedImage
import java.nio.file.{Files, Path, Paths}

import javax.imageio.ImageIO

import scala.collection.JavaConverters._

object Teaser extends App {

  val workdir = Paths.get("hackyeaster2019/challenges/teaser/files/frames").toAbsolutePath

  val egg = reconstructImage(Files.newDirectoryStream(workdir).asScala.toList.sorted)

  saveImage(egg, workdir.getParent.resolve("egg.png"))

  def reconstructImage(frames: List[Path]): BufferedImage = {
    val size = math.sqrt(frames.size).toInt
    val image = new BufferedImage(size, size, BufferedImage.TYPE_INT_ARGB)

    val graphics = image.getGraphics

    frames.zipWithIndex.foreach { case (file, idx) =>
      val xpos = idx % size
      val ypos = idx / size

      val frame = loadImage(file)
      val color = new Color(frame.getRGB(0, 0))

      graphics.setColor(color)
      graphics.drawRect(xpos, ypos, 1, 1)
    }

    graphics.dispose()

    image
  }

  def loadImage(path: Path): BufferedImage = ImageIO.read(path.toFile)

  def saveImage(image: BufferedImage, path: Path): Unit = ImageIO.write(image, "png", path.toFile)

}
