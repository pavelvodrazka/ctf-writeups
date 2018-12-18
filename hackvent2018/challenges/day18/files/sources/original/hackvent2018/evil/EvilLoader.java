package hackvent2018.evil;

public class EvilLoader extends ClassLoader {
   public EvilLoader(ClassLoader parent) {
      super(parent);
   }

   private Class getClass(String name) throws ClassNotFoundException {
      byte[] b = this.loadEvilClass(name);
      return this.defineClass(name, b, 0, b.length);
   }

   public Class loadClass(String name) throws ClassNotFoundException {
      try {
         try {
            return this.getClass(name);
         } catch (ClassFormatError var3) {
            return super.loadClass(name);
         }
      } catch (ClassNotFoundException var4) {
         return super.loadClass(name);
      }
   }

   private byte[] loadEvilClass(String name) throws ClassNotFoundException {
      Class clazz = EvilLoader.class.getClassLoader().loadClass(name);

      try {
         byte[] e1 = (byte[])clazz.getField("b").get(clazz);
         return e1;
      } catch (IllegalAccessException | NoSuchFieldException | SecurityException | ClassFormatError | IllegalArgumentException var4) {
         throw new ClassNotFoundException(var4.toString());
      }
   }
}
