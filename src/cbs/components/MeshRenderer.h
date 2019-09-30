#ifndef MeshRenderer_h
#define MeshRenderer_h

#pragma warning(disable: 26495)

#include "Component.h"
#include "../Object.h"
#include "../message_system/PropertyIn.h"
#include "../../scenes/Scene.h"
#include "../../rendering/Drawable.h"
#include "../../resources/Model3D/Model3D.h"

class MeshRenderer : public Component, public Drawable {
public:
    MeshRenderer(Model3D& model, ShaderProgram::EType type);

    void MakeConnectors(MessageManager& message_manager) override;
    void Initialize() override;
    void Destroy() override;

    void Draw(const ShaderProgram& shader) const override;

    PropertyIn<glm::mat4> ModelIn;

private:
    void DrawMesh(const ShaderProgram& shader, const Mesh& mesh) const;

    Model3D& m_Model3D;
};

#pragma warning(default: 26495)
#endif
