#ifndef Component_h
#define Component_h

#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

class Object;
class ConnectionPipe;
class ConnectionsManager;

class Component {
    friend class Object;

public:
    Component() = default;
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
    Component(Component&&) = delete;
    Component& operator=(Component&&) = delete;
    virtual ~Component() = default;

    std::uint8_t ID() const { return m_ID; }
    Object& Object() const { return *m_Object; }

protected:
    virtual void Initialize() {};
    virtual void Update() { assert(true && "Update function not overloaded"); };
    virtual void Destroy() {};

    void RegisterUpdateCall() const;
    void UnregisterUpdateCall() const;

private:
    class Object* m_Object{ nullptr };
    std::uint8_t m_ID{ 0 };
};

#endif
