#ifndef MeshObject_h
#define MeshObject_h

#include "Mesh.h"

#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <string>
#include <vector>

class ResourcesManager;

class Model3D {
public:
    Model3D(std::string path, ResourcesManager& manager);

private:
    void Load(ResourcesManager& manager);
    void LoadNode(const aiNode* node, const aiScene* scene, std::string directory, ResourcesManager& manager);
    void LoadMesh(const aiMesh* mesh, const aiScene* scene, std::string directory, ResourcesManager& manager);

    std::string m_Path;
    std::vector<Mesh> m_Meshes;
};

#endif 
