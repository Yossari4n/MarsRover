#include "PhysicsManager.h"

void PhysicsManager::Initialize() {
    Logger::Instance().InfoLog(Logger::ESender::Physics, "Initializing physics");

    m_CollisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
    m_Dispatcher = std::make_unique<btCollisionDispatcher>(m_CollisionConfiguration.get());
    m_Broadphase = std::make_unique<btDbvtBroadphase>();
    m_Solver = std::make_unique<btMLCPSolver>(new btDantzigSolver());

    m_World = std::make_unique<btDiscreteDynamicsWorld>(m_Dispatcher.get(), m_Broadphase.get(), m_Solver.get(), m_CollisionConfiguration.get());
    m_World->getSolverInfo().m_minimumSolverBatchSize = 1;
    m_World->getSolverInfo().m_globalCfm = 0.0001;

    m_World->setGravity(btVector3(btScalar(0), btScalar(-10), btScalar(0)));
}

void PhysicsManager::StepSimulation(float delta_time) {
    m_World->stepSimulation(delta_time);
    for (auto it = m_PhysicalObjects.begin(); it != m_PhysicalObjects.end(); it++) {
        (*it)->PhysicsUpdate();
    }
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

            if (btRigidBody* body = btRigidBody::upcast(obj)) {
                if (auto shape = body->getCollisionShape()) {
                    delete shape;
                }

                if (auto motion_state = body->getMotionState()) {
                    delete motion_state;
                }
            }

            m_World->removeCollisionObject(obj);
            delete obj;
        }
    }
}

void PhysicsManager::RegisterPhysicalObject(IPhysicalObject* component) {
    assert(std::find(m_PhysicalObjects.begin(), m_PhysicalObjects.end(), component) == m_PhysicalObjects.end());

    m_PhysicalObjects.push_back(component);
}

void PhysicsManager::UnregisterPhysiaclObject(IPhysicalObject* component) {
    auto to_erase = std::find(m_PhysicalObjects.begin(), m_PhysicalObjects.end(), component);
    if (to_erase != m_PhysicalObjects.end()) {
        m_PhysicalObjects.erase(to_erase);
    }
}

void PhysicsManager::AddRigidBody(btRigidBody* rigid_body) {
    // Bullet asserts that each rigidbody can be added only once

    m_World->addRigidBody(rigid_body);
}

void PhysicsManager::RemoveRigidBody(btRigidBody* rigid_body) {
    // Bullet asserts that each rigidbody can be removed only once

    m_World->removeRigidBody(rigid_body);
}

void PhysicsManager::AddConstraint(btTypedConstraint* constraint, bool disable_collisions_between_linked_bodies) {
    m_World->addConstraint(constraint, disable_collisions_between_linked_bodies);
}

void PhysicsManager::RemoveConstraint(btTypedConstraint* constraint) {
    m_World->removeConstraint(constraint);
}

void PhysicsManager::AddVehicle(btActionInterface* vehicle) {
    m_World->addVehicle(vehicle);
}

void PhysicsManager::RemoveVehicle(btActionInterface* vehicle) {
    m_World->removeVehicle(vehicle);
}
