//
// Created by Adkhambek on 23/01/21.
//

#include <jni.h>
#include <string>
#include <android/log.h>

#define  LOG_TAG    "NDK_TEST"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


#define J_PACKAGE(METHOD_NAME) Java_mr_adkhambek_ndk_Store_##METHOD_NAME
#define J_EXPORT(RETURN, METHOD_NAME) extern "C" JNIEXPORT RETURN JNICALL J_PACKAGE(METHOD_NAME)

#define JNI_METHOD1(RETURN, METHOD_NAME) J_EXPORT(RETURN, METHOD_NAME)(JNIEnv *env, jobject thizz)
#define JNI_METHOD2(RETURN, METHOD_NAME, ...) J_EXPORT(RETURN, METHOD_NAME)(JNIEnv *env, jobject thizz, __VA_ARGS__)


JNI_METHOD1(jint, intFromJNI) {
    return 4;
}

JNI_METHOD1(jstring, stringFromJNI) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNI_METHOD2(jint, calculateFromJNI, jint a, jint b) {
    return a + b;
}

JNI_METHOD1(jobject, objectFromJNI) {
    std::string hello = "Adam";

    jclass clazz = env->FindClass("mr/adkhambek/ndk/User");
    jmethodID constructorId = env->GetMethodID(clazz, "<init>", "(Ljava/lang/String;)V");
    jobject userObject = env->NewObject(clazz, constructorId, env->NewStringUTF(hello.c_str()));

    return userObject;
}