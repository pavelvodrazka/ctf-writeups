package hackyeaster2019

import scala.io.Source

object Egg16 extends App {

  case class Record(id: String, pid: String, kind: String, ord: Int, value: String)

  val records = Source.fromFile("hackyeaster2019/challenges/egg16/files/pngs.dump")
    .getLines
    .map(_.split('\t'))
    .map(cols => Record(cols(0), cols(1), cols(2), cols(3).toInt, cols(4)))
    .toList

  records.filter(_.kind == "png").foreach { png =>
    val path = s"hackyeaster2019/challenges/egg16/files/pngs/${png.value}.png"
    val bytes = assemblePNG(png)
    saveToFile(path, bytes)
  }

  def assemblePNG(root: Record): Array[Byte] = {
    List("png.head", "png.ihdr", "png.chrm", "png.gama", "png.bkgd", "png.phys", "png.idat", "png.text", "png.time", "png.iend")
      .flatMap(kind => assembleChunk(root, kind))
      .toArray
  }

  def assembleChunk(root: Record, kind: String): Array[Byte] = {
    records.filter(r => r.pid == root.id && r.kind == kind)
      .sortBy(_.ord)
      .flatMap { r => if (records.exists(_.pid == r.id)) assembleChunk(r, kind) else b64dec(r.value) }
      .toArray
  }

}
