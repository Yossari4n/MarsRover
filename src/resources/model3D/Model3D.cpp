#include "Model3D.h"

Model3D::Model3D(std::vector<Mesh> meshes)
    : m_Meshes(meshes) {}

void Model3D::Free() {
    for (auto& mesh : m_Meshes) {
        mesh.Free();
    }
}
