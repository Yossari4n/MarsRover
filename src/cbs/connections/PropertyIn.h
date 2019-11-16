#ifndef PropertyIn_h
#define PropertyIn_h

#include "ConnectionsManager.h"
#include "PropertyOut.h"

template <class T>
class PropertyIn final : public AbstractPropertyIn {
    friend class ConnectionsManager;

public:
    PropertyIn(Component* owner)
        : m_Owner(owner)
        , m_Source(nullptr) {}

    PropertyIn() = delete;
    PropertyIn(const PropertyIn&) = delete;
    PropertyIn& operator=(const PropertyIn& other) = delete;
    PropertyIn(PropertyIn&&) = delete;
    PropertyIn& operator=(PropertyIn&&) = delete;
    ~PropertyIn() = default;

    Component* Owner() const override { return m_Owner; }

    const T& Value() const { return m_Source->Value(); }
    operator const T&() const { return m_Source->Value(); }

    bool Connected() const { return m_Source != nullptr; }

private:
    void RemoveSource() override { m_Source = nullptr; }

    Component* m_Owner;
    PropertyOut<T>* m_Source;
};

template <class T, size_t N>
class PropertyIn<T[N]> final : public AbstractPropertyIn {
    friend class ConnectionsManager;

public:
    PropertyIn(Component* owner)
        : m_Owner(owner) {
        m_Sources.fill(nullptr);
    }

    PropertyIn() = delete;
    PropertyIn(const PropertyIn&) = delete;
    PropertyIn& operator=(const PropertyIn&) = delete;
    PropertyIn(PropertyIn&&) = delete;
    PropertyIn& operator=(PropertyIn&&) = delete;
    ~PropertyIn() = default;

    Component* Owner() const override { return m_Owner; }

    const T& operator[](std::size_t idx) const { return m_Sources[idx]->Value(); }

    bool Connected(std::size_t idx) const { return m_Sources[idx] != nullptr; }

private:
    void RemoveSource() override {
        for (auto& ptr : m_Sources) {
            ptr = nullptr;
        }
    }

    Component* m_Owner;
    std::array<PropertyOut<T>*, N> m_Sources;
};

#endif
