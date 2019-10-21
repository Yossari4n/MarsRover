#include "RawMesh.h"

RawMesh::RawMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<RawTexture*> diffuse, std::vector<RawTexture*> specular, float shininess)
    : m_Vertices(vertices)
    , m_Indices(indices)
    , m_DiffuseTextures(diffuse)
    , m_SpecularTextures(specular)
    , m_Shininess(shininess) {
}
