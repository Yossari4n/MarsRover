#include "MainScene.h"

#include "../cbs/components/MeshRenderer.h"
#include "../cbs/components/RigidBody.h"
#include "../cbs/components/Camera.h"
#include "../cbs/components/FirstPersonController.h"
#include "../cbs/components/DirectionalLight.h"
#include "../cbs/components/PointLight.h"
#include "../cbs/components/Dummy.h"
#include "../cbs/components/Vehicle.h"

void MainScene::CreateScene() {
    FrameRateLimit(60);
    Skybox("resources/skyboxes/mars/right.png",
           "resources/skyboxes/mars/left.png",
           "resources/skyboxes/mars/top.png",
           "resources/skyboxes/mars/bottom.png",
           "resources/skyboxes/mars/back.png",
           "resources/skyboxes/mars/front.png");

    auto light = CreateObject("Light"); {
        light->CreateComponent<DirectionalLight>(glm::vec3(-0.2f, -0.5f, 0.3f),
                                                 glm::vec3(0.05f),
                                                 glm::vec3(0.7f),
                                                 glm::vec3(0.8f));
    }

    auto rover = CreateObject("Rover"); {
        rover->Root().Scale(glm::vec3(0.1f));
        auto mesh = rover->CreateComponent<MeshRenderer>(GetModel("resources/models/opportunity/oppy.obj"), EShaderType::Phong);
        auto rigid_body = rover->CreateComponent<RigidBody>(btScalar(800.0f), new btBoxShape(btVector3(1.0f, 0.1f, 0.5f)));
        auto vehicle = rover->CreateComponent<Vehicle>();
        rover->Connect(rover->Root().ModelOut, mesh->ModelIn);
        rover->Connect(rigid_body->This, vehicle->Chassis);
    }

    auto camera = CreateObject("Camera"); {
        camera->Root().Move(glm::vec3(-5.0f, 0.0f, 0.0f));
        camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), static_cast<float>(g_Window.Width()) / static_cast<float>(g_Window.Height()), 0.1f, 100.0f));
        camera->CreateComponent<FirstPersonController>();
    }

    auto ground = CreateObject("Ground"); {
        ground->Root().Position(glm::vec3(0.0f, -1.0f, 0.0f));
        ground->CreateComponent<RigidBody>(btScalar(0.0f), new btBoxShape(btVector3(50.0f, 0.1f, 50.0f)));
    }
}
