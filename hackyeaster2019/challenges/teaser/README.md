# 00 - Teaser

On April 16, the sixth edition of the Hacky Easter competition is going to start! Check out the [promo video](https://youtu.be/xGGOVUCutO8)!

In order to sweeten the waiting time, we are providing a teaser challenge in advance. Download the video file below, and find the teaser Easter egg.

[he2019_teaser.zip](files/he2019_teaser.zip)

### Solution

Provided ZIP archive contained a high framerate MP4 video file.

```
$ unzip he2019_teaser.zip 
Archive:  he2019_teaser.zip
  inflating: he2019_teaser.mp4
$ ffmpeg -i he2019_teaser.mp4 -hide_banner
Input #0, mov,mp4,m4a,3gp,3g2,mj2, from 'he2019_teaser.mp4':
  Metadata:
    major_brand     : isom
    minor_version   : 512
    compatible_brands: isomiso2mp41
    encoder         : Lavf58.17.101
  Duration: 00:00:05.00, start: 0.000000, bitrate: 15905 kb/s
    Stream #0:0(und): Video: mpeg4 (Simple Profile) (mp4v / 0x7634706D), yuv420p, 100x100 [SAR 1:1 DAR 1:1], 14190 kb/s, 46080.20 fps, 46080 tbr, 46080 tbn, 46080 tbc (default)
    Metadata:
      handler_name  : VideoHandler
```

The video consisted only of fast blinking frames of uniform color. I decided to extract the frames to inspect them.

```
$ ffmpeg -i he2019_teaser.mp4 frames/frame%06d.jpg -hide_banner
```

There were 230.400 of them. I noticed that the number was equal to the square of 480, which could mean that it was an animated sequence pixels of an image of dimensions 480x480. I wrote a Scala program which reconstructed the image pixel by pixel from the extracted frames.

```scala
val workdir = Paths.get("hackyeaster2019/challenges/teaser/files/frames").toAbsolutePath

val egg = reconstructImage(Files.newDirectoryStream(workdir).asScala.toList.sorted)

saveImage(egg, workdir.getParent.resolve("egg.png"))

def reconstructImage(frames: List[Path]): BufferedImage = {
  val size = math.sqrt(frames.size).toInt
  val image = new BufferedImage(size, size, BufferedImage.TYPE_INT_ARGB)

  val graphics = image.getGraphics

  frames.zipWithIndex.foreach { case (file, idx) =>
    val xpos = idx % size
    val ypos = idx / size

    val frame = loadImage(file)
    val color = new Color(frame.getRGB(0, 0))

    graphics.setColor(color)
    graphics.drawRect(xpos, ypos, 1, 1)
  }

  graphics.dispose()

  image
}

def loadImage(path: Path): BufferedImage = ImageIO.read(path.toFile)

def saveImage(image: BufferedImage, path: Path): Unit = ImageIO.write(image, "png", path.toFile)
```

The complete source code can be found [here](../../src/main/scala/hackyeaster2019/Teaser.scala).

### Egg

![egg.png](files/egg.png "egg.png")
