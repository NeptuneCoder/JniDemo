//
// Created by yanghai on 17/4/2.
//
#include <string.h>
#include <jni.h>
#include "jni_yh_com_jnidemo_AndroidJni.h"
/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/HelloJni/HelloJni.java
 */
JNIEXPORT jstring JNICALL
Java_jni_yh_com_jnidemo_AndroidJni_getHelloWordText(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("Hello from JNI ，hello yh!");
}

JNIEXPORT jstring JNICALL
Java_jni_yh_com_jnidemo_AndroidJni_setUserName(JNIEnv *env, jobject thiz, jstring result) {
//    const char * str_buf = env->GetStringChars(result);
//    printf("constent is %s", str_buf);
    return env->NewStringUTF("this  is  have param method!");

}