package hackvent2017

import java.nio.file.{Files, Paths}

import hackvent2017.day22.IceKey

object Day22 {

  def main(args: Array[String]): Unit = {
    val encrypted = Files.readAllBytes(Paths.get("hackvent2017/challenges/day22/files/HV17-flag"))
    val key = "ice-cold"

    val ice = new IceKey(1)
    ice.set(key.getBytes)

    val flag = encrypted.grouped(8).map { enc =>
      val dec = Array.ofDim[Byte](8)
      ice.decrypt(enc, dec)
      ascii(dec)
    }.mkString

    print(flag)
  }

}
