#ifndef RigidBody_h
#define RigidBody_h

#include "Component.h"
#include "../../scenes/Scene.h"
#include "../../physics/PhysicsManager.h"
#include "../../physics/IPhysicalObject.h"
#include "../connections/PropertyIn.h"

class RigidBody : public Component, public IPhysicalObject {
public:
    RigidBody(btScalar mass, btCollisionShape* shape);

    void Initialize() override;
    void Destroy() override;

    void PhysicsUpdate() override;

public:
    PropertyIn<Transform*> TransformIn{ this };

private:
    btRigidBody* m_RigidBody;
};

#endif
