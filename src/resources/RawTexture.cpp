#include "RawTexture.h"

RawTexture::RawTexture(const std::string& path) 
    : m_Path(path) {
    m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Components, 0);
}

RawTexture::~RawTexture() {
    stbi_image_free(m_Data);
}
