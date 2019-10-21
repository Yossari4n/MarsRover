#ifndef RawMesh_h
#define RawMesh_h

#include "../RawTexture.h"
#include "../../rendering/ShaderProgram.h"

#pragma warning(push, 0)
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <vector>
#pragma warning(pop)

class RawMesh {
public:
    struct Vertex {
        glm::vec3 Position{ 0.0f };
        glm::vec3 Normal{ 0.0f };
        glm::vec2 TexCoords{ 0.0f };
    };

    RawMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<RawTexture*> diffuse, std::vector<RawTexture*> specular, float shininess);

    RawMesh() = delete;
    RawMesh(const RawMesh&) = default;
    RawMesh& operator=(const RawMesh&) = default;
    RawMesh(RawMesh&& other) = default;
    RawMesh& operator=(RawMesh&& other) = default;
    ~RawMesh() = default;

    const std::vector<Vertex>& Vertices() const { return m_Vertices; }
    const std::vector<unsigned int>& Indices() const { return m_Indices; }
    const std::vector<RawTexture*>& DiffuseTextures() const { return m_DiffuseTextures; }
    const std::vector<RawTexture*>& SpecularTextures() const { return m_SpecularTextures; }
    float Shininess() const { return m_Shininess; }

private:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<RawTexture*> m_DiffuseTextures;
    std::vector<RawTexture*> m_SpecularTextures;
    float m_Shininess;
};

#endif
