#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(RawModel& raw_model, ShaderProgram::EType type)
    : Drawable(type)
    , m_Model(raw_model) {
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

    auto end = m_Model.Meshes().end();
    for (auto it = m_Model.Meshes().begin(); it != end; it++) {
        DrawMesh(shader, *it);
    }
}

void MeshRenderer::DrawMesh(const ShaderProgram& shader, const Mesh& mesh) const {
    auto size = mesh.DiffuseTextures().size();
    GLuint tex_index = 0;
    for (; tex_index < size; tex_index++) {
        const auto& texture = mesh.DiffuseTextures()[tex_index];

        glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(tex_index));
        shader.Uniform("material.diffuse", static_cast<int>(tex_index));
        glBindTexture(GL_TEXTURE_2D, texture.ID());
    }

    size = mesh.SpecularTextures().size();
    for (; tex_index < size; tex_index++) {
        const auto& texture = mesh.SpecularTextures()[tex_index];

        glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(tex_index));
        shader.Uniform("material.specular", static_cast<int>(tex_index));
        glBindTexture(GL_TEXTURE_2D, texture.ID());
    }

    shader.Uniform("material.shininess", mesh.Shininess());

    glBindVertexArray(mesh.VAO());
    glDrawElements(GL_TRIANGLES, mesh.IndicesCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}
