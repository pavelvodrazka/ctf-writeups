# 25 - Hidden Egg #1

*Heads* up! You gonna find this hidden egg!

### Solution

The *heads* word written in italics was obviously a hint so I took a look at the response headers. I found one particularly interesting: `Content-Eggcoding`. It contained Base64-encoded URL of the egg.

```bash
$ wget https://hackyeaster.hacking-lab.com/hackyeaster/challenge.html?id=25 -O/dev/null -q -d 2>&1 | grep Content-Eggcoding | cut -d' ' -f2 | base64 -d
https://hackyeaster.hacking-lab.com/hackyeaster/images/eggs/ba0c74ed439ab4795fc36999f542ba50b326e109.png
$ wget -Oegg.png -q https://hackyeaster.hacking-lab.com/hackyeaster/images/eggs/ba0c74ed439ab4795fc36999f542ba50b326e109.png
```
### Egg

![egg.png](files/egg.png "egg.png")