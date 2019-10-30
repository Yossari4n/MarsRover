#ifndef DrawManager_h
#define DrawManager_h

#include "ShaderProgram.h"
#include "primitives/Cubemap.h"

#pragma warning(push, 0)
#include <dependencies/imgui/imgui.h>
#include <dependencies/imgui/imgui_impl_opengl3.h>
#include <dependencies/imgui/imgui_impl_glfw.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma warning(pop)

#include <vector>
#include <array>
#include <assert.h>


class Camera;
class IDrawable;
class IShaderProperty;
class IGUIWidget;

enum class EShaderType {
    PureColor = 0,
    PureTexture,
    Phong,
    Skybox,

    Count
};

class DrawManager {
public:
    DrawManager() = default;

    void Initialize();

    void RegisterCamera(Camera* camera);
    Camera* MainCamera() const;

    void Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front);
    void Background(const glm::vec3& background);

    void RegisterDrawCall(const IDrawable* drawable, EShaderType shader);
    void UnregisterDrawCall(const IDrawable* drawable, EShaderType shader);

    void RegisterShaderProperty(const IShaderProperty* property, EShaderType shader);
    void UnregisterShaderProperty(const IShaderProperty* property, EShaderType shader);

    void RegisterWidget(IGUIWidget* widget);
    void UnregisterWidget(IGUIWidget* widget);

    void CallDraws() const;

private:
    glm::vec3 m_Background{ 0.0f };
    std::unique_ptr<Cubemap> m_Skybox{ nullptr };

    Camera* m_Camera{ nullptr };
    std::vector<IGUIWidget*> m_GUIWidgets;

    std::array<ShaderProgram, static_cast<size_t>(EShaderType::Count)> m_ShaderPrograms;
};

#endif
