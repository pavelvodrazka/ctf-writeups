# 24 - Hidden Egg 1

I like hiding eggs in baskets :)

### Solution

I found a image of a basket on the Hacky Easter page.

```
$ wget -q -O basket.jpg https://hackyeaster.hacking-lab.com/hackyeaster/images/flags.jpg
$ file basket.jpg 
basket.jpg: JPEG image data, JFIF standard 1.01, resolution (DPI), density 72x72, segment length 16, Exif Standard: [TIFF image data, big-endian, direntries=17, height=458, bps=0, PhotometricIntepretation=RGB, description=https://hackyeaster.hacking-lab.com/hackyeaster/images/eggs/f8f87dfe67753457dfee34648860dfe786., width=732], baseline, precision 8, 732x458, components 3
```

The egg was hidden directly in the image description.

```
$ strings basket.jpg | grep eggs | head -n 1
https://hackyeaster.hacking-lab.com/hackyeaster/images/eggs/f8f87dfe67753457dfee34648860dfe786.png
$ wget -q -O egg.png https://hackyeaster.hacking-lab.com/hackyeaster/images/eggs/f8f87dfe67753457dfee34648860dfe786.png
```

### Egg

![egg.png](files/egg.png "egg.png")
