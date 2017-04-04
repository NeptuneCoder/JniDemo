//
// Created by yanghai on 17/4/2.
//
#include <string.h>
#include <jni.h>
#include "jni_yh_com_jnidemo_AndroidJni.h"
#include "TestInclude.h"

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/HelloJni/HelloJni.java
 */
//char *Jstring2CStr(JNIEnv *env, jstring jstr);

JNIEXPORT jstring JNICALL
Java_jni_yh_com_jnidemo_AndroidJni_getHelloWordText(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("Hello from JNI ，hello yh!");
}

JNIEXPORT jstring JNICALL
Java_jni_yh_com_jnidemo_AndroidJni_setUserName(JNIEnv *env, jobject thiz, jstring jstr) {
//    const char * str_buf = env->GetStringChars(result);
//    printf("constent is %s", str_buf);
//    int result1 = TestInclude::add(2, 3);
//    char *re = 't';
//    char *cstr = Jstring2CStr(env, jstr);
//    char *result1 = 'W';
//    strcat(cstr, result1); //拼接两个字符串
//    return env->NewStringUTF(cstr);
//    char buf[128];
//    const char *str;
//    str = env->GetStringUTFChars(jstr, NULL);
//    if (str == NULL) { //不要忘记检测，否则分配内存失败会抛出异常
//        return NULL; /* OutOfMemoryError already thrown */
//    }
////    printf("%s", str);
//
//    env->ReleaseStringUTFChars(jstr, str);
//
//    /* We assume here that the user does not type more than  * 127 characters */
//    scanf("%s", buf);
    return env->NewStringUTF("this is test code");

}


/**

* 工具方法

* 作用: 把java中的string 转化成一个c语言中的char数组

* 接受的参数 envjni环境的指针

* jstr 代表的是要被转化的java的string 字符串

* 返回值 : 一个c语言中的char数组的首地址 (char 字符串)

*/

//char *Jstring2CStr(JNIEnv *env, jstring jstr) {
//    char *rtn = NULL;
//    jclass clsstring = env->FindClass(env, "java/lang/String");
//
//    jstring strencode = env->NewStringUTF(env, "GB2312");
//
//    jmethodID mid =
//            env->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
//
//// String.getByte("GB2312");
//
//    jbyteArray barr =
//
//            (jbyteArray) env->CallObjectMethod(env, jstr, mid, strencode);
//
//    jsize alen = env->GetArrayLength(env, barr);
//
//    jbyte *ba = env->GetByteArrayElements(env, barr, JNI_FALSE);
//
//    if (alen > 0) {
//
//        rtn = (char *) malloc(alen + 1); //"\0"
//
//        memcpy(rtn, ba, alen);
//
//        rtn[alen] = 0;
//
//    }
//
//    env->ReleaseByteArrayElements(env, barr, ba, 0); //
//
//    return rtn;
//}