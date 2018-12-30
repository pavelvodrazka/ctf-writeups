package hackvent2018.day24;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class RedPill {

    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.out.println("java -jar redpill.jar <red pill serial number> \n");
            System.exit(0);
        }

        if (!args[0].matches("[0-9]{2}-[0-9]{3}-[0-9]{3}")) {
            System.out.println("That's not a red pill");
            System.exit(0);
        }

        byte[] iv = args[0].replace("-", "").getBytes();
        byte[] k = new byte[16];
        System.arraycopy(iv, 0, k, 0, 8);
        System.arraycopy(iv, 0, k, 8, 8);
        byte[] b = Files.readAllBytes((new File("flag")).toPath());
        byte[] f = new byte[(b.length + 1) / 2];

        for (int i = 0; i < b.length; ++i) {
            if (i % 2 == 0) {
                f[i / 2] = (byte) (f[i / 2] | b[i] << 4);
            } else {
                f[i / 2] = (byte) (f[i / 2] | b[i] & 15);
            }
        }

        Cipher3 c = new Cipher3();
        c.setupKey(k);
        c.setupIV(iv);
        byte[] fc = c.crypt(f);
        Files.write((new File("flag_encrypted")).toPath(), fc);
    }

}
