package hackvent2018.day24;

import java.util.Arrays;

public class Cipher3 {

    public static final int KEYSTREAM_LENGTH = 16;
    public static final int IV_LENGTH = 8;

    private static final int[] A = new int[] { 1295307597, -749914925, 886263092, 1295307597, -749914925, 886263092, 1295307597, -749914925 };

    private final int[] X = new int[8];
    private final int[] C = new int[8];
    private byte b = 0;
    private int keyindex = 0;
    private byte[] keystream = null;

    private final int rotl(int value, int shift) {
        return value << shift | value >>> 32 - shift;
    }

    public byte[] crypt(byte[] message) {
        int index = 0;

        while (index < message.length) {
            if (this.keystream == null || this.keyindex == 16) {
                this.keystream = this.keyStream();
                this.keyindex = 0;
            }

            while (this.keyindex < 16 && index < message.length) {
                int var10001 = index++;
                message[var10001] ^= this.keystream[this.keyindex];
                ++this.keyindex;
            }
        }

        return message;
    }

    private byte[] keyStream() {
        this.nextState();
        byte[] s = new byte[16];
        int x = this.X[0] & '\uffff' ^ this.X[5] >>> 16;
        s[0] = (byte) (x & 255);
        s[1] = (byte) (x >> 8);
        x = this.X[3] & '\uffff' ^ this.X[0] >>> 16;
        s[2] = (byte) (x & 255);
        s[3] = (byte) (x >> 8);
        x = this.X[2] & '\uffff' ^ this.X[7] >>> 16;
        s[4] = (byte) (x & 255);
        s[5] = (byte) (x >> 8);
        x = this.X[5] & '\uffff' ^ this.X[2] >>> 16;
        s[6] = (byte) (x & 255);
        s[7] = (byte) (x >> 8);
        x = this.X[4] & '\uffff' ^ this.X[1] >>> 16;
        s[8] = (byte) (x & 255);
        s[9] = (byte) (x >> 8);
        x = this.X[7] & '\uffff' ^ this.X[4] >>> 16;
        s[10] = (byte) (x & 255);
        s[11] = (byte) (x >> 8);
        x = this.X[6] & '\uffff' ^ this.X[3] >>> 16;
        s[12] = (byte) (x & 255);
        s[13] = (byte) (x >> 8);
        x = this.X[1] & '\uffff' ^ this.X[6] >>> 16;
        s[14] = (byte) (x & 255);
        s[15] = (byte) (x >> 8);
        return s;
    }

    private void nextState() {
        for (int j = 0; j < 8; ++j) {
            long t = ((long) this.C[j] & 4294967295L) + ((long) A[j] & 4294967295L) + (long) this.b;
            this.b = (byte) ((int) (t >>> 32));
            this.C[j] = (int) (t & -1L);
        }

        int[] G = new int[8];

        for (int j = 0; j < 8; ++j) {
            long t = (long) (this.X[j] + this.C[j]) & 4294967295L;
            t *= t;
            G[j] = (int) (t & -1L ^ t >>> 32);
        }

        this.X[0] = G[0] + this.rotl(G[7], 16) + this.rotl(G[6], 16);
        this.X[1] = G[1] + this.rotl(G[0], 8) + G[7];
        this.X[2] = G[2] + this.rotl(G[1], 16) + this.rotl(G[0], 16);
        this.X[3] = G[3] + this.rotl(G[2], 8) + G[1];
        this.X[4] = G[4] + this.rotl(G[3], 16) + this.rotl(G[2], 16);
        this.X[5] = G[5] + this.rotl(G[4], 8) + G[3];
        this.X[6] = G[6] + this.rotl(G[5], 16) + this.rotl(G[4], 16);
        this.X[7] = G[7] + this.rotl(G[6], 8) + G[5];
    }

    public void reset() {
        this.b = 0;
        this.keyindex = 0;
        this.keystream = null;
        Arrays.fill(this.X, 0);
        Arrays.fill(this.C, 0);
    }

    public void setupIV(byte[] IV) {
        short[] sIV = new short[IV.length >> 1];

        for (int i = 0; i < sIV.length; ++i) {
            sIV[i] = (short) (IV[2 * i + 1] << 8 | (short) IV[2 * i] & 255);
        }

        this.setupIV(sIV);
    }

    public void setupIV(short[] iv) {
        int[] var10000 = this.C;
        var10000[0] ^= iv[1] << 16 | iv[0] & '\uffff';
        var10000 = this.C;
        var10000[1] ^= iv[3] << 16 | iv[1] & '\uffff';
        var10000 = this.C;
        var10000[2] ^= iv[3] << 16 | iv[2] & '\uffff';
        var10000 = this.C;
        var10000[3] ^= iv[2] << 16 | iv[0] & '\uffff';
        var10000 = this.C;
        var10000[4] ^= iv[1] << 16 | iv[0] & '\uffff';
        var10000 = this.C;
        var10000[5] ^= iv[3] << 16 | iv[1] & '\uffff';
        var10000 = this.C;
        var10000[6] ^= iv[3] << 16 | iv[2] & '\uffff';
        var10000 = this.C;
        var10000[7] ^= iv[2] << 16 | iv[0] & '\uffff';
        this.nextState();
        this.nextState();
        this.nextState();
        this.nextState();
    }

    public void setupKey(byte[] key) {
        short[] sKey = new short[key.length >> 1];

        for (int i = 0; i < sKey.length; ++i) {
            sKey[i] = (short) (key[2 * i + 1] << 8 | (short) key[2 * i] & 255);
        }

        this.setupKey(sKey);
    }

    public void setupKey(short[] key) {
        this.X[0] = key[1] << 16 | key[0] & '\uffff';
        this.X[1] = key[6] << 16 | key[5] & '\uffff';
        this.X[2] = key[3] << 16 | key[2] & '\uffff';
        this.X[3] = key[0] << 16 | key[7] & '\uffff';
        this.X[4] = key[5] << 16 | key[4] & '\uffff';
        this.X[5] = key[2] << 16 | key[1] & '\uffff';
        this.X[6] = key[7] << 16 | key[6] & '\uffff';
        this.X[7] = key[4] << 16 | key[3] & '\uffff';
        this.C[0] = key[4] << 16 | key[5] & '\uffff';
        this.C[1] = key[1] << 16 | key[2] & '\uffff';
        this.C[2] = key[6] << 16 | key[7] & '\uffff';
        this.C[3] = key[3] << 16 | key[4] & '\uffff';
        this.C[4] = key[0] << 16 | key[1] & '\uffff';
        this.C[5] = key[5] << 16 | key[6] & '\uffff';
        this.C[6] = key[2] << 16 | key[3] & '\uffff';
        this.C[7] = key[7] << 16 | key[0] & '\uffff';
        this.nextState();
        this.nextState();
        this.nextState();
        this.nextState();
        int[] var10000 = this.C;
        var10000[0] ^= this.X[4];
        var10000 = this.C;
        var10000[1] ^= this.X[5];
        var10000 = this.C;
        var10000[2] ^= this.X[6];
        var10000 = this.C;
        var10000[3] ^= this.X[7];
        var10000 = this.C;
        var10000[4] ^= this.X[0];
        var10000 = this.C;
        var10000[5] ^= this.X[1];
        var10000 = this.C;
        var10000[6] ^= this.X[2];
        var10000 = this.C;
        var10000[7] ^= this.X[3];
    }

}
