package hackyeaster2019

object Egg03 extends App {

  println(decrypt("K7sAYzGlYx0kZyXIIPrXxK22DkU4Q+rTGfUk9i9vA60C/ZcQOSWNfJLTu4RpIBy/27yK5CBW+UrBhm0="))

  def encrypt(text: String): String = {
    val bytes = str2bytes(text)
    val x = BigInt(bytes) * BigInt("5" * 101)
    b64enc(x.toByteArray)
  }

  def decrypt(text: String): String = {
    val bytes = b64dec(text)
    val x = BigInt(bytes) / BigInt("5" * 101)
    ascii(x.toByteArray)
  }

}
