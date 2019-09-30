#ifndef Model3D_h
#define Model3D_h

#include "Mesh.h"

#pragma warning(push, 0)
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <string>
#include <vector>
#pragma warning(pop)

class ResourcesManager;

class Model3D {
public:
    Model3D(std::string path, ResourcesManager& manager);

    std::string FilePath() const { return m_Path; }
    const std::vector<Mesh>& Meshes() const { return m_Meshes; }

private:
    void Load(ResourcesManager& manager);
    void LoadNode(const aiNode* node, const aiScene* scene, std::string directory, ResourcesManager& manager);
    void LoadMesh(const aiMesh* mesh, const aiScene* scene, std::string directory, ResourcesManager& manager);

    std::string m_Path;
    std::vector<Mesh> m_Meshes;
};

#endif 
