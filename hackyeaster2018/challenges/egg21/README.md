# 21 - Hot Dog

or: how to solve this darn crypto challenge to get your sleep back.

Enter the flag found, into the Egg-o-Matic below, without brackets.

[hotdog.zip](files/hotdog.zip)

### Solution

I extracted the ZIP archive and looked at what I got.

```bash
$ unzip hotdog.zip 
Archive:  hotdog.zip
  inflating: hotdog.jpg
$ du -h hotdog.jpg 
34M	hotdog.jpg
```

The archive contained only one image file which was suspiciously large. It immediately caught my attention and I decided to inspect its content in `hexedit`. It turned out that it was a good idea. I found a [RSA public key](files/pubkey.pem) hidden at the beginning of the file.

```
*Don't forget to delete this*
-----BEGIN PUBLIC KEY-----
MIIBIDANBgkqhkiG9w0BAQEFAAOCAQ0AMIIBCAKBgQTMleqB9nvRKhTnR4/2BDDU
g5hkjbRQygvrZWDATbC9rXxCAqaegim2XUlD8yVxYkyzJZxmAYba7qLTe3bctocM
L7GXdMf3kQiVLPigN2auEiPFreWZvZ/b4FzcvOhh+SprypAkYn9SapTyGzLdpYdD
TyoWFRT7QgEhIsDGcncsXQKBgQCVbdUZa5uQ7O9bgu2WPvUwwvuI+ZK5gOZCF299
1QRa/rdDHKyYiUxxZXjemxGICxvoC698wVvmVqzG/sCT+iLArIh4OmSHgyd1yjcA
CWmsffHYLvsl3tnN9Jiu5qzN6aGthHjK/424NK0RkfjUdmnQydYN/MqfS7c+AkfJ
QWV/9w==
-----END PUBLIC KEY-----
```

The public key still did not explain the image size so I tried to use `foremost` tool on the file.

```bash
$ foremost -v -i hotdog.jpg 
Processing: hotdog.jpg
Length: 33 MB (35115900 bytes)
Num	 Name (bs=512)	       Size	 File Offset	 Comment 
0:	00068501.png 	      42 KB 	   35072724 	  (480 x 480)
1 FILES EXTRACTED
```

It found a [PNG image](files/encrypted_egg.png) containing an egg with a QR code inside:

![encrypted_egg.png](files/encrypted_egg.png "encrypted_egg.png")

I scanned to QR code and got a [Base64 encoded string](files/encrypted_egg.b64):

```
Arf3ThIY8VQg2GUd249wzDYi7CXqTST+9g4Q7bbT2eF+mD2KB+6oi3rVSY/eZ6/onNBNYPo2BPqIVEbL35G62pIHvabGcrYosGCpYhiz6EYnamnNPrHdzmEOs8lCRw1c2Pe8kl41FH0ud7tBn6qD/stnZfGkcbeIrjaSiIYSveHS
```

Something was telling me that this could be the flag encrypted with the public key I found earlier. Since there was no private key I decided to try to compute it from the public key. 

In case you haven't done this before there is a very handy [article about the RSA key generation](https://en.wikipedia.org/wiki/RSA_(cryptosystem)#Key_generation) on Wikipedia which contains all the necessary information.

The first step was to extract the modulus and the exponent.

```bash
$ openssl rsa -pubin -noout -text < pubkey.pem 
Public-Key: (1027 bit)
Modulus:
    04:cc:95:ea:81:f6:7b:d1:2a:14:e7:47:8f:f6:04:
    30:d4:83:98:64:8d:b4:50:ca:0b:eb:65:60:c0:4d:
    b0:bd:ad:7c:42:02:a6:9e:82:29:b6:5d:49:43:f3:
    25:71:62:4c:b3:25:9c:66:01:86:da:ee:a2:d3:7b:
    76:dc:b6:87:0c:2f:b1:97:74:c7:f7:91:08:95:2c:
    f8:a0:37:66:ae:12:23:c5:ad:e5:99:bd:9f:db:e0:
    5c:dc:bc:e8:61:f9:2a:6b:ca:90:24:62:7f:52:6a:
    94:f2:1b:32:dd:a5:87:43:4f:2a:16:15:14:fb:42:
    01:21:22:c0:c6:72:77:2c:5d
Exponent:
    00:95:6d:d5:19:6b:9b:90:ec:ef:5b:82:ed:96:3e:
    f5:30:c2:fb:88:f9:92:b9:80:e6:42:17:6f:7d:d5:
    04:5a:fe:b7:43:1c:ac:98:89:4c:71:65:78:de:9b:
    11:88:0b:1b:e8:0b:af:7c:c1:5b:e6:56:ac:c6:fe:
    c0:93:fa:22:c0:ac:88:78:3a:64:87:83:27:75:ca:
    37:00:09:69:ac:7d:f1:d8:2e:fb:25:de:d9:cd:f4:
    98:ae:e6:ac:cd:e9:a1:ad:84:78:ca:ff:8d:b8:34:
    ad:11:91:f8:d4:76:69:d0:c9:d6:0d:fc:ca:9f:4b:
    b7:3e:02:47:c9:41:65:7f:f7
```

Then I wrote a Scala [program](../../src/main/scala/hackyeaster2018/Egg21.scala) which calculates the private key and decrypts the flag with it.

This is how the private key is calculated.

```scala
val modulus = BigInt("04cc95ea81f67bd12a14e7478ff60430d48398648db450ca0beb6560c04db0bdad7c4202a69e8229b65d4943f32571624cb3259c660186daeea2d37b76dcb6870c2fb19774c7f79108952cf8a03766ae1223c5ade599bd9fdbe05cdcbce861f92a6bca9024627f526a94f21b32dda587434f2a161514fb42012122c0c672772c5d", 16)
val pubkey = BigInt("956dd5196b9b90ecef5b82ed963ef530c2fb88f992b980e642176f7dd5045afeb7431cac98894c716578de9b11880b1be80baf7cc15be656acc6fec093fa22c0ac88783a6487832775ca37000969ac7df1d82efb25ded9cdf498aee6accde9a1ad8478caff8db834ad1191f8d47669d0c9d60dfcca9f4bb73e0247c941657ff7", 16)

def calculatePrivKey(): BigInt = {
  // modulus = p * q
  // factorization of modulus (in decimal) done by http://factordb.com/index.php?query=862742154642231839245490652305447811003939188889879160601916825098919376499239658083286458498338565473757684120273913355054578804223148627929674551888979169974716805550925487885904303307287848617172307192932601824962171808534262290925626312023335394889835400367620156052212076713592230783194049748993932995677
  val p = BigInt("21787995226958172829467888206490681114003213044856067031128998135742112625134255635772352085743308949466567934785458002652816217408595135233580400606278413")
  val q = BigInt("39597133451487334277950950530003861952885112404500618298702299905566831117666470098035890477572068210683971280104304184580469417440656443567196733216950929")

  // calculate phi
  val phi = lcm(p - 1, q - 1)

  // privkey * pubkey ≡ 1 (mod phi)
  pubkey.modInverse(phi)
}
```

And this was the result of the decryption with the calculated private key:

```
Great job haxxor, here's your flag: {b3w4r3_0f_c0n71nu3d_fr4c710n5}
```

### Egg

![egg.png](files/egg.png "egg.png")