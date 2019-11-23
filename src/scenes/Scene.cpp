#include "Scene.h"

void Scene::PreRun() {
    m_DrawManager.Initialize();
    m_PhysicsManager.Initialize();
    m_AudioManager.Initialize();
}

void Scene::Run() {
    m_Running = true;
    m_ObjectManager.InitializeObjects();

    // Initialize Time manager as close to game loop as possible
    // to avoid misrepresented delta time
    g_Time.Initialize();
    
    // Game loop
    while (m_Running && !glfwWindowShouldClose(g_Window)) {
        // If frame rate is greater than limit then wait
        do {
            g_Time.Hold();
            glfwPollEvents();
        } while (g_Time.DeltaTime() < m_FrameRateLimit);
        
        // Update global systems
        g_Time.Update();
        g_Input.Update(g_Window);
        
        // Managers
        m_PhysicsManager.StepSimulation(g_Time.DeltaTime());
        m_ObjectManager.UpdateObjects();
        m_DrawManager.CallDraws();
    }
}

void Scene::PostRun() {
    m_ObjectManager.DestroyObjects();
    m_PhysicsManager.ExitPhysics();
}

void Scene::Exit() {
    m_Running = false;
}

void Scene::FrameRateLimit(unsigned int frame_rate) {
    m_FrameRateLimit = frame_rate != 0 ? 1.0f / (float)frame_rate : 0.0f;
}

Object* Scene::CreateObject(const std::string& name) {
    return m_ObjectManager.CreateObject(name);
}

void Scene::DestroyObject(const std::string& name) {
    m_ObjectManager.DestroyObject(name);
}

void Scene::DestroyObject(Object::ID_t id) {
    m_ObjectManager.DestroyObject(id);
}

void Scene::RegisterDrawCall(const IDrawable* drawable, EShaderType shader) {
    m_DrawManager.RegisterDrawCall(drawable, shader);
}

void Scene::UnregisterDrawCall(const IDrawable* drawable, EShaderType shader) {
    m_DrawManager.UnregisterDrawCall(drawable, shader);
}

void Scene::RegisterShaderProperty(const IShaderProperty* property, EShaderType shader) {
    m_DrawManager.RegisterShaderProperty(property, shader);
}

void Scene::UnregisterShaderProperty(const IShaderProperty* property, EShaderType shader) {
    m_DrawManager.UnregisterShaderProperty(property, shader);
}

void Scene::RegisterGUIWidget(IGUIWidget* widget) {
    m_DrawManager.RegisterGUIWidget(widget);
}

void Scene::UnregisterGUIWidget(IGUIWidget* widget) {
    m_DrawManager.UnregisterGUIWidget(widget);
}

void Scene::DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color) {
    m_DrawManager.DrawLine(start, end, color);
}

void Scene::DrawPlane(glm::mat4 model, glm::vec3 color) {
    m_DrawManager.DrawPlane(model, color);
}

void Scene::DrawCuboid(glm::mat4 model, glm::vec3 color) {
    m_DrawManager.DrawCuboid(model, color);
}

void Scene::RegisterCamera(Camera* camera) {
    m_DrawManager.RegisterCamera(camera);
}

Camera* Scene::MainCamera() const {
    return m_DrawManager.MainCamera();
}

void Scene::Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front) {
    m_DrawManager.Skybox(right, left, top, bottom, back, front);
}

void Scene::Background(const glm::vec3& background) {
    m_DrawManager.Background(background);
}

void Scene::RegisterPhysicalObject(IPhysicalObject* component) {
    m_PhysicsManager.RegisterPhysicalObject(component);
}

void Scene::UnregisterPhysicalObject(IPhysicalObject* component) {
    m_PhysicsManager.UnregisterPhysiaclObject(component);
}

void Scene::AddRigidBody(btRigidBody* rigid_body) {
    m_PhysicsManager.AddRigidBody(rigid_body);
}

void Scene::RemoveRigidBody(btRigidBody* rigid_body) {
    m_PhysicsManager.RemoveRigidBody(rigid_body);
}

void Scene::AddConstraint(btTypedConstraint* constraint, bool disable_collisions_between_linked_bodies) {
    m_PhysicsManager.AddConstraint(constraint, disable_collisions_between_linked_bodies);
}

void Scene::RemoveConstraint(btTypedConstraint* constraint) {
    m_PhysicsManager.RemoveConstraint(constraint);
}

void Scene::AddVehicle(btActionInterface* vehicle) {
    m_PhysicsManager.AddVehicle(vehicle);
}

void Scene::RemoveVehicle(btActionInterface* vehicle) {
    m_PhysicsManager.RemoveVehicle(vehicle);
}

void Scene::Gravity(const btVector3& gravity) {
    m_PhysicsManager.Gravity(gravity);
}

btVector3 Scene::Gravity() const {
    return m_PhysicsManager.Gravity();
}

btDynamicsWorld* Scene::DynamicsWorld() {
    return m_PhysicsManager.DynamicsWorld();
}

RawTexture& Scene::LoadTexture(const std::string& path) {
    return m_ResourceManager.LoadTexture(path);
}

RawModel& Scene::LoadModel(const std::string& path) {
    return m_ResourceManager.LoadModel(path);
}

Sound& Scene::LoadSound(const std::string& path) {
    return m_ResourceManager.LoadSound(path);
}
