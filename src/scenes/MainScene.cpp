#include "MainScene.h"

#include "../cbs/components/MeshRenderer.h"
#include "../cbs/components/RigidBody.h"
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
        rover->Root().Rotate(glm::vec3(glm::radians(93.0f), glm::radians(21.0f), glm::radians(87.0f)));
        auto mesh = rover->CreateComponent<MeshRenderer>(GetModel("resources/models/opportunity/oppy.obj"), ShaderProgram::EType::Phong);
        auto rigid_body = rover->CreateComponent<RigidBody>(btScalar(1.0f), new btBoxShape(btVector3(0.1f, 0.1f, 0.1f)));
        rover->Connect(rover->Root().ModelOut, mesh->ModelIn);
    }

    auto camera = CreateObject("Camera"); {
        camera->Root().Position(glm::vec3(-17.5f, -10.0f, 0.0f));
        camera->CreateComponent<Camera>(glm::perspective(glm::radians(45.0f), static_cast<float>(g_Window.Width()) / static_cast<float>(g_Window.Height()), 0.1f, 100.0f));
        camera->CreateComponent<FirstPersonController>();
    }

    btBoxShape* groundShape = new btBoxShape(btVector3(btScalar(50.0f), btScalar(0.1f), btScalar(50.0f)));
    btTransform groundTrans;
    groundTrans.setIdentity();
    groundTrans.setOrigin(btVector3(0, -15, 0));
    btDefaultMotionState* motion_state = new btDefaultMotionState(groundTrans);
    btRigidBody::btRigidBodyConstructionInfo info(0.0f, motion_state, groundShape);

    btRigidBody* ground = new btRigidBody(info);
    AddRigidBody(ground);
}