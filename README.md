这是一个调用JNI的demo,记录jni技术相关的知识点，为以后的学习做好笔记；
----
整体描述：

声明含有native描述的方法的java类，通过对应的.class文件生成C/C++的头文件（头文件是一种包含功能函数、数据接口声明的载体文件）。
然后在main目录下新建一个文件夹（文件夹名字随意,项目中该目录名称为jni），将生成的头文件copy该目录下，再定义Android.mk和Application.mk文件（具体含义查阅文档，项目中已经写好了）
这个时候新建C/C++文件，就可以实现自己定义的方法体了。最后就需要配置自己的ndk环境和gradle.properties文件中android.useDeprecatedNdk = true属性值。
在main目录下，使用ndk-build命令编译生成对应的so文件。最后将生成的so文件copy到android stdio工程中默认的jniLibs目录下就ok了。

------
具体实现步骤如下：
1. 新建含有native方法的java类；(编译成对应的.class文件)
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
在这里需要注意的是，生成的头文件在app/build/intermediates/classes/debug/jni目录下面；

3. 在main目录下新建名为jni的文件夹（jni名词可修改，如果修改的话，需要在gradle里面的配置，不然会出现找不到文件的情况）
4. 将生成的头文件copy该目录下
5. 新建具体的实现类AdroidJni.cpp
6. 新建Android.mk,该文件指定要编译的C源文件和生成的库名，这两个参数很重要，[如果是编译多个文件](#user-jump)
```
LOCAL_MODULE    := AndroidJni
LOCAL_SRC_FILES := AndroidJni.cpp
```
7. Application.mk 该文件定义生成那些cup类型的so文件，或者配置参数为 APP_ABI := all(全部的CPU类型)
```
APP_ABI := armeabi,x86,x86_64,mips64,armeabi-v7a,arm64-v8a
```

8. 在local.properties中培训ndk路径，需要配置在环境变量中
[ndk 的下载地址](https://developer.android.com/ndk/downloads/index.html?hl=zh-cn)
```
ndk.dir=/Users/yh/Documents/android-sdk/android-ndk-r11c
```

9. 使用ndk-build命令，生成需要的so文件
在jni 的父目录中（一般就是main目录下），使用ndk-build命令，即可生成所有版本的的so文件
注：如果ndk-build命令找不到，需要配置一下环境变量
 
 这个时候，工作已经完成的差不多了。只需要把生成的so文件copy工程中，就可以开始使用了。
 
10. 将生成的so文件，copy到jniLibs目录中；（jniLibs如果没有，在main目录下创建，该目录android stdio 中存放so文件的默认的位置）

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
                Toast.makeText(MainActivity.this, androidJni.setUserName("yh"), Toast.LENGTH_LONG).show();
            }
        });

```
创建AndroidJni类型的对象，然后调用定义的方法。


注意：生成的头文件是由包名+类名+方面名组成的。
以上为基础内容.
 
 [参考资料1](http://www.jianshu.com/p/aba734d5b5cd)
 
 [参考资料2](http://www.cnblogs.com/eddy-he/archive/2012/08/08/2628676.html)
 
 [参考资料3](http://www.cnblogs.com/wi100sh/p/5178668.html)
 
 [参考资料4](http://www.xpabc.com/xpabc/article/show/189.htm)
 
 [android开发艺术探究14章]()


#### 二 <h5 id = "user-jump">编译多个源文件</h5>
需要在android.mk 文件中的LOCAL_SRC_FILES :的值通过 空格 + \ + 空格 +新增加要编译的文件，如下：
 ```
LOCAL_SRC_FILES := AndroidJni.cpp \ TestInclude.cpp
```
[参考资料](http://www.eoeandroid.com/blog-1179893-48781.html)

#### 三
在编译工程时，如果需要依赖完整的C++库需要在Application.mk文件中配置如下：

```
APP_STL:=c++_static
LOCAL_CPPFLAGS  += -std=c++11
```

[参考资料](http://stackoverflow.com/questions/32188853/ndk-not-identifying-certain-header-files-like-mutex-and-future)


#### 四 应用项目中的配置 
 由于在应用项目中，使用到了C++的完整库，Application.mk配置如下
 ```
 #指定编译那些cpu类型的so文件
 #armeabi,x86,x86_64,armeabi-v7a,arm64-v8a
 
 #下面代码片段编译的so文件 mutex no such file or directory
 APP_ABI := armeabi,x86,x86_64,armeabi-v7a,arm64-v8a
 
 APP_STL:=c++_static
 APP_STL:=gnustl_static
 
 APP_CFLAGS   += -DHAVE_PTHREADS -DHAVE_ANDROID_OS=1
 APP_CXXFLAGS += -DHAVE_PTHREADS -DHAVE_ANDROID_OS=1
 
 
 APP_CPPFLAGS += -std=c++11
 #NDK 为 libc++ 提供了预建的静态和共享库，但您也可以在构建之前将以下行添加到 Application.mk 文件或者在环境中设置它，强制 NDK 从来源构建 libc++：
 LIBCXX_FORCE_REBUILD := true
 ```
 
 Android.mk 配置如下：
 ```
 LOCAL_PATH := $(call my-dir)
 
 include $(CLEAR_VARS)
 
 LOCAL_MODULE    := http-jni
 LOCAL_SRC_FILES := HttpJni.cpp \ Socket.hpp
 LOCAL_LDLIBS += -llog
 
 include $(BUILD_SHARED_LIBRARY)

 ```
 心得：如果需要一些特殊的库，需要在Android.mk 或Application.mk里面配置。
