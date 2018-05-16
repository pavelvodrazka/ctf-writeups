# 04 - Memeory

Fancy a round of memeory?

Click [here](https://hackyeaster.hacking-lab.com/hackyeaster/memeory/memeory.html) to play.

### Description

The provided link brought you to the page with a 10x10 Meme version of the Memory game. You had to beat the game to get the egg, but it wasn't that easy. After three misses the game ended with a javascript alert:

*you only have 3 miss clicks, hobo...*

### Solution

It was a task for some javascript code executed through the browser's console.

I quickly came up with this script which simply flips all the cards to reveal the images. 

```javascript
$("figure > a").each(function(idx) {
    var front = $(this).children(".boxFront");
    var back = $(this).children(".boxBack");
    var image = $(front).attr("src");
    $(back).attr("src", image);
});
```

Although it worked like a charm I still had to manually find and click all the matching images.

Later I realized that I can identify cards by the anchor values in their URLs. The matching cards had anchor values `#card_${n}` and `#card_${n+1}`. It allowed me to write a new script which did all the work for me. It simply simulates clicking on matching cards by sending click requests in the right order.

```javascript
for (i = 0; i < 100; i++) {
    $("figure > a[href='#card_" + i + "']").click();
}
```

### Egg

![egg.png](files/egg.png "egg.png")