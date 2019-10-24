#ifndef MeshRenderer_h
#define MeshRenderer_h

#pragma warning(disable: 26495)

#include "Component.h"
#include "../Object.h"
#include "../connections/PropertyIn.h"
#include "../../scenes/Scene.h"
#include "../../rendering/Drawable.h"
#include "../../rendering/Model/Model.h"

class MeshRenderer : public Component, public Drawable {
public:
    MeshRenderer(RawModel& model, ShaderProgram::EType type);

    void MakeConnectors(MessageManager& message_manager) override;
    void Initialize() override;
    void Destroy() override;

    void Draw(const ShaderProgram& shader) const override;

    PropertyIn<glm::mat4> ModelIn;

private:
    void DrawMesh(const ShaderProgram& shader, const Mesh& mesh) const;

    Model m_Model;
};

#pragma warning(default: 26495)
#endif
