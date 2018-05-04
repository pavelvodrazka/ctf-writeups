package hackyeaster2018

import scala.io.Source

object Egg21 {

  // extracted from "forgotten" public key inside the hotdog.jpg
  private val modulus = BigInt("04cc95ea81f67bd12a14e7478ff60430d48398648db450ca0beb6560c04db0bdad7c4202a69e8229b65d4943f32571624cb3259c660186daeea2d37b76dcb6870c2fb19774c7f79108952cf8a03766ae1223c5ade599bd9fdbe05cdcbce861f92a6bca9024627f526a94f21b32dda587434f2a161514fb42012122c0c672772c5d", 16)
  private val pubkey = BigInt("956dd5196b9b90ecef5b82ed963ef530c2fb88f992b980e642176f7dd5045afeb7431cac98894c716578de9b11880b1be80baf7cc15be656acc6fec093fa22c0ac88783a6487832775ca37000969ac7df1d82efb25ded9cdf498aee6accde9a1ad8478caff8db834ad1191f8d47669d0c9d60dfcca9f4bb73e0247c941657ff7", 16)
  private val privkey = calculatePrivKey()

  def main(args: Array[String]): Unit = {
    val encrypted = b64Decode(Source.fromFile("hackyeaster2018/challenges/egg21/files/encrypted_egg.b64").mkString)
    println(ascii(decrypt(encrypted)))
  }

  private def calculatePrivKey(): BigInt = {
    // modulus = p * q
    // factorization of modulus (in decimal) done by http://factordb.com/index.php?query=862742154642231839245490652305447811003939188889879160601916825098919376499239658083286458498338565473757684120273913355054578804223148627929674551888979169974716805550925487885904303307287848617172307192932601824962171808534262290925626312023335394889835400367620156052212076713592230783194049748993932995677
    val p = BigInt("21787995226958172829467888206490681114003213044856067031128998135742112625134255635772352085743308949466567934785458002652816217408595135233580400606278413")
    val q = BigInt("39597133451487334277950950530003861952885112404500618298702299905566831117666470098035890477572068210683971280104304184580469417440656443567196733216950929")

    // calculate phi
    val phi = lcm(p - 1, q - 1)

    // privkey * pubkey ≡ 1 (mod phi)
    pubkey.modInverse(phi)
  }

  // RSA encryption: ciphertext = plaintext ^ pubkey % modulus
  private def encrypt(plaintext: Array[Byte]): Array[Byte] = {
    val base = BigInt(plaintext)
    base.modPow(pubkey, modulus).toByteArray
  }

  // RSA decryption: plaintext = ciphertext ^ privkey % modulus
  private def decrypt(ciphertext: Array[Byte]): Array[Byte] = {
    val base = BigInt(ciphertext)
    base.modPow(privkey, modulus).toByteArray
  }

}
