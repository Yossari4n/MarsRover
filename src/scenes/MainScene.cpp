#include "MainScene.h"

#include "../cbs/components/MeshRenderer.h"
#include "../cbs/components/RigidBody.h"
#include "../cbs/components/Camera.h"
#include "../cbs/components/FirstPersonController.h"
#include "../cbs/components/DirectionalLight.h"
#include "../cbs/components/PointLight.h"
#include "../cbs/components/Dummy.h"
#include "../cbs/components/Vehicle.h"
#include "../cbs/components/Controller.h"

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

        auto front_left = rover->CreateComponent<Transform>();
        rover->Connect(rover->Root().This, front_left->Parent);
        front_left->Move(glm::vec3(0.8f, -0.5f, -1.1f));

        auto front_right = rover->CreateComponent<Transform>();
        rover->Connect(rover->Root().This, front_right->Parent);
        front_right->Move(glm::vec3(-0.8f, -0.5f, -1.1f));

        auto back_left = rover->CreateComponent<Transform>();
        rover->Connect(rover->Root().This, back_left->Parent);
        back_left->Move(glm::vec3(-0.8f, -0.5f, 0.8f));

        auto back_right = rover->CreateComponent<Transform>();
        rover->Connect(rover->Root().This, back_right->Parent);
        back_right->Move(glm::vec3(0.8f, -0.5f, 0.8f));

        auto mesh = rover->CreateComponent<MeshRenderer>(LoadModel("resources/models/opportunity/oppy.obj"), EShaderType::Phong);
        rover->Connect(rover->Root().This, mesh->TransformIn);

        auto rigid_body = rover->CreateComponent<RigidBody>(100, new btBoxShape(btVector3(0.5f, 0.25f, 0.75f)));
        rover->Connect(rover->Root().This, rigid_body->TransformIn);

        auto vehicle = rover->CreateComponent<Vehicle>(0.1f, 0.3f, 0.4f, 0.3f);
        rover->Connect(rigid_body->This, vehicle->Chassis);
        rover->Connect(front_left->This, vehicle->FrontWheel1);
        rover->Connect(front_right->This, vehicle->FrontWheel2);
        rover->Connect(back_left->This, vehicle->BackWheel1);
        rover->Connect(back_right->This, vehicle->BackWheel2);

        auto controller = rover->CreateComponent<Controller>(100.0f, 25.0f, 0.5f);
        rover->Connect(vehicle->This, controller->ControlledVehicle);
    }

    auto camera = CreateObject("Camera"); {
        camera->Root().Move(glm::vec3(-10.0f, 0.0f, 0.0f));
        camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), static_cast<float>(g_Window.Width()) / static_cast<float>(g_Window.Height()), 0.1f, 500.0f));
        auto fps = camera->CreateComponent<FirstPersonController>();
        camera->Connect(camera->Root().This, fps->TransformIn);
    }

    auto ground = CreateObject("Ground"); {
        ground->Root().Position(glm::vec3(0.0f, -2.0f, 0.0f));
        auto rigid_body = ground->CreateComponent<RigidBody>(0, new btBoxShape(btVector3(15.0f, 1.0f, 50.0f)));
        ground->Connect(ground->Root().This, rigid_body->TransformIn);
    } 

    Sound& background = LoadSound("resources/audio/ambient.wav");
    std::cout << background.Length();
}
