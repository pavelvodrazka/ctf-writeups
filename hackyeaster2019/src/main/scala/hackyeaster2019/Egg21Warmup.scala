package hackyeaster2019

import java.nio.file.Paths

import javax.imageio.ImageIO

object Egg21Warmup extends App {

val dir = Paths.get("hackyeaster2019/challenges/egg21/files/warmup")

val left = ImageIO.read(dir.resolve("c11.png").toFile)
val right = ImageIO.read(dir.resolve("75687138-87d0-4c78-b2e3-f335acf76f15.png").toFile)

println(differences)

def differences: String = {
  assert(left.getWidth == right.getWidth && left.getHeight == right.getHeight)

  val pixels = for (x <- 0 until left.getWidth; y <- 0 until left.getHeight) yield (x, y)
  val differences = pixels.filter { case (x, y) => left.getRGB(x, y) != right.getRGB(x, y) }

  differences.map(t => s"[${t._1},${t._2}]").mkString("[", ", ", "]")
}

}
