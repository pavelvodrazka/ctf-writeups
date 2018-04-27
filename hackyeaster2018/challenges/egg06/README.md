# 06 - Cooking for Hackers

You've found this recipe online:

```
1 pinch: c2FsdA==
2 tablesspoons: b2ls
1 teaspoon: dDd3Mmc=
50g: bnRkby4=
2 medium, chopped: b25pb24=
```

But you need one more secret ingredient! Find it!

### Solution

The first step was obvious. I used Base64 decoder to get the ingredient names.

```
1 pinch: salt
2 tablesspoons: oil
1 teaspoon: t7w2g
50g: ntdo.
2 medium, chopped: onion
``` 

The next step took me a while. I have to say I was completely blind. The third and fourth ingredients didn't make any sense to me. Then I focused on the dot at the end of fourth ingredient and finally realized that I have to concat those ingredients to get an onion address:

```
saltoilt7w2gntdo.onion
```

I opened the address in Tor Browser and got the egg.

### Egg

![egg.png](files/egg.png "egg.png")