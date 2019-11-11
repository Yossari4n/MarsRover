#ifndef Vehicle_h
#define Vehicle_h

#include "Component.h"
#include "../connections/PropertyIn.h"

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Vehicle/btRaycastVehicle.h"

constexpr float DEFAULT_BREAKING_FORCE = 10.0f;

class RigidBody;
class Vehicle : public Component {
public:
    Vehicle();
    
    void Initialize() override;
    void Update() override;
    void Destroy() override;

    PropertyIn<RigidBody*> Chassis{ this };
    PropertyIn<RigidBody*> LeftFrontWheel{ this };
    PropertyIn<RigidBody*> RightFrontWheel{ this };
    PropertyIn<RigidBody*> LeftBackWheel{ this };
    PropertyIn<RigidBody*> RightBackWheel{ this };

private:
    btRaycastVehicle* m_Vehicle;
    btVehicleRaycaster* m_VehicleRaycaster;
    btRaycastVehicle::btVehicleTuning m_Tunning;

    // Hardcoded for now
    float m_EngineForce{ 1000.0f };
    float m_BreakingForce{ 100.0f };
    float m_VehicleSteering{ 0.0f };

    float m_MaxEngineForce{ 1000.0f };
    float m_MaxBreakingForce{ 100.0f };
    float m_SteeringIncrement{ 0.04f };
    float m_SteeringClamp{ 0.3f };

    // Remove?
    float m_WheelRadius{ 0.5f };
    float m_WheelWidth{ 0.4f };

    // btWheelInfo
    float m_WheelFriction{ 1.0f };
    float m_SuspensionStiffness{ 10.0f };
    float m_SuspensionDamping{ 2.3f };
    float m_SuspensionCompression{ 100.4f };
    float m_RollInfluence{ 1.0f };

    btScalar m_SuspensionRestLength{ 0.6f };
    btVector3 m_WheelDirectionCS0{ 0, -1, 0 };
    btVector3 m_WheelAxleCS{ -1, 0, 0 };
};

#endif
