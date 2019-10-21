#include "ResourcesManager.h"

RawTexture& ResourcesManager::GetTexture(std::string path) {
    if (m_Textures.find(path) == m_Textures.end()) {
        m_Textures.try_emplace(path, path);
    }

    return m_Textures.at(path);
}

RawModel& ResourcesManager::GetModel(std::string path) {
    if (m_Models.find(path) == m_Models.end()) {
        m_Models.try_emplace(path, path, *this);
    }

    return m_Models.at(path);
}
