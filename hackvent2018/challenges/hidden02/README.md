# Hidden 02

The second hidden flag was an alternative solution to [day 15](../day15/README.md).

I used `dig` to lookup text strings for [www.hackvent.org](https://www.hackvent.org/) domain and this was the result.

```
$ dig www.hackvent.org txt | grep '^\w'
www.hackvent.org.	138	IN	TXT	"Nice try, but this would be too easy, nah? However, get a hidden flag: SFYxOC1PU0lOLVRjNG4tUjNWMy1hbEl0LUFsbDE="
```

Then I simply Base64 decoded the flag.

```
$ echo "SFYxOC1PU0lOLVRjNG4tUjNWMy1hbEl0LUFsbDE=" | base64 -d
HV18-OSIN-Tc4n-R3V3-alIt-All1
```
