# Day 18: Be Evil

*Only today and for this challenge, please.*

 * Download [evil.jar](files/evil.jar)
 * java -jar evil.jar
 
Thanks to **scal** for the artwork!

### Solution

To start with the JAR file I wrote a simple program to decompile its classes using [Fernflower decompiler](https://github.com/JetBrains/intellij-community/tree/master/plugins/java-decompiler/engine).

```scala
extractJarFiles(workdir("evil.jar"), workdir("classes/original"), "class")
decompileClasses(workdir("classes/original"), workdir("sources/original"))

def decompileClasses(srcPath: Path, destPath: Path): Unit = {
  assert(Files.isDirectory(srcPath))
  assert(Files.isDirectory(destPath) || !Files.exists(destPath))

  Files.createDirectories(destPath)
  ConsoleDecompiler.main(Array("-log=WARN", srcPath.toString, destPath.toString))
}

def extractJarFiles(jarPath: Path, destPath: Path, ext: String): Unit = {
  assert(isFileWithExtension(jarPath, "jar"))

  val zipfs = FileSystems.newFileSystem(jarPath, null)
  val zipfsRoot = zipfs.getPath("/")
  Files.createDirectories(destPath)

  Files.walk(zipfsRoot).forEach(path => if (isFileWithExtension(path, ext)) {
    val fileZipPath = zipfsRoot.relativize(path)
    val fileDestPath = destPath.resolve(fileZipPath.toString)
    Files.createDirectories(fileDestPath.getParent)
    Files.copy(path, fileDestPath, StandardCopyOption.REPLACE_EXISTING)
  })
}

def isFileWithExtension(path: Path, ext: String): Boolean =
  Files.isRegularFile(path) && path.getFileName.toString.endsWith(s".$ext")

def workdir(subpath: String): Path =
  Paths.get("hackvent2018/challenges/day18/files/").resolve(subpath)
```

I got [extracted classes](files/classes/original) and [decompiled sources](files/sources/original) as the result.

As expected, some of the decompiled classes were obfuscated. They carried the actual bytecode in a byte array stored in a field called simply `b`. Loading of such classes was implemented in a custom classloader named [EvilLoader](files/sources/original/hackvent2018/evil/EvilLoader.java).

I extended my program to be able to deobfuscate such classes by unwrapping the byte array if it started with magic number `0xcafebabe` indicating there was a java class bytecode stored inside.

```scala
deobfuscateClasses(workdir("classes/original"), workdir("classes/deobfuscated"))
decompileClasses(workdir("classes/deobfuscated"), workdir("sources/deobfuscated"))

def deobfuscateClasses(srcPath: Path, destPath: Path): Unit = {
  assert(Files.isDirectory(srcPath))
  assert(Files.isDirectory(destPath) || !Files.exists(destPath))

  val classLoader = pathClassLoader(srcPath)
  Files.walk(srcPath).forEach(path => if (isFileWithExtension(path, "class")) {
    val relPath = srcPath.relativize(path)
    val className = relPath.getFileName.toString.replace(".class", "")

    val clazz = classLoader.loadClass(s"hackvent2018.evil.$className")
    val bytecode = getFieldValue[Array[Byte]](clazz, "b")
        .find(b => hex(b.slice(0, 4)) == "cafebabe")
        .getOrElse(Files.readAllBytes(path))

    val fileDestPath = destPath.resolve(relPath)
    Files.createDirectories(fileDestPath.getParent)
    Files.write(fileDestPath, bytecode)
  })
}

def pathClassLoader(dirPath: Path): ClassLoader = {
  assert(Files.isDirectory(dirPath))
  new PathClassLoader(dirPath)
}

def getFieldValue[T](clazz: Class[_], name: String): Option[T] =
  clazz.getFields.find(_.getName == "b").map(_.get(clazz).asInstanceOf[T])
```

Then I inspected [deobfuscated sources](files/sources/deobfuscated) and found the only important class named [EvilEvent](files/sources/deobfuscated/hackvent2018/evil/EvilEvent.java) which was hiding the flag from me.

To reveal the flag I simply called method `eventResult` through reflection on dynamically loaded class.

```scala
val evilClass = pathClassLoader(workdir("classes/deobfuscated")).loadClass("hackvent2018.evil.EvilEvent")
val flag = getDeclaredMethod(evilClass, "eventResult").get.invoke(null)
println(flag)

def getDeclaredMethod[T](clazz: Class[_], name: String): Option[Method] =
  clazz.getDeclaredMethods.find(m => m.getName == name).map(m => { m.setAccessible(true); m })
```

[This](../../src/main/scala/hackvent2018/Day18.scala) is the final version of my program. After running it I got the flag.

```
The flag is HV18-ztZB-nusz-r43L-wopV-ircY
```
