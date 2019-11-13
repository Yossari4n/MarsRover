#include "Vehicle.h"

#include "../Object.h"
#include "../../scenes/Scene.h"
#include "RigidBody.h"
#include "Transform.h"


Vehicle::Vehicle(float suspension_rest_length, float steering_clamp, float wheel_radius, float wheel_width)
    : m_VehicleRaycaster(nullptr)
    , m_Vehicle(nullptr)
    , m_SuspensionRestLength(suspension_rest_length)
    , m_SteeringClamp(steering_clamp)
    , m_WheelRadius(wheel_radius)
    , m_WheelWidth(wheel_width) {

}

void Vehicle::Initialize() {
    assert(Chassis.Connected() && FrontWheel1.Connected() && FrontWheel2.Connected() && BackWheel1.Connected() && BackWheel2.Connected());

    m_VehicleRaycaster = new btDefaultVehicleRaycaster(Object().Scene().DynamicsWorld());
    m_Vehicle = new btRaycastVehicle(m_Tunning, Chassis.Value()->Handle(), m_VehicleRaycaster);

    Chassis.Value()->Handle()->setActivationState(DISABLE_DEACTIVATION);
    Object().Scene().AddVehicle(m_Vehicle);
    m_Vehicle->setCoordinateSystem(2, 1, 0);

    glm::vec3 chassis_pos = Chassis.Value()->TransformIn.Value()->Position();

    glm::vec3 diff = chassis_pos - FrontWheel1.Value()->Position();
    btVector3 connect_point(diff.x, diff.y, diff.z);
    m_Vehicle->addWheel(connect_point, m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, m_Tunning, true);

    diff = chassis_pos - FrontWheel2.Value()->Position();
    connect_point = btVector3(diff.x, diff.y, diff.z);
    m_Vehicle->addWheel(connect_point, m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, m_Tunning, true);

    diff = chassis_pos - BackWheel1.Value()->Position();
    connect_point = btVector3(diff.x, diff.y, diff.z);
    m_Vehicle->addWheel(connect_point, m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, m_Tunning, false);

    diff = chassis_pos - BackWheel2.Value()->Position();
    connect_point = btVector3(diff.x, diff.y, diff.z);
    m_Vehicle->addWheel(connect_point, m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, m_Tunning, false);

    auto handle = Chassis.Value()->Handle();
    handle->setCenterOfMassTransform(btTransform::getIdentity());
    handle->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
    handle->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
    m_Vehicle->resetSuspension();
    for (int i = 0; i < m_Vehicle->getNumWheels(); i++) {
        m_Vehicle->updateWheelTransform(i, true);
    }

    RegisterUpdateCall();
}

void Vehicle::Update() {
    // Front
    m_Vehicle->applyEngineForce(10.0f, 0);
    //m_Vehicle->setSteeringValue(-0.5f, 0);
    m_Vehicle->applyEngineForce(10.0f, 1);
    //m_Vehicle->setSteeringValue(-0.5f, 1);
   
    // Back
    //m_Vehicle->setBrake(0.0f, 2);
    //m_Vehicle->setBrake(0.0f, 3);

    {
        auto tr = m_Vehicle->getWheelTransformWS(0);
        auto origin = tr.getOrigin();
        glm::vec3 glm_pos(origin.getX(), origin.getY(), origin.getZ());
        auto rot = tr.getRotation();
        glm::quat glm_rot(rot.getW(), rot.getX(), rot.getY(), rot.getZ());
        glm::vec3 glm_scl(m_WheelRadius, m_WheelRadius, m_WheelWidth);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm_pos) * glm::mat4_cast(glm_rot);
        model = glm::scale(model, glm_scl);
        Object().Scene().DrawCuboid(model, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    {
        auto tr = m_Vehicle->getWheelTransformWS(1);
        auto origin = tr.getOrigin();
        glm::vec3 glm_pos(origin.getX(), origin.getY(), origin.getZ());
        auto rot = tr.getRotation();
        glm::quat glm_rot(rot.getW(), rot.getX(), rot.getY(), rot.getZ());
        glm::vec3 glm_scl(m_WheelRadius, m_WheelRadius, m_WheelWidth);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm_pos) * glm::mat4_cast(glm_rot);
        model = glm::scale(model, glm_scl);
        Object().Scene().DrawCuboid(model, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    {
        auto tr = m_Vehicle->getWheelTransformWS(2);
        auto origin = tr.getOrigin();
        glm::vec3 glm_pos(origin.getX(), origin.getY(), origin.getZ());
        auto rot = tr.getRotation();
        glm::quat glm_rot(rot.getW(), rot.getX(), rot.getY(), rot.getZ());
        glm::vec3 glm_scl(m_WheelRadius, m_WheelRadius, m_WheelWidth);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm_pos) * glm::mat4_cast(glm_rot);
        model = glm::scale(model, glm_scl);
        Object().Scene().DrawCuboid(model, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    {
        auto tr = m_Vehicle->getWheelTransformWS(3);
        auto origin = tr.getOrigin();
        glm::vec3 glm_pos(origin.getX(), origin.getY(), origin.getZ());
        auto rot = tr.getRotation();
        glm::quat glm_rot(rot.getW(), rot.getX(), rot.getY(), rot.getZ());
        glm::vec3 glm_scl(m_WheelRadius, m_WheelRadius, m_WheelWidth);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm_pos) * glm::mat4_cast(glm_rot);
        model = glm::scale(model, glm_scl);
        Object().Scene().DrawCuboid(model, glm::vec3(0.0f, 1.0f, 1.0f));
    }
}

void Vehicle::Destroy() {
    Object().Scene().RemoveVehicle(m_Vehicle);

    delete m_VehicleRaycaster;
    delete m_Vehicle;
}

void Vehicle::WheelInfo(float suspension_stiffness, float damping_relaxation, float damping_compression, float friction_slip, float roll_influence) {
    for (int i = 0; i < m_Vehicle->getNumWheels(); i++) {
        btWheelInfo& wheel = m_Vehicle->getWheelInfo(i);

        wheel.m_suspensionStiffness = suspension_stiffness;
        wheel.m_wheelsDampingRelaxation = damping_relaxation;
        wheel.m_wheelsDampingCompression = damping_compression;
        wheel.m_frictionSlip = friction_slip;
        wheel.m_rollInfluence = roll_influence;
    }
}
