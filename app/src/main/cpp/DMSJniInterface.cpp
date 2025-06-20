//
// Created by AI Assistant
//

#include "DMSJniInterface.h"
#include "DMSCenter.h"
#include "DMRCenter.h"
//#include <Neptune.h>
#include "NdkLogger.h"
#include <jni.h>

NPT_SET_LOCAL_LOGGER("DMSJniInterface");

JNIEXPORT void JNICALL
JNI_FUNC_DMS(enableLogPrint)(JNIEnv *env, jclass type, jboolean enable) {
    LOGD("DMSJniInterface::enableLogPrint() - Enable: %d", enable);
    
    if (enable) {
        // Enable detailed logging for Media Server
        NPT_LogManager::GetDefault().Configure(
            "plist:.level=FINE;.handlers=ConsoleHandler;.ConsoleHandler.outputs=2;"
            ".ConsoleHandler.colors=false;.ConsoleHandler.filter=59");
    } else {
        // Disable or reduce logging
        NPT_LogManager::GetDefault().Configure(
            "plist:.level=WARNING;.handlers=ConsoleHandler;.ConsoleHandler.outputs=2;"
            ".ConsoleHandler.colors=false;.ConsoleHandler.filter=59");
    }
}

JNIEXPORT jint JNICALL
JNI_FUNC_DMS(startServer)(JNIEnv *env, jclass type, jstring friendly_name_,
                         jstring uuid_, jstring path_) {
    LOGD("DMSJniInterface::startServer()");
    
    // Handle null parameters safely
    const char *friendly_name = NULL;
    const char *uuid = NULL;
    const char *path = NULL;
    
    if (friendly_name_ != NULL) {
        friendly_name = env->GetStringUTFChars(friendly_name_, 0);
    }
    if (uuid_ != NULL) {
        uuid = env->GetStringUTFChars(uuid_, 0);
    }
    if (path_ != NULL) {
        path = env->GetStringUTFChars(path_, 0);
    }
    
    NPT_Result result = NPT_ERROR_INVALID_STATE;
    
    DMSCenter* dmsCenter = DMSCenter::getInstance();
    if (dmsCenter != NULL) {
        result = dmsCenter->Start(friendly_name, uuid, path);
    } else {
        LOGE("DMSCenter instance is null");
    }
    
    // Release string resources safely
    if (friendly_name_ != NULL && friendly_name != NULL) {
        env->ReleaseStringUTFChars(friendly_name_, friendly_name);
    }
    if (uuid_ != NULL && uuid != NULL) {
        env->ReleaseStringUTFChars(uuid_, uuid);
    }
    if (path_ != NULL && path != NULL) {
        env->ReleaseStringUTFChars(path_, path);
    }
    
    return result;
}

JNIEXPORT jint JNICALL
JNI_FUNC_DMS(stopServer)(JNIEnv *env, jclass type) {
    LOGD("DMSJniInterface::stopServer()");
    
    NPT_Result result = NPT_ERROR_INVALID_STATE;
    
    DMSCenter* dmsCenter = DMSCenter::getInstance();
    if (dmsCenter != NULL) {
        result = dmsCenter->Stop();
    } else {
        LOGE("DMSCenter instance is null");
    }
    
    return result;
}

JNIEXPORT void JNICALL
JNI_FUNC_DMR_TYPE(setDMRType)(JNIEnv *env, jclass type, jint dmr_type) {
    LOGD("DMRJniProxy::setDMRType() - Type: %d", dmr_type);
    
    DMRCenter* dmrCenter = DMRCenter::getInstance();
    if (dmrCenter != NULL) {
        dmrCenter->SetDMRType(dmr_type);
    } else {
        LOGE("DMRCenter instance is null");
    }
} 