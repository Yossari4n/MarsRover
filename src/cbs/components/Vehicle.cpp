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

    glm::vec3 diff = FrontWheel1.Value()->Position() - chassis_pos;
    m_Vehicle->addWheel(btVector3(diff.x, diff.y, diff.z), m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, m_Tunning, true);

    diff = FrontWheel2.Value()->Position(); - chassis_pos;
    m_Vehicle->addWheel(btVector3(diff.x, diff.y, diff.z), m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, m_Tunning, true);

    diff = BackWheel1.Value()->Position() - chassis_pos;
    m_Vehicle->addWheel(btVector3(diff.x, diff.y, diff.z), m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, m_Tunning, false);

    diff = BackWheel2.Value()->Position() - chassis_pos;
    m_Vehicle->addWheel(btVector3(diff.x, diff.y, diff.z), m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, m_Tunning, false);

    for (int i = 0; i < m_Vehicle->getNumWheels(); i++) {
        btWheelInfo& wheel = m_Vehicle->getWheelInfo(i);

        // Hardcoded for now
        wheel.m_suspensionStiffness = 20.0f;
        wheel.m_wheelsDampingRelaxation = 2.3f;
        wheel.m_wheelsDampingCompression = 4.4f;
        wheel.m_frictionSlip = 1000.0f;
        wheel.m_rollInfluence = 0.1f;
    }

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
    m_Vehicle->applyEngineForce(100, 0);
    m_Vehicle->applyEngineForce(100, 1);
    // TODO change this monstrosity
    {
        auto tr = m_Vehicle->getWheelTransformWS(0);
        auto origin = tr.getOrigin();
        glm::vec3 glm_pos(origin.getX(), origin.getY(), origin.getZ());
        auto rot = tr.getRotation();
        glm::quat glm_rot(rot.getW(), rot.getX(), rot.getY(), rot.getZ());
        glm::vec3 glm_scl(m_WheelWidth, m_WheelRadius, m_WheelRadius);
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
        glm::vec3 glm_scl(m_WheelWidth, m_WheelRadius, m_WheelRadius);
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
        glm::vec3 glm_scl(m_WheelWidth, m_WheelRadius, m_WheelRadius);
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
        glm::vec3 glm_scl(m_WheelWidth, m_WheelRadius, m_WheelRadius);
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

void Vehicle::ApplyEngineForce(float force) {}

void Vehicle::Brake(float brake) {}

void Vehicle::Steer(float steering) {}
