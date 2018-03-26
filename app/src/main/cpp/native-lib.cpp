#include <jni.h>
#include <string>

#include <android/log.h>
#include <android/log.h>

#define  LOG_TAG    "===test==="
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

using namespace std;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_gzb_jnitest_NativeUtil_stringFromJNI(JNIEnv *env, jobject instance) {
    /**
     * 第一个参数JNIEnv是指向可用JNI函数表的接口指针
     * 第二个参数jobject是工具类的Java对象引用
     */

    /*1.JNIEnv接口指针*/
    //C代码
    //return (*env)->NewStringUTF(env,"Hello from JNI !");

    //C++
    return env->NewStringUTF("hello");

    /*2.实例方法与静态方法*/
    //实例方法
    //(JNIEnv * env,jobject thiz);
    //静态方法,因为静态方法没有与实例绑定，因此通过第二个参数获取类引用而不是实例引用
    //(JNIEnv * env,jclass clazz);

}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_gzb_jnitest_NativeUtil_stringCreate(JNIEnv *env, jclass type) {

    /**
     * 字符串操作
     */
    //1.创建字符串
    jstring javaString;
    javaString = env->NewStringUTF("Hello World!");

    //2.把Java字符串转换成C++字符串
    const char *str;
    jboolean *isCopy;
    str = env->GetStringUTFChars(javaString, isCopy);
    if (0 != str) {
        LOGD("Java string");

        if (0 == isCopy) {
            LOGD("C string is a copy of the Java string.");
        } else {
            LOGD("C string points to actual string.");
        }
    }

    //3.释放字符串
    env->ReleaseStringUTFChars(javaString, str);

    return env->NewStringUTF(str);


}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_gzb_jnitest_NativeUtil_testArray(JNIEnv *env, jclass type) {
    /**
     * 数组操作
     */

    //1.创建数组
    jintArray javaArray;
    javaArray = env->NewIntArray(10);
    if (0 != javaArray) {
        LOGD("array...");
    }

    //2.访问数组元素
    //将数组的代码复制成c++数组或者让JNI提供直接指向数组元素的指针

    //3.对副本的操作
    jint nativeArray[10];
    //将java数组区复制到C++数组中
    env->GetIntArrayRegion(javaArray,0,10,nativeArray);
    //从C++数组向Java数组提交所做的修改
    env->SetIntArrayRegion(javaArray,0,10,nativeArray);

    //4.对直接指针的操作
    jint* nativeDirectArray;
    jboolean isCopy;
    //获取指向Java数组元素的直接指针
    nativeDirectArray = env->GetIntArrayElements(javaArray,&isCopy);
    //释放指向Java数组元素的直接指针
    env->ReleaseIntArrayElements(javaArray,nativeDirectArray,0);


    return env->NewStringUTF("hello");
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_gzb_jnitest_NativeUtil_testNIO(JNIEnv *env, jclass type) {
    /**
     * NIO操作
     */
    //1.创建直接字节缓冲区
    //基于给定的字节数组创建字节缓冲区
    unsigned char* buffer = new unsigned char[1024];

    jobject directBuffer;
    directBuffer = env->NewDirectByteBuffer(buffer,1024);

    //2.直接字节缓冲区获取
    //通过Java字节缓冲区获取原声字节数组
    unsigned char* buffer2;
    buffer2 = (unsigned char *) env->GetDirectBufferAddress(directBuffer);

    return env->NewStringUTF("hello");
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_gzb_jnitest_NativeUtil_testJObject(JNIEnv *env, jobject instance) {
    /**
     * 访问域：实力域和静态域
     */
    //1.获取域ID
    //用对象引用获得类
    jclass  clazz;
    clazz = env->GetObjectClass(instance);

    //获取实例域的域ID
    jfieldID instanceFieldId;
    instanceFieldId = env->GetFieldID(clazz,"instanceField","Ljava/lang/String;");

    //获取静态域的域ID
    jfieldID  staticFieldId;
    staticFieldId = env->GetStaticFieldID(clazz,"staticField","Ljava/lang/String");

    /*两个函数最后一个参数是Java中表示鱼类性的域描述符*/

    //2.获取域
    //获得实例域
    jstring instanceField;
    instanceField = (jstring) env->GetObjectField(instance, instanceFieldId);

    //获得静态域
    jstring staticField;
    staticField = (jstring) env->GetStaticObjectField(clazz, staticFieldId);


    return env->NewStringUTF("hello");
}