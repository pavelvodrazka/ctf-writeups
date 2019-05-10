# 09 - rorriM rorriM

Mirror, mirror, on the wall, who's the fairest of them all?

[evihcra.piz](files/evihcra.piz)

### Solution

As the filename suggested the provided [evihcra.piz](files/evihcra.piz) file was a mirrored image of original `archive.zip` file. I found this very useful [thread](https://unix.stackexchange.com/questions/416401/how-to-reverse-the-content-of-binary-file) on StackOverflow which helped me to get the [original](files/archive.zip) ZIP archive.

```
$ xxd -p -c1 < evihcra.piz | tac | xxd -p -r > archive.zip
$ unzip archive.zip 
Archive:  archive.zip
  inflating: 90gge.gnp
```

I inspected the image extracted from the archive.

```
xxd -l 16 90gge.gnp 
00000000: 8947 4e50 0d0a 1a0a 0000 000d 4948 4452  .GNP........IHDR
```

It looked like a standard PNG image but the header was reversed (`.GNP` instead of `.PNG`). I fixed that and got this image.

![egg09.png](files/egg09.png "egg09.png")

Again the image was mirrored and it had inverted colors. It was an easy task for ImageMagick.

```
$ convert egg09.png -flop -negate egg.png
```

### Egg

![egg.png](files/egg.png "egg.png")
