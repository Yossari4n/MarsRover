#ifndef MarsRover_h
#define MarsRover_h

#include "Component.h"
#include "../connections/PropertyIn.h"

#include "btBulletDynamicsCommon.h"

class RigidBody;
class MarsRover : public Component {
public:
    MarsRover();
    
    void Initialize() override;
    void Update() override;
    void Destroy() override;

    PropertyIn<RigidBody*> Chassis{ this };
    PropertyIn<RigidBody*> LeftFrontWheel{ this };
    PropertyIn<RigidBody*> RightFrontWheel{ this };
    PropertyIn<RigidBody*> LeftBackWheel{ this };
    PropertyIn<RigidBody*> RightBackWheel{ this };

private:
};

#endif
