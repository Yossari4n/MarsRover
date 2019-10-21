#include "ObjectManager.h"

#include "../scenes/Scene.h"

ObjectManager::ObjectManager(class Scene& owner)
    : m_Scene(owner) {
}

void ObjectManager::InitializeObjects() {
    for (auto& [key, object] : m_Objects) {
        object.InitializeComponents();
    }
}

void ObjectManager::UpdateObjects() {
    for (auto& [key, object] : m_Objects) {
        object.UpdateComponents();
    }
}

void ObjectManager::DestroyObjects() {
    for (auto& [key, object] : m_Objects) {
        object.DestroyComponents();
    }
    m_Objects.clear();
}

Object* ObjectManager::CreateObject(const std::string& name) {
    Object::ID_t id = m_Hasher(name);

    assert(m_Objects.find(id) == m_Objects.end());

    m_Objects.try_emplace(id, *this, id, name);

    return &m_Objects.at(id);
}

void ObjectManager::DestroyObject(const std::string& name) {
    Object::ID_t id = m_Hasher(name);
    DestroyObject(id);
}

void ObjectManager::DestroyObject(Object::ID_t id) {
    auto object = m_Objects.find(id);

    if (object != m_Objects.end()) {
        object->second.DestroyComponents();
        m_Objects.erase(object);
    }
}
