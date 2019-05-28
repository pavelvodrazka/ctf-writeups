# 19 - CoUmpact DiAsc

Today the new eggs for HackyEaster 2019 were delivered, but unfortunately the password was partly destroyed by a water damage.

![coumpactdiasc.jpg](files/coumpactdiasc.jpg "coumpactdiasc.jpg")

[coumpactdiasc](files/coumpactdiasc)

### Solution

Provided binary was a non-stripped 64-bit ELF executable.

```
$ file coumpactdiasc
coumpactdiasc: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=68a512b137c34cf17ffeed69b27557b6f8f697f3, with debug_info, not stripped
```

As usual I opened IDA and decompiled the binary but my understanding of the decompiled code wasn't enough to solve the challenge. Luckily *engy* taught me a neat trick how to guess cipher used without deeper understanding of the code. All I had to do was to fill both the encryption key and the encrypted data with zeroes and run the modified binary. This was the decrypted hex value of the first block.

```
140f0f1011b5223d79587717ffd9ec3a
```

I simply searched it on Google which directed me to this useful [page](http://web.mit.edu/kenta/www/three/aes/aes-zero.html). From there I learned that `coumpactdiasc` was a CUDA implementation of AES-128 decryption. This was a huge shortcut.

I found out from the decompiled code that the password should be 16 characters long and I knew from the challenge picture that it ended with `THCUDA`. The remaining 10 characters were still too much since I decided not to use CUDA which I was not familiar with. Instead I took my best guess that the second partially visible word from the end of the password was `WITH` and implemented my parallel bruteforce solver in Scala using solely my CPU power.

Firstly I dumped the [encrypted data](files/egg.encrypted) from IDA using following script.

```
auto fname      = "Z:\\tmp\\egg.encrypted";
auto address    = 0x0687500;
auto size       = 16 * 0x10DA;
auto file       = fopen(fname, "wb");

savefile(file, 0, address, size);
fclose(file);
```

Then I tried to find first 8 uppercase characters of the password which decrypted the first block of the encrypted data to a PNG file header.

```scala
val encrypted = loadFromFile("hackyeaster2019/challenges/egg19/files/egg.encrypted")

bruteforce("WITHCUDA").foreach(password => println(s"password: $password"))

def bruteforce(suffix: String): Option[String] = {
  val block = encrypted.take(16) // first block
  val expected = hex2bytes("89504e470d0a1a0a").tail // PNG header

  val alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

  var found: Option[String] = None
  breakable {
    for (p1 <- alphabet; p2 <- alphabet) {
      alphabet.par.foreach { p3 =>
        val cipher = createCipher()
        val prefix = s"$p1$p2$p3"

        for (p4 <- alphabet; p5 <- alphabet; p6 <- alphabet; p7 <- alphabet; p8 <- alphabet) {
          val passwd = s"$prefix$p4$p5$p6$p7$p8$suffix"
          val decrypted = decrypt(cipher, block, createKey(passwd))

          if (expected.sameElements(decrypted.take(expected.length))) {
            found = Some(passwd)
          }

          if (found.nonEmpty) {
            break
          }
        }
      }
    }
  }

  found
}

def createCipher(): Cipher = Cipher.getInstance("AES/ECB/NoPadding")

def createKey(password: String): Array[Byte] = password.getBytes

def decrypt(cipher: Cipher, encrypted: Array[Byte], key: Array[Byte]): Array[Byte] = {
  val keyspec = new SecretKeySpec(key, "AES")
  cipher.init(Cipher.DECRYPT_MODE, keyspec)
  cipher.doFinal(encrypted)
}
```

It found the password in few minutes.

```
AESCRACKWITHCUDA
```

The last thing to do was to add a method to decrypt the egg using the password and save it to a file.

```scala
bruteforce("WITHCUDA").foreach { password =>
  println(s"password: $password")
  decrypt(password)
}

def decrypt(passwd: String): Unit = {
  val cipher = createCipher()
  val decrypted = decrypt(cipher, encrypted, createKey(passwd))
  saveToFile("hackyeaster2019/challenges/egg19/files/egg.png", decrypted)
}
```

The complete source code of my bruteforce solver can be found [here](../../src/main/scala/hackyeaster2019/Egg19.scala).

### Egg

![egg.png](files/egg.png "egg.png")
