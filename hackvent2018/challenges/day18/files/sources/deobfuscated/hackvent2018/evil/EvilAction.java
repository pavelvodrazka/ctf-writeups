package hackvent2018.evil;

import hackvent2018.evil.EvilEvent;
import hackvent2018.evil.EvilImages;
import hackvent2018.evil.EvilType;
import hackvent2018.evil.NotEvil;
import java.awt.Component;
import java.util.Arrays;
import java.util.Iterator;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;

public class EvilAction {
   private byte[] b = new byte[]{(byte)-64, (byte)15, (byte)15, (byte)10, (byte)82, (byte)79, (byte)76, (byte)67, (byte)76};

   public String[] getMenu() {
      Iterator var2 = System.getenv().keySet().iterator();

      while(var2.hasNext()) {
         String u = (String)var2.next();
         if(Arrays.equals(this.b, this.xor(u.getBytes(), NotEvil.b))) {
            String[] t = new String[]{"No", "Go away", "Yes"};
            return t;
         }
      }

      String[] u1 = new String[]{"No", "Go away"};
      return u1;
   }

   public ImageIcon respond1(int answer) {
      switch(answer) {
      case 0:
         return EvilImages.getIcon(EvilType.NOTEVIL);
      case 1:
         return EvilImages.getIcon(EvilType.SAD);
      case 2:
         Iterator var3 = System.getenv().keySet().iterator();

         while(var3.hasNext()) {
            String s = (String)var3.next();
            if(Arrays.equals(this.b, this.xor(s.getBytes(), NotEvil.b))) {
               return EvilImages.getIcon(EvilType.EVIL);
            }
         }

         return EvilImages.getIcon(EvilType.NOTEVIL);
      default:
         return EvilImages.getIcon(EvilType.SAD);
      }
   }

   public void respond2(int answer) {
      if(answer == 2) {
         Iterator var3 = System.getenv().keySet().iterator();

         while(var3.hasNext()) {
            String s = (String)var3.next();
            if(Arrays.equals(this.b, this.xor(s.getBytes(), NotEvil.b))) {
               String[] buttons2 = new String[]{"Cool"};
               JOptionPane.showOptionDialog((Component)null, EvilEvent.eventResult(), "Evilist", -1, 1, (Icon)null, buttons2, buttons2[0]);
            }
         }
      }

   }

   private byte[] xor(byte[] c, byte[] b) {
      byte[] x = new byte[c.length];

      for(int i = 0; i < c.length; ++i) {
         x[i] = (byte)(c[i] ^ b[i]);
      }

      return x;
   }
}
