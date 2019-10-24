#ifndef TriggerOut_h
#define TriggerOut_h

#include "ConnectionsManager.h"

class TriggerOut final : public AbstractTriggerOut {
    friend class ConnectionsManager;

public:
    TriggerOut() 
        : m_Owner(nullptr)
        , m_ConnectionsManager(nullptr) { }
    ~TriggerOut() = default;

    Component* Owner() const override { return m_Owner; }

    void Trigger() override { m_ConnectionsManager->ForwardTrigger(this); }

private:
    TriggerOut(Component* owner, ConnectionsManager* connections_manager)
        : m_Owner(owner)
        , m_ConnectionsManager(connections_manager) { }

    TriggerOut& operator=(const TriggerOut& other) {
        if (this == &other) {
            return *this;
        }

        m_Owner = other.m_Owner;
        m_ConnectionsManager = other.m_ConnectionsManager;

        return *this;
    }

    TriggerOut(const TriggerOut&) = default;
    TriggerOut(TriggerOut&&) = default;
    TriggerOut& operator=(TriggerOut&&) = default;

    Component* m_Owner;
    ConnectionsManager* m_ConnectionsManager;
};

#endif
