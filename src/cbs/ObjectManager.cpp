#include "ObjectManager.h"

#include "../scenes/Scene.h"

ObjectManager::ObjectManager(class Scene& owner)
    : m_Scene(owner)
    , m_NextObjectID(0) {
}

void ObjectManager::InitializeObjects() {
    for (Objects_t::size_type i = 0; i < m_Objects.size(); i++) {
        m_Objects[i]->InitializeComponents();
    }
}

void ObjectManager::UpdateObjects() {
    for (Objects_t::size_type i = 0; i < m_Objects.size(); i++) {
        m_Objects[i]->UpdateComponents();
    }
}

void ObjectManager::DestroyObjects() {
    for (Objects_t::size_type i = 0; i < m_Objects.size(); i++) {
        m_Objects[i]->DestroyComponents();
    }
    m_Objects.clear();
}

Object* ObjectManager::CreateObject(std::string name) {
    m_Objects.push_back(std::make_unique<Object>(*this, m_NextObjectID, name));

    m_NextObjectID = m_NextObjectID + 1;

    return m_Objects.at(m_Objects.size() - 1).get();
}

void ObjectManager::DestroyObject(std::uint8_t id) {
    auto object = std::find_if(m_Objects.begin(),
                               m_Objects.end(),
                               [=](std::unique_ptr<Object>& obj) { return obj->ID() == id; });

    if (object != m_Objects.end()) {
        (*object)->DestroyComponents();
        m_Objects.erase(object);
    }
}
