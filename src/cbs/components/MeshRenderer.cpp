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

    auto end = m_Model3D.Meshes().end();
    for (auto it = m_Model3D.Meshes().begin(); it != end; it++) {
        DrawMesh(shader, *it);
    }
}

void MeshRenderer::DrawMesh(const ShaderProgram& shader, const Mesh& mesh) const {
    const auto size = mesh.Textures().size();
    for (GLuint i = 0; i < size; i++) {
        const auto& texture = mesh.Textures()[i];

        glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
        shader.Uniform("material." + texture.TypeName(), static_cast<int>(i));
        glBindTexture(GL_TEXTURE_2D, texture.ID());
    }

    glBindVertexArray(mesh.VAO());
    glDrawElements(GL_TRIANGLES, mesh.IndicesCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}
