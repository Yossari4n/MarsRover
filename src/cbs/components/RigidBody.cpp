#include "RigidBody.h"

RigidBody::RigidBody(btScalar mass, btCollisionShape* shape) {
    btVector3 local_inertia(0, 0, 0);
    if (mass != 0.0f) {
        shape->calculateLocalInertia(mass, local_inertia);
    }

    btTransform start;
    start.setIdentity();

    // Resources will be deleted by PhysicsManager on PhysicsExits
    btDefaultMotionState* motion_state = new btDefaultMotionState(start);
    btRigidBody::btRigidBodyConstructionInfo info(mass, motion_state, shape, local_inertia);

    m_RigidBody = new btRigidBody(info);
    m_RigidBody->setUserIndex(-1);
}

void RigidBody::Initialize() {
    btTransform transform;
    transform.setIdentity();

    auto pos = Object().Root().Position();
    transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

    auto rot = Object().Root().Rotation();
    transform.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));

    m_RigidBody->setWorldTransform(transform);
    m_RigidBody->getMotionState()->setWorldTransform(transform);

    Object().Scene().AddRigidBody(m_RigidBody);
    Object().Scene().RegisterPhysicalObject(this);
}

void RigidBody::Destroy() {
    Object().Scene().UnregisterPhysicalObject(this);
}

void RigidBody::PhysicsUpdate() {
    btTransform trans;
    m_RigidBody->getMotionState()->getWorldTransform(trans);

    Object().Root().Position(glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
    Object().Root().Rotation(glm::quat(trans.getRotation().getW(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ()));
}
