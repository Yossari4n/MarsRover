#ifndef Vehicle_h
#define Vehicle_h

#include "Component.h"
#include "../connections/PropertyIn.h"

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Vehicle/btRaycastVehicle.h"

constexpr float DEFAULT_BREAKING_FORCE = 10.0f;

class RigidBody;
class Transform;
class Vehicle : public Component {
public:
    Vehicle(float suspension_rest_length, float steering_clamp, float wheel_radius, float wheel_width);
    
    void Initialize() override;
    void Update() override;
    void Destroy() override;

    void WheelInfo(float suspension_stiffness, float damping_relaxation, float damping_compression, float friction_slip, float roll_influence);

    PropertyIn<RigidBody*> Chassis{ this };
    PropertyIn<Transform*> FrontWheel1{ this };
    PropertyIn<Transform*> FrontWheel2{ this };
    PropertyIn<Transform*> BackWheel1{ this };
    PropertyIn<Transform*> BackWheel2{ this };

private:
    btRaycastVehicle* m_Vehicle;
    btVehicleRaycaster* m_VehicleRaycaster;
    btRaycastVehicle::btVehicleTuning m_Tunning;

    float m_SteeringClamp;
    btScalar m_SuspensionRestLength;

    float m_EngineForce{ 0.0f };
    float m_BreakingForce{ 0.0f };
    float m_VehicleSteering{ 0.0f }; 
    btVector3 m_WheelDirectionCS0{ 0, -1, 0 };
    btVector3 m_WheelAxleCS{ 1, 0, 0 };

    // Remove?
    float m_WheelRadius{ 0.5f };
    float m_WheelWidth{ 0.4f };
};

#endif
