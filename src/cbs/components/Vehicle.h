#ifndef Vehicle_h
#define Vehicle_h

#include "Component.h"
#include "../connections/PropertyIn.h"
#include "../connections/PropertyOut.h"
#include "../connections/MessageIn.h"

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Vehicle/btRaycastVehicle.h"

class RigidBody;
class Transform;
class Vehicle : public Component {
public:
    Vehicle(float suspension_rest_length, float steering_clamp, float wheel_radius, float wheel_width);
    
    void Initialize() override;
    void Update() override;
    void Destroy() override;

    void ApplyEngineForce(float force);
    void Brake(float brake);
    void Steer(float steering);

    PropertyOut<Vehicle*> This{ this, this };
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

    float m_MaxEngineForce{ 0.0f };
    float m_MaxBreakingForce{ 0.0f };
    float m_VehicleSteering{ 0.0f }; 
    btVector3 m_WheelDirectionCS0{ 0, -1, 0 };
    btVector3 m_WheelAxleCS{ 1, 0, 0 };

    // TODO calculate based on Transforms
    float m_WheelRadius;
    float m_WheelWidth;
};

#endif
