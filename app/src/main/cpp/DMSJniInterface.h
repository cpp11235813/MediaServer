//
// Created by AI Assistant
//

#ifndef PLATINUMMEDIA_DMSJNIINTERFACE_H
#define PLATINUMMEDIA_DMSJNIINTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>

// JNI function name helpers
#define JNI_FUNC_DMS(x) Java_com_github_mediaserver_server_jni_DMSJniInterface_##x
#define JNI_FUNC_DMR_TYPE(x) Java_com_mipt_platinum_DMRJniProxy_##x

/**
 * Enable log printing for Media Server
 */
JNIEXPORT void JNICALL
JNI_FUNC_DMS(enableLogPrint)(JNIEnv *env, jclass type, jboolean enable);

/**
 * Start media server
 */
JNIEXPORT jint JNICALL
JNI_FUNC_DMS(startServer)(JNIEnv *env, jclass type, jstring friendly_name_,
                         jstring uuid_, jstring path_);

/**
 * Stop media server
 */
JNIEXPORT jint JNICALL
JNI_FUNC_DMS(stopServer)(JNIEnv *env, jclass type);

/**
 * Set DMR type
 */
JNIEXPORT void JNICALL
JNI_FUNC_DMR_TYPE(setDMRType)(JNIEnv *env, jclass type, jint dmr_type);

#ifdef __cplusplus
}
#endif

#endif //PLATINUMMEDIA_DMSJNIINTERFACE_H 