#ifndef ResourcesManager_h
#define ResourcesManager_h

#include "RawTexture.h"
#include "RawModel/RawModel.h"
#include "../debuging/Logger.h"

#include <string>
#include <unordered_map>

constexpr const char* ERROR_TEXTURE_PATH = "resources/textures/ErrorTexture.png";
constexpr const char* ERROR_MODEL3D_PATH = "resources/models/ErrorMesh/ErrorMesh.obj";

class ResourcesManager {
public:
    RawTexture& GetTexture(std::string path);
    RawModel& GetModel(std::string path);

private:
    std::unordered_map<std::string, RawTexture> m_Textures;
    std::unordered_map<std::string, RawModel> m_Models;
};

#endif 
