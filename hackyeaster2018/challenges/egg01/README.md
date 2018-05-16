# 01 - Prison Break

Your fellow inmate secretly passed you an old cell phone and a weird origami. The only thing on the phone are two stored numbers.

```
555-7747663 Link
555-7475464 Sara
```

Find the password and enter it in the Egg-o-Matic below. Lowercase only, no spaces!

[origami.png](files/origami.png "origami.png")

### Solution

There was a message written on the origami which contained a text followed by two lines of dots.

```
. ... ... .... ... .. ..
... ... .... .. ... .. .
```

I had two lines containing seven clusters of dots each and there were two phone numbers stored in the phone consisting of predial followed by seven numbers. Now I had to put it all together. 

The number of dots in each cluster determined the number of repetitions of a digit at the corresponding position of the phone number. This is called the Multi-Tap Cipher principle. The reconstructed ciphertext was:

```
7 777 444 7777 666 66 33 777 444 7777 55 444 66 4
```

Then I used this [online decoder](https://www.dcode.fr/multitap-abc-cipher) to decrypt the message and got this password:

```
PRISONERISKING
```

### Egg

![egg.png](files/egg.png "egg.png")