#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(Model3D& model, ShaderProgram::EType type)
    : Drawable(type)
    , m_Model3D(model) {
}

void MeshRenderer::MakeConnectors(MessageManager& message_manager) {
    message_manager.Make(this, ModelIn);
}

void MeshRenderer::Initialize() {
    Object().Scene().RegisterDrawCall(this);
}

void MeshRenderer::Destroy() {
    Object().Scene().UnregisterDrawCall(this);
}

void MeshRenderer::Draw(const ShaderProgram& shader) const {
    shader.Uniform("model", ModelIn);
    m_Model3D.Draw(shader);
}
