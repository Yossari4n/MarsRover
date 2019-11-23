#include "Controller.h"
#include "Vehicle.h"

Controller::Controller(float engine_force, float breaking_force, float steering)
    : m_MaxEngineForce(engine_force) 
    , m_MaxBreakingForce(breaking_force)
    , m_MaxSteering(steering) {

}

void Controller::Initialize() {
    assert(ControlledVehicle.Connected());

    RegisterUpdateCall();
}

void Controller::Update() {
    const float delta = g_Time.FixedDeltaTime();

    m_CurrEngineForce = 0.0f;
    m_CurrBreakingForce = 0.0f;
    m_CurrSteering = 0.0f;

    if (g_Input.KeyHold(m_Forward)) {
        m_CurrEngineForce = m_MaxEngineForce;
    } else if (g_Input.KeyHold(m_Backward)) {
        m_CurrBreakingForce = m_MaxBreakingForce;
    }

    if (g_Input.KeyHold(m_Left)) {
        m_CurrSteering = m_MaxSteering;
    } else if (g_Input.KeyHold(m_Right)) {
        m_CurrSteering = -m_MaxSteering;
    }

    ControlledVehicle.Value()->ApplyEngineForce(m_CurrEngineForce);
    ControlledVehicle.Value()->Brake(m_CurrBreakingForce);
    ControlledVehicle.Value()->Steer(m_CurrSteering);
}
