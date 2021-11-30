#pragma once

#include "Object.h"
#include "Effect.h"
#include <vector>

class ParticleSystem : public Object {
    private:
        Mesh mesh;
        Material material;
        Vector3* velocities;
        Vector3* positions;
        size_t count;
        std::vector<Effect*> effects;

    public:
        ParticleSystem(size_t count);
        virtual void draw(Matrix matModel);
        void update(float dt);
        void addEffect(Effect *effect);
};