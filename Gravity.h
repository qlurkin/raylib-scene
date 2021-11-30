#pragma once

#include "Effect.h"

class Gravity : public Effect {
    private:
        Vector3 g;

    public:
        Gravity(Vector3 g);
        void apply(Vector3 *positions, Vector3 *velocities, size_t count, float dt);
};