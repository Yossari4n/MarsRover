#include "Line.h"

Line::Line(glm::vec3 start, glm::vec3 end, glm::vec3 color)
    : m_Color(color) {
    GLfloat vertices[] = { start.x, start.y, start.z, end.x, end.y, end.z };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Line::~Line() {
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void Line::Draw(const ShaderProgram &shader) const {
    shader.Uniform("model", glm::mat4(1.0f));
    shader.Uniform("color", m_Color);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);
}
