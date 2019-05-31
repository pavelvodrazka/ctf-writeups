# 26 - Hidden Egg 2

A stylish blue egg is hidden somewhere here on the web server. Go catch it!

### Solution

The word *stylish* and the challenge image of typewriter letters led me to think that the egg could be hidden somewhere in the CSS or font files on the website. I found [source-sans-pro.css](https://hackyeaster.hacking-lab.com/hackyeaster/css/source-sans-pro.css) containing this `font-face` at the end.

```css
@font-face {
    font-family: 'Egg26';
    font-weight: 400;
    font-style: normal;
    font-stretch: normal;
    src: local('Egg26'),
    local('Egg26'),
    url('../fonts/TTF/Egg26.ttf') format('truetype');
}
```

I downloaded and inspected the referenced font file.

```
$ wget -q https://hackyeaster.hacking-lab.com/hackyeaster/fonts/TTF/Egg26.ttf
$ file Egg26.ttf
Egg26.ttf: PNG image data, 480 x 480, 8-bit/color RGBA, non-interlaced
$ cp Egg26.ttf egg.png
```

### Egg

![egg.png](files/egg.png "egg.png")
