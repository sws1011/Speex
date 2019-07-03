package com.speex.jni;

/**
 * Created by shiwenshui 2019/5/13 16:54
 */
public class Speex {

    /* quality
     * 1 : 4kbps (very noticeable artifacts, usually intelligible)
     * 2 : 6kbps (very noticeable artifacts, good intelligibility)
     * 4 : 8kbps (noticeable artifacts sometimes)
     * 6 : 11kpbs (artifacts usually only noticeable with headphones)
     * 8 : 15kbps (artifacts not usually noticeable)
     */
    private static final int DEFAULT_COMPRESSION = 4;

    public Speex() {
    }

    public int init() {
        load();
        return init(DEFAULT_COMPRESSION);
    }

    private void load() {
        try {
            System.loadLibrary("speex-lib");
        } catch (Throwable e) {
            e.printStackTrace();
        }
    }

    public native int init(int compression);

    public native int getFrameSize();

    public native int encode(short lin[], int offset, byte encoded[], int size);

    public native int decode(byte encoded[], short out[], int size);

    public native int free();

}
