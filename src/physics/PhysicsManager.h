#ifndef PhysicsManager_h
#define PhysicsManager_h

#include "../debuging/Logger.h"

#pragma warning(push, 0)
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"

#include <assert.h>
#pragma warning(pop)

class PhysicsManager {
public:

    void Initialize();
    void StepSimulation(float delta_time);
    void ExitPhysics();

    void AddRigidBody(btRigidBody* rigid_body);
    void RemoveRigidBody(btRigidBody* rigid_body);

    void Gravity(btVector3 gravity) { m_World->setGravity(gravity); }
    btVector3 Gravity() const { return m_World->getGravity(); }

private:
    std::unique_ptr<btDynamicsWorld> m_World;
    std::unique_ptr<btBroadphaseInterface> m_Broadphase;
    std::unique_ptr<btCollisionDispatcher> m_Dispatcher;
    std::unique_ptr<btConstraintSolver> m_Solver;
    std::unique_ptr<btDefaultCollisionConfiguration> m_CollisionConfiguration;

    btAlignedObjectArray<btCollisionShape*> m_CollisionShapes;
};

#endif
