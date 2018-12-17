# Day 15: Watch Me

Turn on your TV! Santa will broadcast todays flag on his member channel. Can you get it without subscription?

[get it here!](files/HACKvent-2018_by_the_oneandonly_HaRdLoCk.ipa)

### Solution

We got an iOS App Store Package containing a Mach-O 64-bit arm64 executable called *HACKvent-2018*.

```
$ unzip HACKvent-2018_by_the_oneandonly_HaRdLoCk.ipa 
Archive:  HACKvent-2018_by_the_oneandonly_HaRdLoCk.ipa
   creating: Payload/
   creating: Payload/HACKvent-2018.app/
   creating: Payload/HACKvent-2018.app/Base.lproj/
   creating: Payload/HACKvent-2018.app/Base.lproj/Main.storyboardc/
  inflating: Payload/HACKvent-2018.app/Base.lproj/Main.storyboardc/UIViewController-BYZ-38-t0r.nib  
  inflating: Payload/HACKvent-2018.app/Base.lproj/Main.storyboardc/BYZ-38-t0r-view-8bC-Xf-vdC.nib  
  inflating: Payload/HACKvent-2018.app/Base.lproj/Main.storyboardc/Info.plist  
  inflating: Payload/HACKvent-2018.app/Assets.car  
  inflating: Payload/HACKvent-2018.app/HACKvent-2018  
  inflating: Payload/HACKvent-2018.app/Info.plist  
 extracting: Payload/HACKvent-2018.app/PkgInfo
$ file Payload/HACKvent-2018.app/HACKvent-2018
Payload/HACKvent-2018.app/HACKvent-2018: Mach-O 64-bit arm64 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|PIE>
```

I decompiled it using IDA and quickly found all the relevant parts.

`ViewController_decryptFlag`'s job was to load Base64 encoded AES ciphertext stored in `v2->flag`, decrypt it using the key calculated from a seed and store the result into `v2->dec`.

```c
v14 = *(_OWORD *)"uQA\\-nM@=1wl\x1EbN!"; // 0x7551415c2d6e4d403d31776c1e624e21
if (strlen((const char *) &v14)) {
  LOBYTE(v14) = 120;
  if (strlen((const char *) &v14) >= 2) {
    v3 = 1LL;
    do
      *((_BYTE *) &v14 + v3++) += 3;
    while (strlen((const char *) &v14) > v3);
  }
}
v4 = objc_msgSend(&OBJC_CLASS___NSString, "stringWithUTF8String:", &v14);
v5 = objc_retainAutoreleasedReturnValue(v4);
v6 = objc_msgSend(&OBJC_CLASS___NSData, "alloc");
v7 = objc_msgSend(v6, "initWithBase64EncodedString:options:", v2->flag, 0LL);
v8 = objc_msgSend(&OBJC_CLASS___NSString, "alloc");
v9 = objc_msgSend(v7, "AES128DecryptedDataWithKey:", v5);
v10 = objc_retainAutoreleasedReturnValue(v9);
v11 = v10;
v12 = (NSString *)objc_msgSend(v8, "initWithData:encoding:", v10, 4LL);
v13 = v2->dec;
v2->dec = v12;
```

Then there was `ViewController_viewDidLoad` responsible for storing Base64 encoded ciphertext into `v2->flag`, calling `ViewController_decryptFlag` to decrypt it and then printing it. 

```c
objc_storeStrong(&v2->flag, CFSTR("xQ34V+MHmhC8V88KyU66q0DE4QeOxAbp1EGy9tlpkLw="));
ViewController_decryptFlag(v2, "decryptFlag");
v13 = objc_msgSend(
        &OBJC_CLASS___NSString,
        "stringWithFormat:",
        CFSTR("%@\n\n%@"),
        CFSTR("HACKvent 2018 - now on your Apple TV!"),
        v2->dec);
```

I reimplemented those methods in Scala. First thing I wrote was this function which calculates decryption key from given seed.

```scala
def calculateKey(seed: Array[Byte]): Array[Byte] = {
  seed.zipWithIndex.map { case (b, i) =>
    if (i == 0) 120
    else b + 3
  }.map(_.toByte)
}
```

Then I implemented AES decryption.

```scala
def aesDecrypt(bytes: Array[Byte], key: Array[Byte]): Array[Byte] = {
  val keyspec = new SecretKeySpec(key, "AES")
  val cipher = Cipher.getInstance("AES/ECB/NoPadding")
  cipher.init(Cipher.DECRYPT_MODE, keyspec)
  cipher.doFinal(bytes)
}
``` 

All that was left was to put those two parts together with the values found in the decompiled source code.

```scala
val ciphertext = b64dec("xQ34V+MHmhC8V88KyU66q0DE4QeOxAbp1EGy9tlpkLw=")
val seed = hex2bytes("7551415c2d6e4d403d31776c1e624e21")

val plaintext = aesDecrypt(ciphertext, calculateKey(seed))
val flag = ascii(plaintext.slice(0, 29))
println(flag)
```

Complete source code can be found [here](../../src/main/scala/hackvent2018/Day15.scala). I ran it and this was the result.

```
HV18-Nc7c-VdEh-pCek-Bw08-jpM3
```
