# 22 - The Hunt: Muddy Quagmire

Welcome to the longest scavenger hunt of the world!

The hunt is divided into two parts, each of which will give you an Easter egg. Part 2 is the **Muddy Quagmire**.

To get the Easter egg, you have to fight your way through a maze. On your journey, find and solve **9** mini challenges, then go to the exit. Make sure to check your carrot supply! Wrong submissions cost one carrot each.

[Start the hunt](http://whale.hacking-lab.com:5337/)

### Description

The target site provided me these simple instructions:

> *Click the buttons on the left to get some basic help.* 
>
> *What you are seeing is your navigator interface. This is the only option to interact with the environment. Since we are in an early stage of this new feature, we can't provide you any graphical interface right now. But you are smart (this is why you choosed us!) and will figure it out quickly.*
> 
> *You got it. What would be an exciting trip without the option to move and visit all the nice places we promised you?*
> 
> ``` ``bqq`vsm``0npwf0y0z ```
> 
> *You might meet other visitor during your travel. Some really take a lot of time in there to see our whole effort in detail.*
>  
> *But I promise - everyone is nice in there and will love to meet you! 😈*

### Solution

To explore the maze I reused The Hunt Maze [client](../../src/main/scala/hackyeaster2019/tools/TheHuntMaze.scala) I wrote for the first part of The Hunt: [Misty Jungle](../egg21/README.md). This time the maze was just a single stage containing all 9 mini challenges.

Here is an ASCII version of the map. Starting position is marked by `@` and position of the mini challenges by `¤` character.

```
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░██████░██████████████████████████░░
░█      █                          █░
░█ ████ █  ████████████████     ██ █░
░█ █    █ █░█        ¤   █ █   █ █ █░
░█ █ ████ ██   ████████  █  █ █  █ █░
░█ █    █ █   ¤      ███  █     █  █░
░█ ████ █ █  ███    ██ ██ █ █¤█ ██ █░
░█ █    █ █  ███   ██   █ █  █  █  █░
░█¤█ ████ █  █ ███ ██   █ █     █¤█░░
░█ █   @█¤█  █  ██      █  ██ █████░░
░█ ████████  █      ██  ██  █      █░
░█           █   ██ ███ █   ██████ █░
░░██████████ █   ██   █████      █ █░
░░░░░░░█     ██ ██     █   █ ██  █ █░
░░░░░░░█ ██   ███     █  ¤  █  █ █ █░
░░░░░░░█   █   █░██████          █ █░
░░░░░░░█ ¤ █ █  █   █ ███ ████████ █░
░░░░░░░█   █ █    █   ¤█           █░
░░░░░░░░███░█░████░████░███████████░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
```

#### Randonacci

![screenshot.png](files/randonacci/screenshot.png "screenshot.png")

The reference to the [Fibonacci sequence](https://en.wikipedia.org/wiki/Fibonacci_number) was obvious so it was quite easy to understand what was this challenge about. I wrote my [Randonacci sequence](files/randonacci/solve.py) implementation in Python.

```python
import random
from functools import lru_cache

random.seed(1337)

@lru_cache(100)
def fibonacci(n):
    if n <= 1:
        return 1
    return fibonacci(n - 1) + fibonacci(n - 2)

def fibonacci_seq(n):
    return [ fibonacci(i) for i in range(n) ]

def randonacci(n):
    return n % random.randint(1, n)

randonacci_seq = list(map(randonacci, fibonacci_seq(103)))

print(randonacci_seq[-1])
```

The result: `117780214897213996119`

#### Mathonymous

![screenshot.png](files/mathonymous/screenshot.png "screenshot.png")

I simple evaluated the given math expression using python.

```
$ python -c "print 1+91-92-67"
-67
```

#### C0tt0nt4il Ch3ck

![screenshot.png](files/c0tt0nt4il_ch3ck/screenshot.png "screenshot.png")

The small image with yellow text was quickly moving from side to side which made it unreadable. I stopped the JS timer which moved the image in DevTools. Then I could read the text: `bcd3f6h`.

It was a leetspeak alphabet sequence starting with `n` and ending with `t`. To solve the challenge I had to enter the next letter from the sequence.

The answer: `u`

#### Old Rumpy

![screenshot.png](files/old_rumpy/screenshot.png "screenshot.png")

Since it was `15:47` in my time zone (`UTC+2:00`) I knew his timezone was `UTC+0:00`. Andorra la Vella was in `UTC+2:00` time zone so I simply added 2 hours to the time of his trip.

The time: `09:50`

#### Simon's Eyes

![screenshot.png](files/simons_eyes/screenshot.png "screenshot.png")

I had my ASCII map of the maze so it was easy to just convert the path with this Scala script.

```
def solve(): Array[Char] = "aaawwdddwwaaawwdddwwaaaaassssssssssddddddddddwwwwwwdd".map {
  case 'w' => '1'
  case 's' => '6'
  case 'a' => '3'
  case 'd' => '4'
}.toCharArray
```

The result array:

```javascript
["3","3","3","1","1","4","4","4","1","1","3","3","3","1","1","4","4","4","1","1","3","3","3","3","3","6","6","6","6","6","6","6","6","6","6","4","4","4","4","4","4","4","4","4","4","1","1","1","1","1","1","4","4"];
```

#### Bun Bun's Goods & Gadgets

![screenshot.png](files/bun_bun/screenshot.png "screenshot.png")

I clicked the watch button which triggered series of redirects. I inspected them in DevTools. They differed only in the following headers: `Content-Type`, `Set-Cookie` and `WhatYouHear`.

```
Content-Type: shop/gun
WhatYouHear: Not a fan of this?

Content-Type: shop/wood
WhatYouHear: No haste

Content-Type: shop/hammer
WhatYouHear: Want this?

... (snip) ...

Content-Type: shop/teabag
WhatYouHear: Nothing for you?
``` 

Navigator suggested that I should buy something for Madame Pottine. It was a clear clue on how to identify the right item, the teabag. I copied cookie the value from the `Set-Cookie` header of the request with `Content-Type: shop/teabag`, set it via DevTools and clicked the buy button.

### Flag

```
he19-zKZr-YqJO-4OWb-auss
```
