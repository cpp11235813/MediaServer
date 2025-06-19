#pragma once

#include "Platinum/Core/PltAction.h"
#include "Neptune/Core/NptReferences.h"
#include "Platinum/Devices/MediaRenderer/PltMediaRenderer.h"

class IMediaActionReceiver : public PLT_MediaRendererDelegate {
public:
    virtual void OnPlay(NPT_Reference<PLT_Action> action) {}
    virtual void OnPause(NPT_Reference<PLT_Action> action) {}
    virtual void OnStop(NPT_Reference<PLT_Action> action) {}
    virtual void OnNext(NPT_Reference<PLT_Action> action) {}
    virtual void OnPrevious(NPT_Reference<PLT_Action> action) {}
    virtual void OnSetAVTransportURI(NPT_Reference<PLT_Action> action) {}
    virtual void OnSeek(NPT_Reference<PLT_Action> action) {}
    virtual void OnSetVolume(NPT_Reference<PLT_Action> action) {}
    virtual void OnSetMute(NPT_Reference<PLT_Action> action) {}
};
