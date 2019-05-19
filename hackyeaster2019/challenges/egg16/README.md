# 16 - Every-Thing

After the brilliant idea from [here](http://geek-and-poke.com/geekandpoke/2013/7/22/future-proof-your-data-model).

The data model is stable and you can really store *Every-Thing*.

[EveryThing.zip](files/EveryThing.zip)

### Solution

Provided ZIP archive contained a MySQL dump file.

```
$ unzip EveryThing.zip 
Archive:  EveryThing.zip
  inflating: EveryThing.sql
```

It contained a single table called `Thing` with the following schema.

```mysql
CREATE TABLE `Thing` (
  `id` binary(16) NOT NULL,
  `ord` int(11) NOT NULL,
  `type` varchar(255) NOT NULL,
  `value` varchar(1024) DEFAULT NULL,
  `pid` binary(16) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FKfaem61vklu1cjw9ckunvpicgi` (`pid`),
  CONSTRAINT `FKfaem61vklu1cjw9ckunvpicgi` FOREIGN KEY (`pid`) REFERENCES `Thing` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
```

I imported it into a local MariaDB instance to explore the data. I focused on the `type` column and quickly noticed a promising group of types starting with `png`.

```mariadb
MariaDB [he19thing]> select distinct type from Thing where type like 'png%';
+----------+
| type     |
+----------+
| png      |
| png.idat |
| png.phys |
| png.head |
| png.time |
| png.bkgd |
| png.iend |
| png.ihdr |
| png.chrm |
| png.gama |
| png.text |
+----------+
```

The type names matched the standard [PNG chunks](http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html#C.Summary-of-standard-chunks). I dumped all the records belonging to this group for further processing.

```mariadb
MariaDB [he19thing]> select hex(id) id, hex(pid) pid, type, ord, value into outfile '/tmp/pngs.dump' from Thing where type like 'png%' order by hex(pid), type, ord;
```

Then I looked up the order constraints of the individual PNG chunks.

| Chunk     | Constraint                         |
| :-------- | :--------------------------------- |
| png.ihdr  | Must be first                      |
| png.chrm  | Before PLTE and IDAT               |
| png.gama  | Before PLTE and IDAT               |
| png.bkgd  | After PLTE; before IDAT            |
| png.phys  | Before IDAT                        |
| png.idat  | Multiple IDATs must be consecutive |
| png.text  | None                               |
| png.time  | None                               |
| png.iend  | Must be last                       |

I ended up with this chunks order:
`png.head`, `png.ihdr`, `png.chrm`, `png.gama`, `png.bkgd`, `png.phys`, `png.idat`, `png.text`, `png.time`, `png.iend`.

Now it was time to write a Scala program to put all the chunks together to get the PNG images stored in the database dump.

```scala
case class Record(id: String, pid: String, kind: String, ord: Int, value: String)

val records = Source.fromFile("hackyeaster2019/challenges/egg16/files/pngs.dump")
  .getLines
  .map(_.split('\t'))
  .map(cols => Record(cols(0), cols(1), cols(2), cols(3).toInt, cols(4)))
  .toList

records.filter(_.kind == "png").foreach { png =>
  val path = s"hackyeaster2019/challenges/egg16/files/pngs/${png.value}.png"
  val bytes = assemblePNG(png)
  saveToFile(path, bytes)
}

def assemblePNG(root: Record): Array[Byte] = {
  List("png.head", "png.ihdr", "png.chrm", "png.gama", "png.bkgd", "png.phys", "png.idat", "png.text", "png.time", "png.iend")
    .flatMap(kind => assembleChunk(root, kind))
    .toArray
}

def assembleChunk(root: Record, kind: String): Array[Byte] = {
  records.filter(r => r.pid == root.id && r.kind == kind)
    .sortBy(_.ord)
    .flatMap { r => if (records.exists(_.pid == r.id)) assembleChunk(r, kind) else b64dec(r.value) }
    .toArray
}
```

The complete source code can be found [here](../../src/main/scala/hackyeaster2019/Egg16.scala).

As a result of running my program I got 11 PNG files assembled. Each one of them contained an egg. The correct one was stored in the file called `A strange car.png`.

### Egg

![egg.png](files/egg.png "egg.png")
