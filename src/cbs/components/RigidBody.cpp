#include "RigidBody.h"

RigidBody::RigidBody(btScalar mass, btCollisionShape* shape) {
    btVector3 local_inertia(0, 0, 0);
    if (mass != 0.0f) {
        shape->calculateLocalInertia(mass, local_inertia);
    }

    btTransform start;
    start.setIdentity();

    // motion_state will be deleted with m_RigidBody deletion
    btDefaultMotionState* motion_state = new btDefaultMotionState(start);
    btRigidBody::btRigidBodyConstructionInfo info(mass, motion_state, shape, local_inertia);

    m_RigidBody = new btRigidBody(info);
    m_RigidBody->setUserIndex(-1);
}

RigidBody::~RigidBody() {
    delete m_RigidBody->getMotionState();
    delete m_RigidBody;
}

void RigidBody::Initialize() {
    Object().Scene().AddRigidBody(m_RigidBody);
}

void RigidBody::Destroy() {
    Object().Scene().RemoveRigidBody(m_RigidBody);
}
