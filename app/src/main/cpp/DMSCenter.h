//
// Created by AI Assistant
//

#ifndef PLATINUMMEDIA_DMSCENTER_H
#define PLATINUMMEDIA_DMSCENTER_H

//#include <Platinum.h>
//#include <PltMediaServer.h>
#include <PltUPnP.h>
#include "Neptune/Core/NptTypes.h"
#include "Neptune/Core/NptThreads.h"
#include "Platinum/Core/PltUPnP.h"
#include "Neptune/Core/NptStrings.h"

/**
 * DMSCenter - Device Media Server Center
 * Singleton class to manage DLNA Media Server functionality
 */
class DMSCenter {
public:
    // Singleton pattern
    static DMSCenter* getInstance(void);
    static void releaseInstance(void);
    
    // Constructor and Destructor
    DMSCenter(void);
    ~DMSCenter();
    
    // Initialization and Configuration
    NPT_Result Init(const char* friendly_name, const char* uuid, const char* path);
    NPT_Result SetRenderConfig(const char* param1, const char* param2, const char* param3, 
                              const char* param4, const char* param5, const char* param6);
    
    // Server Control
    NPT_Result Start(const char* friendly_name, const char* uuid, const char* path);
    NPT_Result Stop(void);

private:
    static DMSCenter* m_pInstance;
    static NPT_Mutex m_Lock;
    
    PLT_UPnP m_UPnP;
    PLT_DeviceHostReference m_Device;
    
    bool m_bStarted;
    NPT_String m_FriendlyName;
    NPT_String m_UUID;
    NPT_String m_Path;
};

#endif //PLATINUMMEDIA_DMSCENTER_H 