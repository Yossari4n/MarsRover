#ifndef Line_h
#define Line_h

#include "../../rendering/IDrawable.h"

class Line : public IDrawable {
public:
    Line(glm::vec3 start, glm::vec3 end, glm::vec3 color);

    Line() = delete;
    Line(const Line&) = delete;
    Line& operator=(const Line&) = delete;
    Line(Line&&) = delete;
    Line& operator=(Line&&) = delete;
    ~Line();

    void Draw(const ShaderProgram& shader) const override;

private:
    GLuint m_VAO;
    GLuint m_VBO;
    glm::vec3 m_Color;
};

#endif
