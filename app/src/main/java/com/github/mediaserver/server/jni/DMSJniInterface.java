package com.github.mediaserver.server.jni;

public class DMSJniInterface {

    static {
        System.loadLibrary("git-platinum");
    }
 
    public static native int startServer(String rootDir, String name, String uid);
    public static native int stopServer();  
    
    public static native boolean enableLogPrint(boolean flag);
    
}
