#ifndef RigidBody_h
#define RigidBody_h

#include "Component.h"
#include "../../scenes/Scene.h"
#include "../../physics/PhysicsManager.h"

class RigidBody : public Component {
public:
    RigidBody(btScalar mass, btCollisionShape* shape);
    ~RigidBody();

    void Initialize() override;
    void Destroy() override;

private:
    btRigidBody* m_RigidBody;
};

#endif
