//
// Created by AI Assistant
//

#include "DMRCenter.h"
#include "MediaRenderer.h"
#include "Neptune/Core/NptConstants.h"
#include "Neptune/Core/NptThreads.h"
#include "Platinum/Core/PltService.h"
#include "NdkLogger.h"

NPT_SET_LOCAL_LOGGER("DMRCenter");

// Static member initialization
DMRCenter* DMRCenter::m_pInstance = NULL;
NPT_Mutex DMRCenter::m_Lock;

DMRCenter::DMRCenter(void) :
    m_ActionReceiver(NULL),
    m_PrivateServerReceiver(NULL),
    m_bStarted(false),
    m_DMRType(0) {
    LOGD("DMRCenter::DMRCenter()");
}

DMRCenter::~DMRCenter() {
    LOGD("DMRCenter::~DMRCenter()");
    Stop();
}

DMRCenter* DMRCenter::getInstance(void) {
    NPT_AutoLock autoLock(m_Lock);
    if (m_pInstance == NULL) {
        m_pInstance = new DMRCenter();
    }
    return m_pInstance;
}

void DMRCenter::releaseInstance(void) {
    NPT_AutoLock autoLock(m_Lock);
    if (m_pInstance != NULL) {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

NPT_Result DMRCenter::Init(const char* friendly_name, const char* uuid) {
    LOGD("DMRCenter::Init() - Name: %s, UUID: %s", friendly_name, uuid);
    
    if (friendly_name) {
        m_FriendlyName = friendly_name;
    }
    if (uuid) {
        m_UUID = uuid;
    }
    
    return NPT_SUCCESS;
}

NPT_Result DMRCenter::SetRenderConfig(const char* param1, const char* param2, const char* param3, 
                                     const char* param4, const char* param5, const char* param6) {
    LOGD("DMRCenter::SetRenderConfig()");
    // Store configuration parameters for later use
    // Implementation depends on specific requirements
    return NPT_SUCCESS;
}

NPT_Result DMRCenter::Start(const char* friendly_name, const char* uuid) {
    LOGD("DMRCenter::Start() - Name: %s, UUID: %s", friendly_name, uuid);
    
    if (m_bStarted) {
        LOGW("DMRCenter already started");
        return NPT_ERROR_INVALID_STATE;
    }
    
    // Update parameters if provided
    if (friendly_name) {
        m_FriendlyName = friendly_name;
    }
    if (uuid) {
        m_UUID = uuid;
    }
    
    // Create MediaRenderer device
    MediaRenderer* renderer = new MediaRenderer(
        m_FriendlyName.GetChars(),
        false, // show_ip
        m_UUID.IsEmpty() ? NULL : m_UUID.GetChars(),
        0,     // port
        false  // port_rebind
    );
    
    m_Device = renderer;
    
    // Add device to UPnP stack
    NPT_Result result = m_UPnP.AddDevice(m_Device);
    if (NPT_FAILED(result)) {
        LOGE("Failed to add device to UPnP stack: %d", result);
        return result;
    }
    
    // Start UPnP stack
    result = m_UPnP.Start();
    if (NPT_FAILED(result)) {
        LOGE("Failed to start UPnP stack: %d", result);
        return result;
    }
    
    m_bStarted = true;
    LOGD("DMRCenter started successfully");
    return NPT_SUCCESS;
}

NPT_Result DMRCenter::Stop(void) {
    LOGD("DMRCenter::Stop()");
    
    if (!m_bStarted) {
        LOGW("DMRCenter not started");
        return NPT_ERROR_INVALID_STATE;
    }
    
    if (m_UPnP.IsRunning()) {
        m_UPnP.Stop();
    }
    
    m_Device = NULL;
    m_bStarted = false;
    
    LOGD("DMRCenter stopped successfully");
    return NPT_SUCCESS;
}

NPT_Result DMRCenter::SetServiceEvent(const char* service, const char* variable, const char* value) {
    LOGD("DMRCenter::SetServiceEvent() - Service: %s, Variable: %s, Value: %s", 
         service, variable, value);
    
    if (!m_bStarted || m_Device.IsNull()) {
        LOGE("DMRCenter not started or device is null");
        return NPT_ERROR_INVALID_STATE;
    }
    
    PLT_Service* pService = NULL;
    NPT_Result result = m_Device->FindServiceByType(service, pService);
    if (NPT_FAILED(result) || pService == NULL) {
        LOGE("Service not found: %s", service);
        return NPT_ERROR_NO_SUCH_ITEM;
    }
    
    return pService->SetStateVariable(variable, value);
}

NPT_Result DMRCenter::SetPrivateServerEvent(const char* event, const char* param) {
    LOGD("DMRCenter::SetPrivateServerEvent() - Event: %s, Param: %s", event, param);
    
    if (m_PrivateServerReceiver) {
        // Call delegate if available
        // Implementation depends on Sub_PrivateServerDelegate interface
    }
    
    return NPT_SUCCESS;
}

NPT_Result DMRCenter::SetRenderingControlEvent(const char* variable, const char* value) {
    LOGD("DMRCenter::SetRenderingControlEvent() - Variable: %s, Value: %s", variable, value);
    
    return SetServiceEvent("urn:schemas-upnp-org:service:RenderingControl:1", variable, value);
}

NPT_Result DMRCenter::SetAVTransportEvent(const char* variable, const char* value) {
    LOGD("DMRCenter::SetAVTransportEvent() - Variable: %s, Value: %s", variable, value);
    
    return SetServiceEvent("urn:schemas-upnp-org:service:AVTransport:1", variable, value);
}

void DMRCenter::SetActionReceiver(PLT_MediaRendererDelegate* receiver) {
    LOGD("DMRCenter::SetActionReceiver()");
    m_ActionReceiver = receiver;
}

void DMRCenter::SetPrivateServerReceiver(Sub_PrivateServerDelegate* receiver) {
    LOGD("DMRCenter::SetPrivateServerReceiver()");
    m_PrivateServerReceiver = receiver;
}

void DMRCenter::SetDMRType(int type) {
    LOGD("DMRCenter::SetDMRType() - Type: %d", type);
    m_DMRType = type;
} 