package hackyeaster2018

import java.io.{BufferedReader, InputStreamReader}
import java.net.Socket

import tools.PaddingOracle

object Egg22 {

  private val oracle = PaddingOracle(bytes => {
    val socket = new Socket("whale.hacking-lab.com", 5555)
    val in = new BufferedReader(new InputStreamReader(socket.getInputStream))
    val out = socket.getOutputStream
    try {
      out.write(bytes)
      in.readLine.startsWith("ok")
    } finally {
      socket.close()
    }
  })

  def main(args: Array[String]): Unit = {
    val ciphertext = loadFromFile("hackyeaster2018/challenges/egg22/files/secret.enc")

    val decrypted = oracle.decrypt(ciphertext)
    val plaintext = new String(decrypted, 0, decrypted.length - decrypted.last) // decrypted = plaintext minus padding

    println(plaintext)
  }

}
