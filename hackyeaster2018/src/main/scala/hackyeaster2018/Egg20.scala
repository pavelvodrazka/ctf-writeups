package hackyeaster2018

import java.io.File

import javax.sound.midi.{MidiEvent, MidiSystem, ShortMessage, Track}

object Egg20 {

  def main(args: Array[String]): Unit = {
    val midi = MidiSystem.getSequence(new File("hackyeaster2018/challenges/egg20/files/nonameyet.mid"))
    val tracks = midi.getTracks

    def eventsOf(track: Track): Seq[MidiEvent] =
      for (i <- 0 until track.size()) yield track.get(i)

    def messagesOf(track: Track): Seq[ShortMessage] =
      eventsOf(track).filter(_.getMessage.isInstanceOf[ShortMessage]).map(_.getMessage.asInstanceOf[ShortMessage])

    def secretOf(track: Track, cmdtype: Int): String =
      messagesOf(track).filter(_.getCommand == cmdtype).map(m => ascii(m.getData2)).mkString

    for ((track, i) <- tracks.zipWithIndex) {
      val secret = secretOf(track, ShortMessage.NOTE_ON)
      if (secret.nonEmpty) {
        printf("track %2d: %s\n", i, secret)
      }
    }
  }

}
