#ifndef ObjectManager_h
#define ObjectManager_h

#include "Object.h"

#include <vector>
#include <unordered_map>
#include <string>

class Scene;

class ObjectManager {
    using Objects_t = std::unordered_map<Object::ID_t, Object>;

public:
    explicit ObjectManager(class Scene& owner);

    void InitializeObjects();
    void UpdateObjects();
    void DestroyObjects();

    Object* CreateObject(const std::string& name);
    void DestroyObject(const std::string& name);
    void DestroyObject(Object::ID_t id);

    Scene& Scene() const { return m_Scene; }

private:
    class Scene& m_Scene;

    std::hash<std::string> m_Hasher;
    Objects_t m_Objects;
};

#endif
