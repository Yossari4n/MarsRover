#ifndef ResourcesManager_h
#define ResourcesManager_h

#include "Texture.h"
#include "Model3D/Model3D.h"
#include "../debuging/Logger.h"

#pragma warning(push, 0)
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stb/stb_image.h>

#include <string>
#include <unordered_map>
#pragma warning(pop)

constexpr const char* ERROR_TEXTURE_PATH = "resources/textures/ErrorTexture.png";
constexpr const char* ERROR_MODEL3D_PATH = "resources/models/ErrorMesh/ErrorMesh.obj";

class ResourcesManager {
public:
    ResourcesManager() = default;
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;
    ResourcesManager(ResourcesManager&&) = delete;
    ResourcesManager& operator=(ResourcesManager&&) = delete;
    ~ResourcesManager();

    Texture& GetTexture(std::string path);
    Model3D& GetModel3D(std::string path);

private:
    std::vector<Mesh> LoadNode(const aiNode* node, const aiScene* scene, std::string directory);
    Mesh LoadMesh(const aiMesh* mesh, const aiScene* scene, std::string directory);

    std::unordered_map<std::string, Texture> m_Textures;
    std::unordered_map<std::string, Model3D> m_Models;
};

#endif 
