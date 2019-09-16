#include "ObjectManager.h"

#include "../scenes/Scene.h"

ObjectManager::ObjectManager(class Scene& owner)
    : m_Scene(owner)
    , m_Hasher() {
}

ObjectManager::~ObjectManager() {
    for (auto it = m_Objects.begin(); it != m_Objects.end(); it++) {
        it->second->DestroyComponents();
    }
    m_Objects.clear();
}

void ObjectManager::InitializeObjects() {
    for (auto it = m_Objects.begin(); it != m_Objects.end(); it++) {
        it->second->InitializeComponents();
    }
}

void ObjectManager::ProcessFrame() {
    for (auto it = m_Objects.begin(); it != m_Objects.end(); it++) {
        it->second->ProcessFrame();
    }
}

Object* ObjectManager::CreateObject(std::string name) {
    auto id = m_Hasher(name);

    assert(m_Objects.find(id) == m_Objects.end());

    m_Objects.emplace(id, std::make_unique<Object>(*this, id, name));

    return m_Objects.at(id).get();
}

void ObjectManager::DestroyObject(std::string name) {
    DestroyObject(m_Hasher(name));
}

void ObjectManager::DestroyObject(size_t id) {
    auto object = m_Objects.find(id);
    object->second->DestroyComponents();
    m_Objects.erase(object);
}
