#include "Vehicle.h"

#include "../Object.h"
#include "../../scenes/Scene.h"
#include "RigidBody.h"

Vehicle::Vehicle()
    : m_VehicleRaycaster(nullptr)
    , m_Vehicle(nullptr) {
}

void Vehicle::Initialize() {
    m_VehicleRaycaster = new btDefaultVehicleRaycaster(Object().Scene().DynamicsWorld());
    m_Vehicle = new btRaycastVehicle(m_Tunning, Chassis.Value()->Handle(), m_VehicleRaycaster);

    Chassis.Value()->Handle()->setActivationState(DISABLE_DEACTIVATION);

    Object().Scene().AddVehicle(m_Vehicle);

    m_Vehicle->setCoordinateSystem(0, 1, 2);

    float connect_height = 1.2f;

    btVector3 connect_point(1.0f - (0.3f * m_WheelWidth), connect_height, 2.0f - m_WheelRadius);
    m_Vehicle->addWheel(connect_point, m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, m_Tunning, true);

    connect_point = btVector3(1.0f + (0.3f * m_WheelWidth), connect_height, 2.0f - m_WheelRadius);
    m_Vehicle->addWheel(connect_point, m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, m_Tunning, true);

    connect_point = btVector3(1.0f - (0.3f * m_WheelWidth), connect_height, -2.0f - m_WheelRadius);
    m_Vehicle->addWheel(connect_point, m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, m_Tunning, false);

    connect_point = btVector3(1.0f + (0.3f * m_WheelWidth), connect_height, -2.0f - m_WheelRadius);
    m_Vehicle->addWheel(connect_point, m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, m_Tunning, false);

    for (int i = 0; i < m_Vehicle->getNumWheels(); i++) {
        btWheelInfo& wheel = m_Vehicle->getWheelInfo(i);

        wheel.m_suspensionStiffness = m_SuspensionStiffness;
        wheel.m_wheelsDampingRelaxation = m_SuspensionDamping;
        wheel.m_wheelsDampingCompression = m_SuspensionCompression;
        wheel.m_frictionSlip = m_WheelFriction;
        wheel.m_rollInfluence = m_RollInfluence;
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
    // Front
    m_Vehicle->applyEngineForce(m_EngineForce, 0);
    m_Vehicle->setSteeringValue(m_VehicleSteering, 0);
    m_Vehicle->applyEngineForce(m_EngineForce, 1);
    m_Vehicle->setSteeringValue(m_VehicleSteering, 1);

    // Back
    m_Vehicle->setBrake(m_BreakingForce, 2);
    m_Vehicle->setBrake(m_BreakingForce, 3);
}

void Vehicle::Destroy() {
    Object().Scene().RemoveVehicle(m_Vehicle);
}
