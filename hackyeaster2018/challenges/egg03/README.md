# 03 - Pony Coder

Tony the pony has encoded something for you. Decode his message and enter it in the egg-o-matic below!  
Lowercase and spaces only, and special characters!

```
gn tn-gha87be4e
```

### Solution

*Pony Coder* obviously referred to the [Punycode](https://en.wikipedia.org/wiki/Punycode)  which is a representation of Unicode with the limited ASCII character subset.

All I had to do was to add `xn--` prefix to the provided code:

```
xn--gn tn-gha87be4e
```

I used [this](https://www.punycoder.com/) online tool to decode the Unicode message:

```
gìn tônì©
```

The instructions about the special characters from the description were a bit misleading, but I quickly realized I have to replace them with the corresponding ASCII characters to get the right password:

```
gin tonic
```

### Egg

![egg.png](files/egg.png "egg.png")