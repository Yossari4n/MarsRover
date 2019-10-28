#ifndef MessageOut_h
#define MessageOut_h

#include "ConnectionsManager.h"

template <class M>
class MessageOut final : public AbstractMessageOut {
    friend class ConnectionsManager;

public:
    MessageOut(Component* owner, ConnectionsManager* connections_manager)
        : m_Owner(owner)
        , m_ConnectionsManager(connections_manager) {}

    MessageOut() = delete;
    MessageOut(const MessageOut&) = delete;
    MessageOut& operator=(const MessageOut&) = delete;
    MessageOut(MessageOut&&) = delete;
    MessageOut& operator=(MessageOut&&) = delete;
    ~MessageOut() = default;

    Component* Owner() const override { return m_Owner; }

    void Send(M& message) {  m_MessageManager->ForwardMessage(this, &message); }

private:
    Component* m_Owner;
    ConnectionsManager* m_ConnectionsManager;
};

#endif
