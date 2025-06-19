#include <jni.h>
#include "DMRCenter.h"
#include "SubMediaRender.cpp"

extern "C" JNIEXPORT jint JNICALL
Java_com_github_mediaserver_server_jni_DMSJniInterface_startServer(JNIEnv* env, jclass clazz, jbyteArray rootDir, jbyteArray name, jbyteArray uid) {
    const char* cRoot = (const char*) env->GetByteArrayElements(rootDir, 0);
    const char* cName = (const char*) env->GetByteArrayElements(name, 0);
    const char* cUid = (const char*) env->GetByteArrayElements(uid, 0);

    auto center = DMRCenter::getInstance();
    center->Init(cName, cUid);
    center->SetActionReceiver(new SubMediaRender());
    center->Start(cRoot);

    env->ReleaseByteArrayElements(rootDir, (jbyte*)cRoot, 0);
    env->ReleaseByteArrayElements(name, (jbyte*)cName, 0);
    env->ReleaseByteArrayElements(uid, (jbyte*)cUid, 0);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_github_mediaserver_server_jni_DMSJniInterface_stopServer(JNIEnv* env, jclass clazz) {
    DMRCenter::getInstance()->Stop();
    return 0;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_github_mediaserver_server_jni_DMSJniInterface_enableLogPrint(JNIEnv* env, jclass clazz, jboolean flag) {
    if (flag) {
        NPT_LogManager::GetDefault().Configure("plist:.level=DEBUG;console:enable=true");
    } else {
        NPT_LogManager::GetDefault().Configure("plist:.level=ERROR;console:enable=false");
    }
    return true;
}
