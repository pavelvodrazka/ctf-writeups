# Hidden 01

I tried to play with `day` parameter in the query string of [daily challenges page](https://hackvent.hacking-lab.com/challenge.php?day=1). The first value I tried was 25 and I got following result.

```
WHAT THE F*** ARE YOU TRYING?
nice try, geek!

The resource (#1959) you are trying to access, is not (yet) for your eyes.
```

So I incremented the `day` value by one and got.

```
WHAT THE F*** ARE YOU TRYING?
nice try, geek!

The resource (#1958) you are trying to access, is not (yet) for your eyes.
```

Very similar output, but the resource `id` value decreased by one. So the `day` value and the resource `id` are connected.

Next step was to directly try to set `day` value to 1984 and the result changed.

```
WHAT THE F*** ARE YOU TRYING?
nice try, geek!

The resource you are trying to access, is hidden in the header.
```

So I looked at the response headers and found the flag.

```http
Connection:Keep-Alive
Content-Type:text/html; charset=UTF-8
Date:Sun, 31 Dec 2017 21:19:56 GMT
Flag:HV17-4llw-aysL-00ki-nTh3-H34d
Keep-Alive:timeout=5, max=100
Server:Merry Christmas & Hacky New Year
Strict-Transport-Security:max-age=15768000
Transfer-Encoding:chunked
```

Hidden flag:

```
HV17-4llw-aysL-00ki-nTh3-H34d
```