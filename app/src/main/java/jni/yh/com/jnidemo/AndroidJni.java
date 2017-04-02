package jni.yh.com.jnidemo;

/**
 * User: YangHai (1454025171@qq.com)
 * Date: 2017-04-02
 * Time: 09:37
 */

public class AndroidJni {
    static {
        System.loadLibrary("AndroidJni");
    }

    public native String getHelloWordText();

    public native String setUserName(String name);
}
