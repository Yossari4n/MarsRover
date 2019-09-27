#ifndef Model_h
#define Model_h

#pragma warning(disable: 26495)

#include "../Component.h"
#include "../../Object.h"
#include "../../message_system/PropertyIn.h"
#include "../../../scenes/Scene.h"
#include "../../../rendering/Drawable.h"
#include "../../../resources/ResourcesManager.h"


class MeshRenderer : public Component, public Drawable {
public:
    MeshRenderer(ShaderProgram::EType type);

    void MakeConnectors(MessageManager& message_manager) override;
    void Initialize() override;
    void Destroy() override;

    void Draw(const ShaderProgram& shader) const override;

    PropertyIn<glm::mat4> ModelIn;

private:

};

#pragma warning(default: 26495)
#endif
