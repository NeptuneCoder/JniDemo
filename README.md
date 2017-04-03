这是一个调用JNI的demo,记录jni技术相关的知识点，为以后的学习做好笔记；
----
整体描述：

声明含有native描述的方法的java类，通过对应的.class文件生成C/C++的头文件（头文件是一种包含功能函数、数据接口声明的载体文件）。
然后在main目录下新建一个文件夹（文件夹名字随意,项目中该目录名称为jni），将生成的头文件copy该目录下，再定义Android.mk和Application.mk文件（具体含义查阅文档，项目中已经写好了）
这个时候新建C/C++文件，就可以实现自己定义的方法体了。最后就需要配置自己的ndk环境和gradle.properties文件中android.useDeprecatedNdk = true属性值。
在main目录下，使用ndk-build命令编译生成对应的so文件。最后将生成的so文件copy到android stdio工程中默认的jniLibs目录下就ok了。

------
具体实现步骤如下：
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
以上为基础内容.
 
 [参考资料1](http://www.jianshu.com/p/aba734d5b5cd)
 
 [参考资料2](http://www.cnblogs.com/eddy-he/archive/2012/08/08/2628676.html)
 
 [参考资料3](http://www.cnblogs.com/wi100sh/p/5178668.html)
 
 [参考资料4](http://www.xpabc.com/xpabc/article/show/189.htm)
 
 [android开发艺术探究14章]()
