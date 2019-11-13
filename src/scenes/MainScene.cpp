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
        auto rigid_body = rover->CreateComponent<RigidBody>(400, new btBoxShape(btVector3(0.5f, 0.25f, 0.75f)));
        auto vehicle = rover->CreateComponent<Vehicle>();

        rover->Connect(rover->Root().ModelOut, mesh->ModelIn);
        rover->Connect(rover->Root().TransformOut, rigid_body->TransformIn);

        rover->Connect(rigid_body->This, vehicle->Chassis);
    }

    auto camera = CreateObject("Camera"); {
        camera->Root().Move(glm::vec3(-10.0f, 0.0f, 0.0f));
        camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), static_cast<float>(g_Window.Width()) / static_cast<float>(g_Window.Height()), 0.1f, 500.0f));
        camera->CreateComponent<FirstPersonController>();
    }

    auto ground = CreateObject("Ground"); {
        ground->Root().Position(glm::vec3(0.0f, -3.0f, 0.0f));
        auto rigid_body = ground->CreateComponent<RigidBody>(0, new btBoxShape(btVector3(15.0f, 1.0f, 15.0f)));
        ground->Connect(ground->Root().TransformOut, rigid_body->TransformIn);
    }
}
