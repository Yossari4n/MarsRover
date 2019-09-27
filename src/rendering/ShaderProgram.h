#ifndef ShaderProgram_h
#define ShaderProgram_h

#pragma warning(push, 0)
#include <glad/glad.h>
#include <glm/glm.hpp>
#pragma warning(pop)

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class ShaderProgram {
public:
    enum EType {
        PureColor = 0,
        PureTexture,
        Phong,
        Skybox,
        
        Count
    };

    enum ETrait : unsigned char {
        NONE = 0,
        LIGHT_RECEIVER = 1 << 0
    };

    ShaderProgram();
    // Delete copy semanatics to prevent silent deletion of shader program
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&&) = default;
    ShaderProgram& operator=(ShaderProgram&&) = default;
    ~ShaderProgram();
    
    void AttachShaders(const char *vertex_path, const char *fragment_path, const char *geometry_path = nullptr);
    void Use() const;
    int ID() const;
    
    ETrait Traits() const { return m_Traits; }
    void Traits(ETrait traits) { m_Traits = traits; }
    
    // Setters for OpenGL shaders
    void Uniform(const std::string &name, bool value) const;
    void Uniform(const std::string &name, int value) const;
    void Uniform(const std::string &name, float value) const;
    void Uniform(const std::string &name, const glm::vec2 &vec) const;
    void Uniform(const std::string &name, float x, float y) const;
    void Uniform(const std::string &name, const glm::vec3 &vec) const;
    void Uniform(const std::string &name, float x, float y, float z) const;
    void Uniform(const std::string &name, const glm::vec4 &vec) const;
    void Uniform(const std::string &name, float x, float y, float z, float w) const;
    void Uniform(const std::string &name, const glm::mat2 &mat) const;
    void Uniform(const std::string &name, const glm::mat3 &mat) const;
    void Uniform(const std::string &name, const glm::mat4 &mat) const;
    
private:
    void LinkProgram();
    unsigned int AttachShader(const char *path, GLenum shader);
    
    unsigned int m_ID;
    ETrait m_Traits;
};

ShaderProgram::ETrait operator| (ShaderProgram::ETrait lhs, ShaderProgram::ETrait rhs);

#endif
