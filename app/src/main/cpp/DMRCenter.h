#pragma once

//#include "PLT_MediaRenderer.h"
//#include "PLT_ActionListener.h"

#include "PltDeviceHost.h"

class DMRCenter {
public:
    static DMRCenter* getInstance();
    static void releaseInstance();

    bool Init(const char* name, const char* uuid);
    void Start(const char* rootDir);
    void Stop();

    void SetRenderConfig(const char* config1, const char* config2, const char* config3,
                         const char* config4, const char* config5);

    void SetAVTransportEvent(const char* sid, const char* varName);
    void SetRenderingControlEvent(const char* sid, const char* varName);
    void SetServiceEvent(const char* sid, const char* service, const char* var);

    void SetActionReceiver(class IMediaActionReceiver* receiver);

private:
    DMRCenter();
    ~DMRCenter();

    static DMRCenter* m_pInstance;
    NPT_Reference<PLT_DeviceHost> m_device;
    IMediaActionReceiver* m_receiver;
};
