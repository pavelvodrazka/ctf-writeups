package hackvent2018

import java.io.{FileWriter, PrintWriter}
import java.time.LocalTime

import tools.Strings

import scala.util.matching.Regex

object Day19 extends App {

  val alphabet = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  val patterns = Array(
    "(?s)HV18-.{10}[a-zA-Z0-9]{4}-.{9}".r,
    "(?s)HV18-[a-zA-Z0-9]{4}-.{5}[a-zA-Z0-9]{4}-[a-zA-Z0-9]{4}-.{4}".r,
    "^HV18-[a-zA-Z0-9]{4}-[a-zA-Z0-9]{4}-[a-zA-Z0-9]{4}-[a-zA-Z0-9]{4}-[a-zA-Z0-9]{4}$".r)
  val stack = populateStack()

  findNextGroup("") // found W3b45 -> guessed W3b45m
  findNextGroup("W3b45m") // found W3b45m1sRl -> guessed W3b45m1sRly
  findNextGroup("W3b45m1sRly") // found W3b45m1sRlyF45t

  def findNextGroup(prefix: String): Unit = {
    val index = prefix.length / 5
    val pattern = patterns(index)
    val length = 5 - (prefix.length % 5)
    assert(length > 0)

    val writer = new PrintWriter(new FileWriter(s"hackvent2018/challenges/day19/files/bf/grp$index.codes"), true)
    try {
      // start in parallel
      alphabet.par.foreach(head => {
        println(s"${LocalTime.now()}: searching for pattern $prefix$head*")
        for (tail <- Strings.of(alphabet).generate(length - 1)) {
          val code = assembleCode(prefix, head + tail)
          val flag = tryPromoCode(code, pattern)
          if (flag.isDefined) {
            println(s"$code  -->  ${flag.get}")
            writer.println(code.trim)
          }
        }
      })
    } finally {
      println(s"${LocalTime.now()}: done!")
      writer.close()
    }
  }

  def assembleCode(prefix: String = "", group: String): String = (prefix + group).padTo(15, ' ')

  def populateStack(): Array[Byte] = {
    val stack = Array.fill[Byte](112)(0)
    val stack_seg_0x00 = hex2bytes("485631382D545259482D415244452D525452595F484152445F4552212100")
    val stack_seg_0x20 = hex2bytes("C1F27468F351BCF00087AB8AA0D157E3DE7112F37285EB2F87A7ABABFF74").dropWhile(_ == 0x0)
    stack_seg_0x00.copyToArray(stack, 0x0)
    stack_seg_0x20.copyToArray(stack, 0x20)
    stack
  }

  def cloneStack(): Array[Byte] = stack.clone()

  def tryPromoCode(code: String, pattern: Regex): Option[String] = {
    val flag = calculateFlag(cloneStack(), code, code.trim.length == 15)
    flag match {
      case pattern() => Some(flag)
      case _ => None
    }
  }

  def calculateFlag(stack: Array[Byte], code: String, checksum: Boolean): String = {
    var result = 0
    var last = 165

    if (code.length == 15) {
      for (i <- 0 until code.length) {
        val b = code(i) * last + 1337
        result += b + code(i)
        stack(92 + i) = (b % 255 & 0xFF).toByte
        last = b % 255
      }

      if (!checksum || result == 217675) {
        for (j <- 0 until 30) {
          val a = stack(32 + j)
          val b = stack(92 + j % 15)
          stack(j) = (b ^ a).toByte
        }
      }
    }

    ascii(stack.slice(0, 29))
  }

}
