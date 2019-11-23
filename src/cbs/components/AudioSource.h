#ifndef AudioSource_h
#define AudioSource_h

#include "Component.h"
#include "../connections/PropertyIn.h"

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

class Transform;
class AudioSource : public Component {
public:
    AudioSource();

    void Initialize() override;
    void Destroy() override;

    PropertyIn<Transform*> TransformIn{ this };

private:
    ALuint m_ID;
};

#endif
