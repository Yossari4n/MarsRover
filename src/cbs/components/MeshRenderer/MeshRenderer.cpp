#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(ShaderProgram::EType type)
    : Drawable(type) {

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
}
