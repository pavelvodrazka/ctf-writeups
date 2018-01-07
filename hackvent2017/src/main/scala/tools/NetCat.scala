package tools

import java.io.{BufferedReader, InputStreamReader, PrintStream}
import java.net.{InetAddress, ServerSocket, Socket}
import java.util.concurrent.CountDownLatch

import scala.collection.mutable.ArrayBuffer
import scala.concurrent.{Await, Future}
import scala.concurrent.duration.Duration
import scala.util.{Failure, Success}

import scala.concurrent.ExecutionContext.Implicits.global

object NetCat {

  // client mode
  def connect(host: String, port: Int): NetCat = new NetCat(outgoingConnection(host, port))
  def connect(host: String, port: Int, onConnection: NetCat => Unit): NetCat = new NetCat(outgoingConnection(host, port), Some(onConnection))
  private def outgoingConnection(host: String, port: Int) = Future(new Socket(InetAddress.getByName(host), port))

  // server mode
  def listen(port: Int): NetCat = new NetCat(incomingConnection(port))
  def listen(port: Int, onConnection: NetCat => Unit): NetCat = new NetCat(incomingConnection(port), Some(onConnection))
  private def incomingConnection(port: Int) = Future(new ServerSocket(port).accept())

}

class NetCat private(connection: Future[Socket], onConnection: Option[NetCat => Unit] = None) {

  private val buffer = Array.ofDim[Char](1024)
  private val termination = new CountDownLatch(1)

  private var in: Option[BufferedReader] = None
  private var out: Option[PrintStream] = None
  private var trace = false

  connection.onComplete {
    case Success(socket) =>
      println("connection established")
      in = Some(new BufferedReader(new InputStreamReader(socket.getInputStream)))
      out = Some(new PrintStream(socket.getOutputStream, true))
      onConnection.foreach(_.apply(this))
    case Failure(error) =>
      throw new RuntimeException(s"Socket creation failed: $error")
  }

  if (onConnection.isEmpty) Await.ready(connection, Duration.Inf)

  def trace(value: Boolean): Unit = trace = value

  def read: String = {
    val data = ArrayBuffer.empty[Char]
    do {
      val length = stdin.read(buffer)
      data ++= buffer.slice(0, length)
    } while (stdin.ready())

    val msg = data.mkString
    if (trace) print(msg)
    msg
  }

  def writeln(msg: String): Unit = {
    stdout.println(msg)
    if (trace) println(msg)
  }

  def write(msg: String): Unit = {
    stdout.print(msg)
    if (trace) print(msg)
  }

  def write(msg: Array[Byte]): Unit = {
    stdout.print(msg)
    if (trace) print(msg)
  }

  def close(): Unit = {
    connection.map(_.close)
    termination.countDown()
  }

  def await(): Unit = termination.await()

  /* -- private methods -- */

  private def stdin = in.getOrElse(throw new IllegalStateException("Not connected"))
  private def stdout = out.getOrElse(throw new IllegalStateException("Not connected"))

}