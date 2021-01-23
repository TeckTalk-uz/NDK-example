#include <jni.h>
#include <string>
#include <vector>


unsigned char key[] = {4, 2, 9, 4, 9, 6, 7, 2, 9, 5};

static std::string base64_encode(const std::string &in) {

    std::string out;

    int val = 0, valb = -6;
    for (u_char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[
                                  (val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6)
        out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[
                              ((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

static std::string base64_decode(const std::string &in) {

    std::string out;

    std::vector<int> T(256, -1);

    for (int i = 0; i < 64; i++)
        T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    int val = 0, valb = -8;
    for (u_char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

std::string applyXor(std::string sequence) {
    int maxIndex = sizeof(key) - 1;

    std::string result = sequence;
    size_t sequenceSize = sequence.size();

    int keyIndex = 0;

    for (int i = 0; i < sequenceSize; i++) {
        if (keyIndex > maxIndex)
            keyIndex = 0;

        result[i] = sequence[i] ^ key[keyIndex++];
    }

    return result;
}

extern "C" {

JNIEXPORT jstring JNICALL
Java_mr_adkhambek_ndk_SecurityActivity_encrypt(
        JNIEnv *env,
        jobject instance,
        jstring plainText_
) {
    const char *plainText = env->GetStringUTFChars(plainText_, 0);

    std::string sequence = applyXor(plainText);
    size_t sequenceSize = sequence.size();

    reverse(sequence.begin(), sequence.end());

    int code = 0;

    for (unsigned long i = 0; i < sequenceSize; i++) {
        code = sequence[i] + 5;
        sequence[i] = (char) code;
    }

    env->ReleaseStringUTFChars(plainText_, plainText);

    return env->NewStringUTF(base64_encode(sequence).c_str());
}

JNIEXPORT jstring JNICALL
Java_mr_adkhambek_ndk_SecurityActivity_decrypt(
        JNIEnv *env,
        jobject instance,
        jstring ciphertext_
) {
    const char *ciphertext = env->GetStringUTFChars(ciphertext_, 0);

    std::string sequence = base64_decode(ciphertext);
    size_t sequenceSize = sequence.size();

    int code;
    for (int i = 0; i < sequenceSize; i++) {
        code = sequence[i] - 5;
        sequence[i] = (char) code;
    }

    reverse(sequence.begin(), sequence.end());

    env->ReleaseStringUTFChars(ciphertext_, ciphertext);

    return env->NewStringUTF(applyXor(sequence).c_str());
}
}

