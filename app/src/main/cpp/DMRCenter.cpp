#include "DMRCenter.h"
#include "IMediaActionReceiver.h"

DMRCenter* DMRCenter::m_pInstance = nullptr;

DMRCenter* DMRCenter::getInstance() {
    if (!m_pInstance) m_pInstance = new DMRCenter();
    return m_pInstance;
}

void DMRCenter::releaseInstance() {
    delete m_pInstance;
    m_pInstance = nullptr;
}

DMRCenter::DMRCenter() : m_receiver(nullptr) {}
DMRCenter::~DMRCenter() {}

bool DMRCenter::Init(const char* name, const char* uuid) {
    return true;
}

void DMRCenter::Start(const char* rootDir) {}
void DMRCenter::Stop() {}

void DMRCenter::SetRenderConfig(const char* c1, const char* c2, const char* c3, const char* c4, const char* c5) {}
void DMRCenter::SetAVTransportEvent(const char* sid, const char* varName) {}
void DMRCenter::SetRenderingControlEvent(const char* sid, const char* varName) {}
void DMRCenter::SetServiceEvent(const char* sid, const char* service, const char* var) {}
void DMRCenter::SetActionReceiver(IMediaActionReceiver* receiver) { m_receiver = receiver; }
