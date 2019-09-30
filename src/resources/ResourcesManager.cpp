#include "ResourcesManager.h"

ResourcesManager::~ResourcesManager() {
    // TODO delete resources
}

Texture& ResourcesManager::GetTexture(std::string path) {
    if (m_Textures.find(path) == m_Textures.end()) {
        int width, height, components;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &components, 0);

        if (!data) {
            std::cout << "Could not load texture at " << path << '\n';
            data = stbi_load(ERROR_TEXTURE_PATH, &width, &height, &components, 0);
        }

        m_Textures.try_emplace(path, data, width, height, components);
        stbi_image_free(data);
    }

    // Using .at instead of operator[] because Texture does not have default ctor
    return m_Textures.at(path);
}

Model3D& ResourcesManager::GetModel3D(std::string path) {
    if (m_Models.find(path) == m_Models.end()) {
        m_Models.try_emplace(path, path, *this);
    }

    // Using .at instead of operator[] because Model3D does not have default ctor
    return m_Models.at(path);
}
