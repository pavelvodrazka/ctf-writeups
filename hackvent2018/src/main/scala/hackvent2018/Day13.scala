package hackvent2018

import java.io.PrintWriter
import java.nio.file.attribute.PosixFilePermissions
import java.nio.file.{Files, Paths}

object Day13 extends App {

  val path = Paths.get("hackvent2018/challenges/day13/files/control.sh")

  def shouldJump(i: Int): Boolean = // i ~ frame number
    (i > 22 && i < 31) || (i > 36 && i < 53) || (i > 67 && i < 77) || (i > 92 && i < 102) || (i > 110 && i < 120) ||
    (i > 129 && i < 144) || (i > 154 && i < 167) || (i > 176 && i < 193) || (i > 207 && i < 218) || (i > 228 && i < 238) ||
    (i > 246 && i < 261) || (i > 273 && i < 283) || (i > 292 && i < 305) || (i > 318 && i < 330) || (i > 337 && i < 352) ||
    (i > 364 && i < 376) || (i > 387 && i < 398) || (i > 411 && i < 422) || (i > 428 && i < 444) || (i > 455 && i < 467) ||
    (i > 477 && i < 491) || (i > 505 && i < 515) || (i > 527 && i < 538) || (i > 544 && i < 561) || (i > 575 && i < 584) ||
    (i > 595 && i < 606) || (i > 617 && i < 627) || (i > 632 && i < 652)

  val pw = new PrintWriter(path.toFile)
  try {
    pw.println("#!/bin/bash")
    pw.println("sleep $DELAY") // initial delay

    for (frame <- 0 to 666) {
      if (shouldJump(frame)) {
        pw.println("xdotool key space") // press spacebar
      }
      pw.println("sleep $TICK") // wait until next frame
    }
  } finally {
    pw.close()
  }

  Files.setPosixFilePermissions(path, PosixFilePermissions.fromString("rwxr-xr-x"))

}
