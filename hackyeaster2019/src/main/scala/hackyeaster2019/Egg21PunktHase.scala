package hackyeaster2019

import java.nio.file.Paths

import javax.imageio.ImageIO

object Egg21PunktHase extends App {

  val workdir = Paths.get("hackyeaster2019/challenges/egg21/files/punkt_hase/frames")
  val frames = workdir.toFile.listFiles().sorted

  val binary = frames.map { file =>
      val image = ImageIO.read(file)
      val rgb = image.getRGB(0, 0)
      if (rgb == 0xffffffff) 1 else 0
    }.mkString

  println(ascii(bin2bytes(binary)))

}
