#include "Texture.h"

Texture::Texture(const unsigned char* data, int width, int height, int components) 
    : m_Width(width)
    , m_Height(height)
    , m_Components(components)
    , m_Type(EType::Unknown) {

    const GLenum format = [=]() {
        switch (m_Components) {
        case 1:
            return GL_RED;

        case 3:
            return GL_RGB;

        case 4:
            return GL_RGBA;

        default:
            assert(true && "Wrong components value");
            return -1;
        }
    }();

    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

std::string Texture::TypeName() const {
    switch (m_Type) {
    case Texture::EType::Diffuse:
        return "diffuse";

    case Texture::EType::Specular:
        return "specular";

    case Texture::EType::Ambient:
        return "ambient";

    case Texture::EType::Emissive:
        return "emissive";

    case Texture::EType::Height:
        return "height";

    case Texture::EType::Normals:
        return "normals";

    case Texture::EType::Shininess:
        return "shininess";

    case Texture::EType::Opacity:
        return "opacity";

    case Texture::EType::Displacement:
        return "displacement";

    case Texture::EType::Lightmap:
        return "lightmap";

    case Texture::EType::Reflection:
        return "reflection";

    default: // Texture::EType::Unknown
        return "unknown";
    }
}
