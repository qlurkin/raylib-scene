#include "Gravity.h"

Gravity::Gravity(Vector3 g, size_t count) : vBuff(this->gpu, count*sizeof(Vector3)), gBuff(this->gpu, sizeof(Vector3)), program(this->gpu, "kernel.cl"), kernel(this->gpu, this->program, "vector_add") {
    this->g = g;
    this->count = count;
    gBuff.upload(&(this->g));
    kernel.setArg(0, vBuff);
    kernel.setArg(1, gBuff);
}

Gravity::~Gravity() {
    vBuff.destroy();
    gBuff.destroy();
    kernel.destroy();
    program.destroy();
    gpu.destroy();
}

void Gravity::apply(Vector3 *positions, Vector3 *velocities, size_t count, float dt) {
    // for(int i=0; i < count; i++) {
    //     velocities[i] = Vector3Add(velocities[i], Vector3Scale(g, dt));
    // }

}

