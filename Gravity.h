#pragma once

#include "Force.h"
#include "GPU.h"

class Gravity : public Force {
    private:
        Vector3 g;
        GPU* gpu;
        Program* program;
        Kernel* kernel;
        size_t count;
        Buffer* vBuff;
        Buffer* gBuff;

    public:
        Gravity(Vector3 g, size_t count);
        ~Gravity();
        void apply(Vector3 *positions, Vector3 *velocities, size_t count, float dt);
};