#ifndef RigidBody_h
#define RigidBody_h

#include "Component.h"
#include "../../physics/PhysicsManager.h"

class RigidBody : public Component {
public:

private:
    btRigidBody* m_RigidBody;
};

#endif
