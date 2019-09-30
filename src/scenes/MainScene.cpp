#include "MainScene.h"

#include "../cbs/components/MeshRenderer.h"
#include "../cbs/components/Camera.h"
#include "../cbs/components/FirstPersonController.h"
#include "../cbs/components/DirectionalLight.h"
#include "../cbs/components/PointLight.h"

void MainScene::CreateScene() {
    FrameRateLimit(60);
    Skybox("resources/skyboxes/basic_blue/right.png",
           "resources/skyboxes/basic_blue/left.png",
           "resources/skyboxes/basic_blue/top.png",
           "resources/skyboxes/basic_blue/bottom.png",
           "resources/skyboxes/basic_blue/back.png",
           "resources/skyboxes/basic_blue/front.png");

    auto light = CreateObject("Light"); {
        light->CreateComponent<DirectionalLight>(glm::vec3(-0.2f, -0.5f, 0.3f),
                                                 glm::vec3(0.05f),
                                                 glm::vec3(0.7f),
                                                 glm::vec3(0.8f));
    }

    auto rover = CreateObject("Rover"); {
        rover->Root().Scale(glm::vec3(0.1f));
        auto mesh = rover->CreateComponent<MeshRenderer>(GetModel("resources/models/opportunity/oppy.obj"), ShaderProgram::EType::Phong);
        rover->Connect(rover->Root().ModelOut, mesh->ModelIn);
    }

    auto camera = CreateObject("Camera"); {
        camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), static_cast<float>(g_Window.Width()) / static_cast<float>(g_Window.Height()), 0.1f, 5000.0f));
        camera->CreateComponent<FirstPersonController>();
    }
}