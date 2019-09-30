#ifndef Mesh_h
#define Mesh_h

#include "../Texture.h"
#include "../../rendering/ShaderProgram.h"

#pragma warning(push, 0)
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <stb/stb_image.h>

#include <iostream>
#include <string>
#include <vector>
#pragma warning(pop)

class Mesh {
public:
    struct Vertex {
        glm::vec3 Position{ 0.0f };
        glm::vec3 Normal{ 0.0f };
        glm::vec2 TexCoords{ 0.0f };
    };

    Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies, std::vector<Texture> textures);

    Mesh() = delete;
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;
    ~Mesh();

    void Draw(const ShaderProgram& shader) const;

    GLuint VAO() const { return m_VAO; }
    GLuint VBO() const { return m_VBO; }
    GLuint EBO() const { return m_EBO; }
    GLsizei IndicesCount() const { return m_IndicesCount; }
    const std::vector<Texture>& Textures() const { return m_Textures; }

private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    GLsizei m_IndicesCount;
    std::vector<Texture> m_Textures;
};

#endif
