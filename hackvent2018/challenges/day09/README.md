# Day 09: Fake xmass balls

A rogue manufacturer is flooding the market with counterfeit yellow xmas balls. They are popping up like everywhere!

Can you tell them apart from the real ones? Perhaps there is some useful information hidden in the fakes...

![fake.png](files/fake.png "fake ball")

### Solution

I started to play with the [real](files/real.png) and the [fake](files/fake.png) ball in Stegsolve's image combiner.

It turned out to be good idea. In a while I found remarkable result of image subtraction (fake - real): 

![fake-real.png](files/fake-real.png "fake - real")

It immediately reminded me a part of a QR code. The next thing I tried was to subtract the images in reverse order (real - fake)

![real-fake.png](files/real-fake.png "real - fake")

This was the missing piece I was looking for. I used addition image combiner to put both parts together:

![(real-fake)+(fake-real).png](files/(real-fake)+(fake-real).png "(real - fake) + (fake - real)")

Voilà! A QR code. I played with it a bit using Gimp to make it more readable.

![qrcode.png](files/qrcode.png "QR code")

Here is the flag stored in the QR code.

```
HV18-PpTR-Qri5-3nOI-n51a-42gJ
```
