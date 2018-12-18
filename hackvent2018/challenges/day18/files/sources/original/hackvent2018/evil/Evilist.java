package hackvent2018.evil;

import hackvent2018.evil.EvilLoader;

public class Evilist {
   public static void main(String[] args) throws Exception {
      new EvilLoader(Evilist.class.getClassLoader());
      EvilLoader loader = new EvilLoader(Evilist.class.getClassLoader());
      Class clazz = loader.loadClass("hackvent2018.evil.EvilWindow");
      clazz.newInstance();
   }
}
