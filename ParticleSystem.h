#pragma once

#include "Object.h"
#include "Force.h"
#include "Collider.h"
#include <vector>

class ParticleSystem : public Object {
    private:
        Mesh mesh;
        Material material;
        Vector3* velocities;
        Vector3* positions;
        size_t count;
        std::vector<Force*> forces;
        std::vector<Collider*> colliders;

    public:
        ParticleSystem(size_t count);
        virtual void draw(Matrix matModel);
        void update(float dt);
        void addForce(Force *force);
        void addCollider(Collider *collider);
};