package tools

import scala.annotation.tailrec

object Strings {
  def of(alphabet: String): Strings = new Strings(alphabet)
}

class Strings(val alphabet: String) {

  def generate(strlen: Int): Stream[String] = {
    assert(strlen > 0)

    def stringOf(indexes: Array[Int]): String = indexes.map(alphabet).mkString
    def next(indexes: Array[Int]): Array[Int] = {
      @tailrec def inc(i: Int): Boolean = if (i < 0) true else {
        indexes(i) = (indexes(i) + 1) % alphabet.length
        if (indexes(i) > 0) false
        else inc(i - 1)
      }
      val carry = inc(strlen - 1)
      if (!carry) indexes else null
    }

    Stream.iterate(Array.fill(strlen)(0))(next).takeWhile(_ != null).map(stringOf)
  }

}
