//
// Created by AI Assistant
//

#include "PlatinumJniProxy.h"
#include "DMRCenter.h"
#include "NdkLogger.h"
#include <Neptune.h>

NPT_SET_LOCAL_LOGGER("PlatinumJniProxy")

JNIEXPORT void JNICALL
JNI_FUNC_DMR(enableLogFrint)(JNIEnv *env, jclass type, jboolean enable) {
    LOGD("PlatinumJniProxy::enableLogFrint() - Enable: %d", enable);
    
    if (enable) {
        // Enable detailed logging
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
JNI_FUNC_DMR(responsseGenaEvent)(JNIEnv *env, jclass type, jstring service_,
                                jstring variable_, jstring value_) {
    LOGD("PlatinumJniProxy::responsseGenaEvent()");
    
    const char *service = env->GetStringUTFChars(service_, 0);
    const char *variable = env->GetStringUTFChars(variable_, 0);
    const char *value = env->GetStringUTFChars(value_, 0);
    
    NPT_Result result = NPT_ERROR_INVALID_STATE;
    
    DMRCenter* dmrCenter = DMRCenter::getInstance();
    if (dmrCenter != NULL) {
        result = dmrCenter->SetServiceEvent(service, variable, value);
    } else {
        LOGE("DMRCenter instance is null");
    }
    
    env->ReleaseStringUTFChars(service_, service);
    env->ReleaseStringUTFChars(variable_, variable);
    env->ReleaseStringUTFChars(value_, value);
    
    return result;
}

JNIEXPORT jint JNICALL
JNI_FUNC_DMR(setRenderConfig)(JNIEnv *env, jclass type, jstring param1_,
                             jstring param2_, jstring param3_, jstring param4_,
                             jstring param5_, jstring param6_) {
    LOGD("PlatinumJniProxy::setRenderConfig()");
    
    const char *param1 = env->GetStringUTFChars(param1_, 0);
    const char *param2 = env->GetStringUTFChars(param2_, 0);
    const char *param3 = env->GetStringUTFChars(param3_, 0);
    const char *param4 = env->GetStringUTFChars(param4_, 0);
    const char *param5 = env->GetStringUTFChars(param5_, 0);
    const char *param6 = env->GetStringUTFChars(param6_, 0);
    
    NPT_Result result = NPT_ERROR_INVALID_STATE;
    
    DMRCenter* dmrCenter = DMRCenter::getInstance();
    if (dmrCenter != NULL) {
        result = dmrCenter->SetRenderConfig(param1, param2, param3, param4, param5, param6);
    } else {
        LOGE("DMRCenter instance is null");
    }
    
    env->ReleaseStringUTFChars(param1_, param1);
    env->ReleaseStringUTFChars(param2_, param2);
    env->ReleaseStringUTFChars(param3_, param3);
    env->ReleaseStringUTFChars(param4_, param4);
    env->ReleaseStringUTFChars(param5_, param5);
    env->ReleaseStringUTFChars(param6_, param6);
    
    return result;
}

JNIEXPORT jint JNICALL
JNI_FUNC_DMR(startMediaRender)(JNIEnv *env, jclass type, jstring friendly_name_, 
                              jstring uuid_) {
    LOGD("PlatinumJniProxy::startMediaRender()");
    
    const char *friendly_name = env->GetStringUTFChars(friendly_name_, 0);
    const char *uuid = env->GetStringUTFChars(uuid_, 0);
    
    NPT_Result result = NPT_ERROR_INVALID_STATE;
    
    DMRCenter* dmrCenter = DMRCenter::getInstance();
    if (dmrCenter != NULL) {
        result = dmrCenter->Start(friendly_name, uuid);
    } else {
        LOGE("DMRCenter instance is null");
    }
    
    env->ReleaseStringUTFChars(friendly_name_, friendly_name);
    env->ReleaseStringUTFChars(uuid_, uuid);
    
    return result;
}

JNIEXPORT jint JNICALL
JNI_FUNC_DMR(stopMediaRender)(JNIEnv *env, jclass type) {
    LOGD("PlatinumJniProxy::stopMediaRender()");
    
    NPT_Result result = NPT_ERROR_INVALID_STATE;
    
    DMRCenter* dmrCenter = DMRCenter::getInstance();
    if (dmrCenter != NULL) {
        result = dmrCenter->Stop();
    } else {
        LOGE("DMRCenter instance is null");
    }
    
    return result;
} 