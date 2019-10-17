#include "PhysicsManager.h"

void PhysicsManager::Initialize() {
    Logger::Instance().InfoLog(Logger::ESender::Physics, "Initializing physics");

    m_CollisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
    m_Dispatcher = std::make_unique<btCollisionDispatcher>(m_CollisionConfiguration.get());
    m_Broadphase = std::make_unique<btDbvtBroadphase>();
    m_Solver = std::make_unique<btSequentialImpulseConstraintSolver>();

    m_World = std::make_unique<btDiscreteDynamicsWorld>(m_Dispatcher.get(), m_Broadphase.get(), m_Solver.get(), m_CollisionConfiguration.get());

    m_World->setGravity(btVector3(btScalar(0), btScalar(-10), btScalar(0)));
}

void PhysicsManager::StepSimulation(float delta_time) {
    m_World->stepSimulation(delta_time);
}

void PhysicsManager::ExitPhysics() {
    Logger::Instance().InfoLog(Logger::ESender::Physics, "Exiting physics");

    if (m_World) {
        int i = m_World->getNumConstraints() - 1;
        for (; i >= 0; i--) {
            m_World->removeConstraint(m_World->getConstraint(i));
        }

        i = m_World->getNumCollisionObjects() - 1;
        for (; i >= 0; i--) {
            btCollisionObject* obj = m_World->getCollisionObjectArray()[i];
            btRigidBody* body = btRigidBody::upcast(obj);

            if (body && body->getMotionState()) {
                delete body->getMotionState();
            }

            m_World->removeCollisionObject(obj);
            delete obj;
        }
    }

    for (int j = 0; j < m_CollisionShapes.size(); j++) {
        delete m_CollisionShapes[j];
    }
}

void PhysicsManager::AddRigidBody(btRigidBody* rigid_body) {
    // Bullet assert that each rigidbody can be added only once

    m_World->addRigidBody(rigid_body);
}

void PhysicsManager::RemoveRigidBody(btRigidBody* rigid_body) {
    m_World->removeRigidBody(rigid_body);
}
