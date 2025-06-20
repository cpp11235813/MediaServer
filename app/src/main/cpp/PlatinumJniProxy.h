//
// Created by AI Assistant
//

#ifndef PLATINUMMEDIA_PLATINUMJNIPROXY_H
#define PLATINUMMEDIA_PLATINUMJNIPROXY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>

// JNI function name helper
#define JNI_FUNC_DMR(x) Java_com_geniusgithub_mediarender_jni_PlatinumJniProxy_##x

/**
 * Enable log printing for Platinum library
 */
JNIEXPORT void JNICALL
JNI_FUNC_DMR(enableLogFrint)(JNIEnv *env, jclass type, jboolean enable);

/**
 * Response to GENA event
 */
JNIEXPORT jint JNICALL
JNI_FUNC_DMR(responsseGenaEvent)(JNIEnv *env, jclass type, jstring service_,
                                jstring variable_, jstring value_);

/**
 * Set render configuration
 */
JNIEXPORT jint JNICALL
JNI_FUNC_DMR(setRenderConfig)(JNIEnv *env, jclass type, jstring param1_,
                             jstring param2_, jstring param3_, jstring param4_,
                             jstring param5_, jstring param6_);

/**
 * Start media renderer
 */
JNIEXPORT jint JNICALL
JNI_FUNC_DMR(startMediaRender)(JNIEnv *env, jclass type, jstring friendly_name_, 
                              jstring uuid_);

/**
 * Stop media renderer
 */
JNIEXPORT jint JNICALL
JNI_FUNC_DMR(stopMediaRender)(JNIEnv *env, jclass type);

#ifdef __cplusplus
}
#endif

#endif //PLATINUMMEDIA_PLATINUMJNIPROXY_H 