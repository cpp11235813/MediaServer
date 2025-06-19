#include "IMediaActionReceiver.h"
#include <android/log.h>

#define TAG "SubMediaRender"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)

class SubMediaRender : public IMediaActionReceiver {
public:
    NPT_Result OnPlay(PLT_ActionReference& action) override {
        LOGI("OnPlay triggered");
        action->SetArgumentValue("Result", "OK");
        return NPT_SUCCESS;
    }

    NPT_Result OnPause(PLT_ActionReference& action) override {
        LOGI("OnPause triggered");
        return NPT_SUCCESS;
    }
    
    NPT_Result OnStop(PLT_ActionReference& action) override {
        LOGI("OnStop triggered");
        return NPT_SUCCESS;
    }
    
    NPT_Result OnNext(PLT_ActionReference& action) override {
        LOGI("OnNext triggered");
        return NPT_SUCCESS;
    }
    
    NPT_Result OnPrevious(PLT_ActionReference& action) override {
        LOGI("OnPrevious triggered");
        return NPT_SUCCESS;
    }
    
    NPT_Result OnSeek(PLT_ActionReference& action) override {
        LOGI("OnSeek triggered");
        return NPT_SUCCESS;
    }
    
    NPT_Result OnSetAVTransportURI(PLT_ActionReference& action) override {
        LOGI("OnSetAVTransportURI triggered");
        return NPT_SUCCESS;
    }
    
    NPT_Result OnSetMute(PLT_ActionReference& action) override {
        LOGI("OnSetMute triggered");
        return NPT_SUCCESS;
    }

    NPT_Result OnSetVolume(PLT_ActionReference& action) override {
        LOGI("OnSetVolume triggered");
        return NPT_SUCCESS;
    }
    
    // 添加缺失的纯虚函数实现
    NPT_Result OnGetCurrentConnectionInfo(PLT_ActionReference& action) override {
        LOGI("OnGetCurrentConnectionInfo triggered");
        return NPT_SUCCESS;
    }
    
    NPT_Result OnSetPlayMode(PLT_ActionReference& action) override {
        LOGI("OnSetPlayMode triggered");
        return NPT_SUCCESS;
    }
    
    NPT_Result OnSetVolumeDB(PLT_ActionReference& action) override {
        LOGI("OnSetVolumeDB triggered");
        return NPT_SUCCESS;
    }
    
    NPT_Result OnGetVolumeDBRange(PLT_ActionReference& action) override {
        LOGI("OnGetVolumeDBRange triggered");
        return NPT_SUCCESS;
    }
};
