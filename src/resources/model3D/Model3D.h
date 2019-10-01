#ifndef Model3D_h
#define Model3D_h

#include "Mesh.h"

#include <vector>

/**
 * Texture
 *
 * TODO doc
 * Life time: managed by ResourceManager; parameterized ctor and Free() should be only called by ResourceManager
 * Value semantics: copyable, moveable
 */
class Model3D {
public:
    explicit Model3D(std::vector<Mesh> meshes);

    Model3D() = delete;
    Model3D(const Model3D&) = default;
    Model3D& operator=(const Model3D&) = default;
    Model3D(Model3D&&) = default;
    Model3D& operator=(Model3D&&) = default;
    ~Model3D() = default;

    void Free();

    const std::vector<Mesh>& Meshes() const { return m_Meshes; }

private:
    std::vector<Mesh> m_Meshes;
};

#endif 
