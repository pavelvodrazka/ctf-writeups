package hackyeaster2019

import scala.reflect.runtime.currentMirror
import scala.tools.reflect.ToolBox

object Egg21Mathonymous extends App {

  val toolbox = currentMirror.mkToolBox()

  val ops = List("+", "-", "*", "/")
  val solution = for {
    op1 <- ops; op2 <- ops; op3 <- ops; op4 <- ops; op5 <- ops
    if eval(s"11 $op1 18 $op2 15 $op3 18 $op4 13 $op5 4") == 84
  } yield s"11 $op1 18 $op2 15 $op3 18 $op4 13 $op5 4 = 84"

  println(solution)

  def eval(expr: String): Int = {
    toolbox.eval(toolbox.parse(expr)).asInstanceOf[Int]
  }

}
