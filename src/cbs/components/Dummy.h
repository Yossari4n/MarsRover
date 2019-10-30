#ifndef Dummy_h
#define Dummy_h

#include "Component.h"

class Dummy : public Component {
public:
    Dummy() = default;

    void Update() override;
};

#endif
