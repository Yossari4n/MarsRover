#ifndef ResourcesManager_h
#define ResourcesManager_h

#include "Texture.h"
#include "Model3D/Model3D.h"

#pragma warning(push, 0)
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stb/stb_image.h>

#include <string>
#include <unordered_map>
#pragma warning(pop)

constexpr const char* ERROR_TEXTURE_PATH = "resources/texture/ErrorTexture.png";
constexpr const char* ERROR_MODEL3D_PATH = ""; // TODO

class ResourcesManager {
public:
    ~ResourcesManager();

    Texture GetTexture(std::string path);
    void GetModel3D(std::string path);

private:
    std::unordered_map<std::string, Texture> m_Textures;
    std::unordered_map<std::string, Model3D> m_Model;
};

#endif 
