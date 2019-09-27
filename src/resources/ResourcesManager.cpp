#include "ResourcesManager.h"

ResourcesManager::~ResourcesManager() {
    // delete resources
}

Texture ResourcesManager::GetTexture(std::string path) {
    if (m_Textures.find(path) == m_Textures.end()) {
        int width, height, components;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &components, 0);

        m_Textures.try_emplace(path, data, width, height, components);
    }

    return m_Textures[path];
}

void ResourcesManager::GetModel3D(std::string path) {
    Model3D test(path, *this);
}
