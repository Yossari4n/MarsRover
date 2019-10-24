#ifndef RigidBody_h
#define RigidBody_h

#include "Component.h"
#include "../../scenes/Scene.h"
#include "../../physics/PhysicsManager.h"
#include "../connections/PropertyIn.h"

class RigidBody : public Component {
public:
    RigidBody(btScalar mass, btCollisionShape* shape);

    void MakeConnectors(ConnectionsManager& message_manager) override;
    void Initialize() override;
    void Update() override;
    void Destroy() override;

    PropertyIn<Transform> TransformIn;

private:
    btRigidBody* m_RigidBody;
};

#endif
