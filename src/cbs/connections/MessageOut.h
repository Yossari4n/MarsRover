#ifndef MessageOut_h
#define MessageOut_h

#include "ConnectionsManager.h"

template <class M>
class MessageOut final : public AbstractMessageOut {
    friend class ConnectionsManager;

public:
    MessageOut() 
        : m_Owner(nullptr)
        , m_ConnectionsManager(nullptr) { }
    ~MessageOut() = default;

    Component* Owner() const override { return m_Owner; }

    void Send(M& message) {  m_MessageManager->ForwardMessage(this, &message); }

private:
    MessageOut(Component* owner, ConnectionsManager* connections_manager)
        : m_Owner(owner)
        , m_ConnectionsManager(connections_manager) { }

    MessageOut& operator=(const MessageOut& other) {
        if (this == &other) {
            return *this;
        }

        m_Owner = other.m_Owner;
        m_ConnectionsManager = other.m_ConnectionsManager;

        return *this;
    }

    MessageOut(const MessageOut&) = default;
    MessageOut(MessageOut&&) = default;
    MessageOut& operator=(MessageOut&&) = default;

    Component* m_Owner;
    ConnectionsManager* m_ConnectionsManager;
};

#endif
