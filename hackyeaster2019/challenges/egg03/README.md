# 03 - Sloppy Encryption

The easterbunny is not advanced at doing math and also really sloppy.

He lost the encryption script while hiding your challenge. Can you decrypt it?

```
K7sAYzGlYx0kZyXIIPrXxK22DkU4Q+rTGfUk9i9vA60C/ZcQOSWNfJLTu4RpIBy/27yK5CBW+UrBhm0=
```

[sloppy.rb](files/sloppy.rb)

### Solution

The encryption written in Ruby looked like this.

```ruby
require"base64"
puts"write some text and hit enter:"
input=gets.chomp
h=input.unpack('C'*input.length).collect{|x|x.to_s(16)}.join
ox='%#X'%h.to_i(16)
x=ox.to_i(16)*['5'].cycle(101).to_a.join.to_i
c=x.to_s(16).scan(/../).map(&:hex).map(&:chr).join
b=Base64.encode64(c)
puts"encrypted text:""#{b}"
```

Since I do not know Ruby at all I decided to reimplement the encryption function in Scala.

```scala
def encrypt(text: String): String = {
  val bytes = str2bytes(text)
  val x = BigInt(bytes) * BigInt("5" * 101)
  b64enc(x.toByteArray)
}
```

Now the code was much more understandable to me so it was pretty easy to write the decryption function.

```scala
def decrypt(text: String): String = {
  val bytes = b64dec(text)
  val x = BigInt(bytes) / BigInt("5" * 101)
  ascii(x.toByteArray)
}
```

Then I simply decoded provided Base64 encoded ciphertext.

```scala
println(decrypt("K7sAYzGlYx0kZyXIIPrXxK22DkU4Q+rTGfUk9i9vA60C/ZcQOSWNfJLTu4RpIBy/27yK5CBW+UrBhm0="))
```

The complete source code can be found [here](../../src/main/scala/hackyeaster2019/Egg03.scala).

Password: `n00b_style_crypto`

### Egg

![egg.png](files/egg.png "egg.png")
