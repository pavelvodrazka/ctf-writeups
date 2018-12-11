# Day 04: Pirating like in the 90ies

*Ahoy, my name is Santa and I want to be a pirate!*

[Go to the pirates!](https://hackvent.hacking-lab.com/Pirates_123/)

### Description

The link brought you to a page with 12 form inputs which looked like this.

![pirates.png](files/pirates.png "pirates")

### Solution

Since I didn't get the reference at first I decided to start with HTML and JS code inspection. I figured out that I was supposed to fill a 4 digits representing a year into each of the form inputs. The `JollyRoger` function concatenated these values into a single string which was then XORed with another "secret" string.

I tried to take advantage of known position of dashes in the result flag and matching halves of the faces to calculate some parts of inputs but it turned out to be a dead end.

After wasting a lot of time I decided to return to the beginning. I read the title again and then I finally got it. It was a reference to the software piracy in the 90s.

It turned out to be an anti-piracy protection of the pirates adventure game [The Secret of Monkey Island](https://en.wikipedia.org/wiki/The_Secret_of_Monkey_Island) from early 90s. The protection itself is called [Dial-a-Pirate](http://www.oldgames.sk/codewheel/secret-of-monkey-island-dial-a-pirate).

Instructions from the game manual:

*Once you've started the program a screen will appear displaying pirate's face (actually a combination of two faces). You will be prompted to enter a date that was significant in the pirate's life at a given geographical location. Use your Dial-a-Pirate wheel to match up the top and bottom halves of the pirate face you see on the screen. Then, locate the window on the wheel that matches the geographical location mentiones on the screen. Using the keyboard, type the date you see in the window.*

Using [this decoder](http://www.oldgames.sk/codewheel/secret-of-monkey-island-dial-a-pirate) I was able to get the right years to fill into the form inputs.

```
1585        1690        1726        1701
1712        1709        1692        1577
1710        1684        1680        1585
```

After submitting the form I got the flag shown in an alert window.

```
HV18-5o9x-4geL-7hkJ-wc4A-xp8F
```
