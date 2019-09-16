#ifndef ObjectManager_h
#define ObjectManager_h

#include "Object.h"

#include <string>
#include <vector>
#include <unordered_map>

class Scene;

class ObjectManager {
    using Objects_t = std::unordered_map<size_t, std::unique_ptr<Object>>;

public:
    explicit ObjectManager(class Scene& owner);
    ~ObjectManager();

    void InitializeObjects();
    void ProcessFrame();

    Object* CreateObject(std::string name);
    void DestroyObject(std::string name);
    void DestroyObject(size_t id);

    Scene& Scene() const { return m_Scene; }

private:
    class Scene& m_Scene;

    Objects_t m_Objects;
    std::hash<std::string> m_Hasher;
};

#endif
