#include "RigidBody.h"

RigidBody::RigidBody(btScalar mass, btCollisionShape* shape)
    : m_ScaleMatrix(1.0f) {
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

    // Dirty way to determinate scale matrix and debug draw function
    switch (shape->getShapeType()) {
    case BOX_SHAPE_PROXYTYPE:
        auto box_shape = reinterpret_cast<btBoxShape*>(shape);
        auto half_extents = box_shape->getHalfExtentsWithMargin();
        m_ScaleMatrix = glm::scale(m_ScaleMatrix, glm::vec3(half_extents.x() * 2, half_extents.y() * 2, half_extents.z() * 2));
        break;
    }
}

void RigidBody::Initialize() {
    btTransform transform;
    transform.setIdentity();

    auto pos = TransformIn.Value()->Position();
    transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

    auto rot = TransformIn.Value()->Rotation();
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

    // TODO optimise it?
    auto origin = trans.getOrigin();
    glm::vec3 glm_pos(origin.getX(), origin.getY(), origin.getZ());
    auto rot = trans.getRotation();
    glm::quat glm_rot(rot.getW(), rot.getX(), rot.getY(), rot.getZ());

    // Update connected transform with position and rotation
    TransformIn.Value()->Position(glm_pos);
    TransformIn.Value()->Rotation(glm_rot);

    // Debug draw
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm_pos) * glm::mat4_cast(glm_rot) * m_ScaleMatrix;
    Object().Scene().DrawCuboid(model, glm::vec3(1.0f, 0.0f, 0.0f));
}
