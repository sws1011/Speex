#include <jni.h>
#include <string>
#include "include/speex/speex.h"

#ifdef __cplusplus
extern "C" {
#endif

SpeexBits enBits, deBits;
bool initFlag;

void *enc_state;                // 编码器状态
void *dec_state;                // 解码器状态

int dec_frame_size;
int enc_frame_size;

extern "C"
JNIEXPORT jint JNICALL
Java_com_speex_jni_Speex_init(JNIEnv *env, jobject instance, jint compression) {

    if (initFlag) {
        return -1;
    }
    initFlag = true;

    speex_bits_init(&enBits);

    speex_bits_init(&deBits);

    int temp = 0;
    // 初始化编码器
    enc_state = speex_encoder_init(&speex_nb_mode);
    // 初始化解码器
    dec_state = speex_decoder_init(&speex_nb_mode);

    temp = compression;
    speex_encoder_ctl(enc_state, SPEEX_SET_QUALITY, &temp);  // 设置压缩质量(0~10)
    speex_encoder_ctl(enc_state, SPEEX_GET_FRAME_SIZE, &enc_frame_size);
    speex_decoder_ctl(dec_state, SPEEX_GET_FRAME_SIZE, &dec_frame_size);

    return 1;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_speex_jni_Speex_getFrameSize(JNIEnv *env, jobject instance) {
    if (!initFlag) {
        return -1;
    }

    return enc_frame_size;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_speex_jni_Speex_decode(JNIEnv *env, jobject instance, jbyteArray encoded_, jshortArray lin_, jint size) {

    if (!initFlag)
        return -1;

    jbyte *encoded = env->GetByteArrayElements(encoded_, NULL);
    jshort *out = env->GetShortArrayElements(lin_, NULL);

    jsize encoded_length = size;

    speex_bits_read_from(&deBits, reinterpret_cast<char *>(encoded), encoded_length);

    speex_decode_int(dec_state, &deBits, out);

    env->ReleaseByteArrayElements(encoded_, encoded, 0);

    env->ReleaseShortArrayElements(lin_, out, 0);

    return (jint) dec_frame_size;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_speex_jni_Speex_encode(JNIEnv *env, jobject instance, jshortArray lin_, jint offset, jbyteArray encoded_,
                                jint size) {
    if (!initFlag)
        return -1;

    jshort buffer[enc_frame_size];

    jshort *lin = env->GetShortArrayElements(lin_, NULL);
    jbyte *encoded = env->GetByteArrayElements(encoded_, NULL);

    int nsamples = (size - 1) / enc_frame_size + 1;
    int i, tot_bytes = 0;
    speex_bits_reset(&enBits);

    for (i = 0; i < nsamples; i++) {
        env->GetShortArrayRegion(lin_, offset + i * enc_frame_size, enc_frame_size, buffer);
        speex_encode_int(enc_state, buffer, &enBits);
    }

    tot_bytes = speex_bits_write(&enBits, (char *) encoded, enc_frame_size);
    env->SetByteArrayRegion(encoded_, 0, tot_bytes, encoded);

    env->ReleaseShortArrayElements(lin_, lin, 0);
    env->ReleaseByteArrayElements(encoded_, encoded, 0);

    return (jint) tot_bytes;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_speex_jni_Speex_free(JNIEnv *env, jobject instance) {

    if (!initFlag)
        return -1;

    speex_bits_destroy(&enBits);
    speex_bits_destroy(&deBits);
    speex_decoder_destroy(dec_state);
    speex_encoder_destroy(enc_state);
    initFlag = false;
    return 1;
}

#ifdef __cplusplus
}
#endif