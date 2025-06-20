//
// Created by AI Assistant
//

#ifndef PLATINUMMEDIA_DMRCENTER_H
#define PLATINUMMEDIA_DMRCENTER_H

//#include <Platinum.h>
//#include <PltMediaRenderer.h>
#include <PltUPnP.h>
#include "Neptune/Core/NptTypes.h"
#include "Neptune/Core/NptThreads.h"
#include "Platinum/Core/PltUPnP.h"
#include "Neptune/Core/NptStrings.h"

// Forward declarations
class PLT_MediaRendererDelegate;
class Sub_PrivateServerDelegate;

/**
 * DMRCenter - Device Media Renderer Center
 * Singleton class to manage DLNA Media Renderer functionality
 */
class DMRCenter {
public:
    // Singleton pattern
    static DMRCenter* getInstance(void);
    static void releaseInstance(void);
    
    // Constructor and Destructor
    DMRCenter(void);
    ~DMRCenter();
    
    // Initialization and Configuration
    NPT_Result Init(const char* friendly_name, const char* uuid);
    NPT_Result SetRenderConfig(const char* param1, const char* param2, const char* param3, 
                              const char* param4, const char* param5, const char* param6);
    
    // Server Control
    NPT_Result Start(const char* friendly_name, const char* uuid);
    NPT_Result Stop(void);
    
    // Event Handlers
    NPT_Result SetServiceEvent(const char* service, const char* variable, const char* value);
    NPT_Result SetPrivateServerEvent(const char* event, const char* param);
    NPT_Result SetRenderingControlEvent(const char* variable, const char* value);
    NPT_Result SetAVTransportEvent(const char* variable, const char* value);
    
    // Delegates and Receivers
    void SetActionReceiver(PLT_MediaRendererDelegate* receiver);
    void SetPrivateServerReceiver(Sub_PrivateServerDelegate* receiver);
    
    // DMR Type Configuration
    void SetDMRType(int type);

private:
    static DMRCenter* m_pInstance;
    static NPT_Mutex m_Lock;
    
    PLT_UPnP m_UPnP;
    PLT_DeviceHostReference m_Device;
    PLT_MediaRendererDelegate* m_ActionReceiver;
    Sub_PrivateServerDelegate* m_PrivateServerReceiver;
    
    bool m_bStarted;
    int m_DMRType;
    NPT_String m_FriendlyName;
    NPT_String m_UUID;
};

#endif //PLATINUMMEDIA_DMRCENTER_H 