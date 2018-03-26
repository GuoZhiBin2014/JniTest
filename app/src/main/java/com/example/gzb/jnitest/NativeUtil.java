package com.example.gzb.jnitest;

/**
 * Created by gzb on 18-3-26.
 */

public class NativeUtil {

    static {
        System.loadLibrary("native-lib");
    }

    public static native String stringFromJNI();

    public static native String stringCreate();

    public static native String testArray();

    public static native String testNIO();

    public static native String testJObject();

    /**
     * 访问域
     */
    //实例域
    private String instanceField = "Instance Field";
    //静态域
    private static String staticField = "Static Field";

}
