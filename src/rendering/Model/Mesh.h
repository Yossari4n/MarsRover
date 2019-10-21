#ifndef Mesh_h
#define Mesh_h

#include "../../resources/RawModel/RawMesh.h"
#include "../Texture.h"

#pragma warning(push, 0)
#include <glad/glad.h>
#pragma warning(pop)

#include <vector>

class Mesh {
public:
    explicit Mesh(const RawMesh& raw_mesh);

    Mesh() = delete;
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;
    ~Mesh();

    GLuint VAO() const { return m_VAO; }
    GLuint VBO() const { return m_VBO; }
    GLuint EBO() const { return m_EBO; }
    GLsizei IndicesCount() const { return m_IndicesCount; }
    const std::vector<Texture>& DiffuseTextures() const { return m_DiffuseTextures; }
    const std::vector<Texture>& SpecularTextures() const { return m_SpecularTextures; }
    float Shininess() const { return m_Shininess; }

private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    GLsizei m_IndicesCount;
    std::vector<Texture> m_DiffuseTextures;
    std::vector<Texture> m_SpecularTextures;
    float m_Shininess;
};

#endif