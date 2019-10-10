#ifndef PhysicsManager_h

#include "../debuging/Logger.h"

#pragma warning(push, 0)
#include "btBulletDynamicsCommon.h"
#pragma warning(pop)

class PhysicsManager {
public:

    void Initialize();

private:
    btDynamicsWorld* m_World;
};

#endif
