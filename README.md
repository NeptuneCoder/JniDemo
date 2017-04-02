这是一个调用JNI的demo,记录jni技术相关的知识点，为以后的学习做好笔记；

1. 新建含有native方法的java类；
2. 生成对应的头文件
```
//到该
app/build/intermediates/classes/debug
//目录下：
//使用
javah -d jni jni.yh.com.jnidemo.AndroidJni
//生成头文件
javah -d jni 完整的包名+类名
```
3. 在mian目录下新建名为jni的文件夹
4. 将生成的头文件copy该目录下
5. 新建具体的实现类AdroidJni.cpp
6. 新建Android.mk,该文件指定要编译的C源文件和生成的库名，这两个很重要
```
LOCAL_MODULE    := AndroidJni
LOCAL_SRC_FILES := AndroidJni.cpp
```
7. Application.mk 该文件定义生成那些cup类型的so文件
```
APP_ABI := armeabi,x86,x86_64,mips64,armeabi-v7a,arm64-v8a
```

8. 在local.properties中培训ndk路径，需要配置在环境变量中
```
ndk.dir=/Users/yh/Documents/android-sdk/android-ndk-r11c
```

9. 使用ndk-build 编译需要的so文件
在jni 的父目录中，使用ndk-build命令，即可生成所有版本的的so文件

10. 将生成的so文件，copy到jniLibs目录中；

11. 配置gradle.properties 中如下参数
```
android.useDeprecatedNdk = true
```
12. 在java代码中如下使用
```
final AndroidJni androidJni = new AndroidJni();
        contentTv.setText(androidJni.getHelloWordText());

        contentTv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, androidJni.setUserName("yanghai"), Toast.LENGTH_LONG).show();
            }
        });

```
创建AndroidJni类型的对象，然后调用定义的方法。


注意：生成的头文件是由包名+类名+方面名组成的。
以后问基础内容.
