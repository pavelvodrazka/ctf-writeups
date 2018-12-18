package hackvent2018.evil;

import hackvent2018.evil.EvilWindow;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class EvilHandler implements MouseListener {
   private EvilWindow ew;

   public EvilHandler(EvilWindow ew) {
      this.ew = ew;
   }

   public void mouseClicked(MouseEvent e) {
      this.ew.ask();
   }

   public void mousePressed(MouseEvent e) {
   }

   public void mouseReleased(MouseEvent e) {
   }

   public void mouseEntered(MouseEvent e) {
   }

   public void mouseExited(MouseEvent e) {
   }
}
