package hackvent2018

import java.lang.reflect.Method
import java.nio.file._

import com.github.marschall.pathclassloader.PathClassLoader
import org.jetbrains.java.decompiler.main.decompiler.ConsoleDecompiler

object Day18 extends App {

  extractJarFiles(workdir("evil.jar"), workdir("classes/original"), "class")
  decompileClasses(workdir("classes/original"), workdir("sources/original"))
  deobfuscateClasses(workdir("classes/original"), workdir("classes/deobfuscated"))
  decompileClasses(workdir("classes/deobfuscated"), workdir("sources/deobfuscated"))

  val evilClass = pathClassLoader(workdir("classes/deobfuscated")).loadClass("hackvent2018.evil.EvilEvent")
  val flag = getDeclaredMethod(evilClass, "eventResult").get.invoke(null)
  println(flag)

  def decompileClasses(srcPath: Path, destPath: Path): Unit = {
    assert(Files.isDirectory(srcPath))
    assert(Files.isDirectory(destPath) || !Files.exists(destPath))

    Files.createDirectories(destPath)
    ConsoleDecompiler.main(Array("-log=WARN", srcPath.toString, destPath.toString))
  }

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

  def pathClassLoader(dirPath: Path): ClassLoader = {
    assert(Files.isDirectory(dirPath))
    new PathClassLoader(dirPath)
  }

  def getFieldValue[T](clazz: Class[_], name: String): Option[T] =
    clazz.getFields.find(_.getName == "b").map(_.get(clazz).asInstanceOf[T])

  def getDeclaredMethod[T](clazz: Class[_], name: String): Option[Method] =
    clazz.getDeclaredMethods.find(m => m.getName == name).map(m => { m.setAccessible(true); m })

  def isFileWithExtension(path: Path, ext: String): Boolean =
    Files.isRegularFile(path) && path.getFileName.toString.endsWith(s".$ext")

  def workdir(subpath: String): Path =
    Paths.get("hackvent2018/challenges/day18/files/").resolve(subpath)

}
