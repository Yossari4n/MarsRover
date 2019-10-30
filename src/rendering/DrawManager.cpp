#include "DrawManager.h"

#include "IDrawable.h"
#include "IShaderProperty.h"
#include "IGUIWidget.h"
#include "primitives/Cubemap.h"
#include "../utilities/Window.h"
#include "../rendering/primitives/Cubemap.h"
#include "../cbs/components/Camera.h"

void DrawManager::Initialize() {
    // Dear imgui initialiation
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(g_Window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // Load default font
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();

    // Create shader programs
    m_ShaderPrograms[static_cast<size_t>(EShaderType::PureColor)].AttachShaders("src/shaders/PURE_COLOR.vert",
                                                                                "src/shaders/PURE_COLOR.frag");


    m_ShaderPrograms[static_cast<size_t>(EShaderType::PureTexture)].AttachShaders("src/shaders/PURE_TEXTURE.vert",
                                                                                  "src/shaders/PURE_TEXTURE.frag");


    m_ShaderPrograms[static_cast<size_t>(EShaderType::Phong)].AttachShaders("src/shaders/PHONG.vert",
                                                                            "src/shaders/PHONG.frag");
    m_ShaderPrograms[static_cast<size_t>(EShaderType::Phong)].Traits(ShaderProgram::ETrait::LIGHT_RECEIVER);


    m_ShaderPrograms[static_cast<size_t>(EShaderType::Skybox)].AttachShaders("src/shaders/SKYBOX.vert",
                                                                             "src/shaders/SKYBOX.frag");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
}

void DrawManager::RegisterCamera(Camera *camera) {
    m_Camera = camera;
}

Camera* DrawManager::MainCamera() const {
    return m_Camera;
}

void DrawManager::Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front) {
    m_Skybox = std::make_unique<Cubemap>(right, left, top, bottom, back, front);
}

void DrawManager::Background(const glm::vec3& background) {
    m_Background = background;
}

void DrawManager::RegisterDrawCall(const IDrawable* drawable, EShaderType shader) {
    m_ShaderPrograms[static_cast<size_t>(shader)].RegisterDrawCall(drawable);
}

void DrawManager::UnregisterDrawCall(const IDrawable* drawable, EShaderType shader) {
    m_ShaderPrograms[static_cast<size_t>(shader)].UnregisterDrawCall(drawable);
}

void DrawManager::RegisterShaderProperty(const IShaderProperty* property, EShaderType shader) {
    m_ShaderPrograms[static_cast<size_t>(shader)].RegisterShaderProperty(property);
}

void DrawManager::UnregisterShaderProperty(const IShaderProperty* property, EShaderType shader) {
    m_ShaderPrograms[static_cast<size_t>(shader)].UnregisterShaderProperty(property);
}

void DrawManager::RegisterWidget(IGUIWidget* widget) {
    // Ensure that each widget is registered at most once
    assert(std::find(m_GUIWidgets.begin(), m_GUIWidgets.end(), widget) == m_GUIWidgets.end());

    m_GUIWidgets.push_back(widget);
}

void DrawManager::UnregisterWidget(IGUIWidget* widget) {
    // Unregistering not registered widget has no effect
    auto to_erase = std::find(m_GUIWidgets.begin(), m_GUIWidgets.end(), widget);
    if (to_erase != m_GUIWidgets.end()) {
        m_GUIWidgets.erase(to_erase);
    }
}

void DrawManager::CallDraws() const {
    glClearColor(m_Background.x, m_Background.y, m_Background.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 pv = m_Camera->Projection() * m_Camera->ViewMatrix();

    for (auto shader = m_ShaderPrograms.begin(); shader != m_ShaderPrograms.end(); shader++) {
        shader->Use();

        shader->Uniform("pv", pv);
        shader->Uniform("viewPos", m_Camera->Object().Root().Position());

        shader->CallProperties();
        shader->CallDraws();
    }

    // Draw skybox
    if (m_Skybox != nullptr) {
        glDepthFunc(GL_LEQUAL);
        const ShaderProgram& skybox_shader = m_ShaderPrograms[static_cast<size_t>(EShaderType::Skybox)];

        skybox_shader.Use();
        skybox_shader.Uniform("pv", m_Camera->Projection() * glm::mat4(glm::mat3(m_Camera->ViewMatrix())));

        m_Skybox->Draw(skybox_shader);

        glDepthFunc(GL_LESS);
    }

    // Draw GUI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (auto widget = m_GUIWidgets.begin(); widget != m_GUIWidgets.end(); widget++) {
        (*widget)->Draw();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame();

    // End of drawing
    glfwSwapBuffers(g_Window);
}
