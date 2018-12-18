package hackvent2018.evil;

import hackvent2018.evil.Evil;
import hackvent2018.evil.NotEvil;
import hackvent2018.evil.Question;
import hackvent2018.evil.Sad;

public class EvilEvent {
   private static byte[] b = new byte[]{(byte)-83, (byte)8, (byte)119, (byte)19, (byte)73, (byte)17, (byte)2, (byte)83, (byte)126, (byte)17, (byte)33, (byte)119, (byte)115, (byte)6, (byte)38, (byte)16, (byte)26, (byte)23, (byte)10, (byte)127, (byte)20, (byte)85, (byte)81, (byte)47, (byte)13, (byte)88, (byte)43, (byte)0, (byte)70, (byte)27, (byte)-122, (byte)8, (byte)83, (byte)17, (byte)125, (byte)46, (byte)78, (byte)64, (byte)89, (byte)78, (byte)41};

   static String eventResult() {
      byte[] x = xor(b, NotEvil.b, 0);
      x = xor(x, Evil.b, 100);
      x = xor(x, Sad.b, 200);
      x = xor(x, Question.b, 300);
      return new String(x);
   }

   private static byte[] xor(byte[] c, byte[] b, int offset) {
      byte[] x = new byte[c.length];

      for(int i = 0; i < c.length; ++i) {
         x[i] = (byte)(c[i] ^ b[i + offset]);
      }

      return x;
   }
}
