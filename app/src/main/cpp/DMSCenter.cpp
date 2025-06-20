//
// Created by AI Assistant
//

#include "DMSCenter.h"
#include "NdkLogger.h"

#include "Neptune/Core/NptConstants.h"
#include "Neptune/Core/NptThreads.h"
#include "Platinum/Devices/MediaServer/PltFileMediaServer.h"
#include <PltFileMediaServer.h>

NPT_SET_LOCAL_LOGGER("DMSCenter");

// Static member initialization
DMSCenter* DMSCenter::m_pInstance = NULL;
NPT_Mutex DMSCenter::m_Lock;

DMSCenter::DMSCenter(void) :
    m_bStarted(false) {
    LOGD("DMSCenter::DMSCenter()");
}

DMSCenter::~DMSCenter() {
    LOGD("DMSCenter::~DMSCenter()");
    Stop();
}

DMSCenter* DMSCenter::getInstance(void) {
    NPT_AutoLock autoLock(m_Lock);
    if (m_pInstance == NULL) {
        m_pInstance = new DMSCenter();
    }
    return m_pInstance;
}

void DMSCenter::releaseInstance(void) {
    NPT_AutoLock autoLock(m_Lock);
    if (m_pInstance != NULL) {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

NPT_Result DMSCenter::Init(const char* friendly_name, const char* uuid, const char* path) {
    LOGD("DMSCenter::Init() - Name: %s, UUID: %s, Path: %s", friendly_name, uuid, path);
    
    if (friendly_name) {
        m_FriendlyName = friendly_name;
    }
    if (uuid) {
        m_UUID = uuid;
    }
    if (path) {
        m_Path = path;
    }
    
    return NPT_SUCCESS;
}

NPT_Result DMSCenter::SetRenderConfig(const char* param1, const char* param2, const char* param3, 
                                     const char* param4, const char* param5, const char* param6) {
    LOGD("DMSCenter::SetRenderConfig()");
    // Store configuration parameters for later use
    // Implementation depends on specific requirements
    return NPT_SUCCESS;
}

NPT_Result DMSCenter::Start(const char* friendly_name, const char* uuid, const char* path) {
    LOGD("DMSCenter::Start() - Name: %s, UUID: %s, Path: %s", friendly_name, uuid, path);
    
    if (m_bStarted) {
        LOGW("DMSCenter already started");
        return NPT_ERROR_INVALID_STATE;
    }
    
    // Update parameters if provided
    if (friendly_name) {
        m_FriendlyName = friendly_name;
    }
    if (uuid) {
        m_UUID = uuid;
    }
    if (path) {
        m_Path = path;
    }
    
    // Create Media Server device
    PLT_FileMediaServer* server = new PLT_FileMediaServer(
        m_Path.GetChars(),     // file_root
        m_FriendlyName.GetChars(), // friendly_name
        false,                 // show_ip
        m_UUID.IsEmpty() ? NULL : m_UUID.GetChars(), // uuid
        0,                     // port
        false                  // port_rebind
    );
    
    m_Device = server;
    
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
    LOGD("DMSCenter started successfully");
    return NPT_SUCCESS;
}

NPT_Result DMSCenter::Stop(void) {
    LOGD("DMSCenter::Stop()");
    
    if (!m_bStarted) {
        LOGW("DMSCenter not started");
        return NPT_ERROR_INVALID_STATE;
    }
    
    if (m_UPnP.IsRunning()) {
        m_UPnP.Stop();
    }
    
    m_Device = NULL;
    m_bStarted = false;
    
    LOGD("DMSCenter stopped successfully");
    return NPT_SUCCESS;
} 