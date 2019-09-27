#ifndef Texture_h
#define Texture_h

#pragma warning(push, 0)
#include <glad/glad.h>

#include <string>
#pragma warning(pop)

class Texture {
public:
    enum class EType {
        Diffuse,
        Specular,
        Ambient,
        Emissive,
        Height,
        Normals,
        Shininess,
        Opacity,
        Displacement,
        Lightmap,
        Reflection,
        Unknown
    };

    Texture(const unsigned char* data, int widht, int height, int components);

    Texture() = delete;
    Texture(const Texture& other) = default;
    Texture& operator=(const Texture& other) = default;
    Texture(Texture&&) = default;
    Texture& operator=(Texture&&) = default;
    ~Texture() = default;

    GLuint ID() const { return m_ID; }
    void Type(EType type) { m_Type = type; }
    EType Type() const { return m_Type; }
    std::string TypeName() const;

private:
    GLuint m_ID;
    int m_Width;
    int m_Height;
    int m_Components;
    EType m_Type;
};

#endif