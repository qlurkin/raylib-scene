#pragma once

#include "Object.h"

class ParticleSystem : public Object {
    private:
        Mesh mesh;
        Material material;
        Vector3* velocities;
        Vector3* positions;
        size_t count;

    public:
        ParticleSystem(size_t count);
        virtual void draw(Matrix matModel);
        void update(float dt);
};