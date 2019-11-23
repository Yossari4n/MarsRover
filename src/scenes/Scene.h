#ifndef Scene_hpp
#define Scene_hpp

#include "../physics/PhysicsManager.h"
#include "../cbs/ObjectManager.h"
#include "../rendering/DrawManager.h"
#include "../resources/ResourcesManager.h"
#include "../audio/AudioManager.h"

#include "../utilities/Time.h"
#include "../utilities/Input.h"
#include "../utilities/Window.h"

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    Scene(Scene&&) = delete;
    Scene& operator=(Scene&&) = delete;

    virtual void CreateScene() = 0;

    void PreRun();
    void Run();
    void PostRun();

    void Exit();
    void FrameRateLimit(unsigned int frame_rate);
    float FrameRate() const { return 1.0f / g_Time.DeltaTime(); }

    // ObjectManger functions
    Object* CreateObject(const std::string& name);
    void DestroyObject(const std::string& name);
    void DestroyObject(Object::ID_t id);

    // DrawManager functions
    void RegisterDrawCall(const IDrawable* drawable, EShaderType shader);
    void UnregisterDrawCall(const IDrawable* drawable, EShaderType shader);
    void RegisterShaderProperty(const IShaderProperty* property, EShaderType shader);
    void UnregisterShaderProperty(const IShaderProperty* property, EShaderType shader);
    void RegisterGUIWidget(IGUIWidget* widget);
    void UnregisterGUIWidget(IGUIWidget* widget);
    void DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color);
    void DrawPlane(glm::mat4 model, glm::vec3 color);
    void DrawCuboid(glm::mat4 model, glm::vec3 color);
    void RegisterCamera(Camera* camera);
    Camera* MainCamera() const;
    void Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front);
    void Background(const glm::vec3& background);

    // PhysicsManager functions
    void RegisterPhysicalObject(IPhysicalObject* physical_object);
    void UnregisterPhysicalObject(IPhysicalObject* physical_object);
    void AddRigidBody(btRigidBody* rigid_body);
    void RemoveRigidBody(btRigidBody* rigid_body);
    void AddConstraint(btTypedConstraint* constraint, bool disable_collisions_between_linked_bodies = false);
    void RemoveConstraint(btTypedConstraint* constraint);
    void AddVehicle(btActionInterface* vehicle);
    void RemoveVehicle(btActionInterface* vehicle);
    void Gravity(const btVector3& gravity);
    btVector3 Gravity() const;
    btDynamicsWorld* DynamicsWorld();

    // ResourceManager functions
    RawTexture& LoadTexture(const std::string& path);
    RawModel& LoadModel(const std::string& path);
    Sound& LoadSound(const std::string& path);

private:
    ObjectManager m_ObjectManager{ *this };
    DrawManager m_DrawManager{};
    PhysicsManager m_PhysicsManager{};
    AudioManager m_AudioManager{};
    ResourcesManager m_ResourceManager{};

    bool m_Running{ false };
    float m_FrameRateLimit{ 0.0f };
};

#endif
