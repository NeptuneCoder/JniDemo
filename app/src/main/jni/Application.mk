#指定编译那些cpu类型的so文件
APP_ABI := armeabi,x86,x86_64,mips64,armeabi-v7a,arm64-v8a
APP_STL:=c++_static
APP_CFLAGS   += -DHAVE_PTHREADS -DHAVE_ANDROID_OS=1
APP_CXXFLAGS += -DHAVE_PTHREADS -DHAVE_ANDROID_OS=1