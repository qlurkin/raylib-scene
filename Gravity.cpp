#include "Gravity.h"
#include <iostream>

Gravity::Gravity(Vector3 g, size_t count) {
    this->g = g;
    this->count = count;
    gpu = new GPU();
    gpu->init();
    vBuff = new Buffer(*gpu, count*sizeof(Vector3));
    gBuff = new Buffer(*gpu, sizeof(Vector3));
    program = new Program(*gpu, "gravity.cl");
    kernel = new Kernel(*gpu, *program, "gravity");
    kernel->setArg(0, *gBuff);
    kernel->setArg(1, *vBuff);
}

Gravity::~Gravity() {
    vBuff->destroy();
    gBuff->destroy();
    kernel->destroy();
    program->destroy();
    gpu->destroy();

    delete vBuff;
    delete gBuff;
    delete kernel;
    delete program;
    delete gpu;
}

void Gravity::apply(Vector3 *positions, Vector3 *velocities, size_t count, float dt) {
    // for(int i=0; i < count; i++) {
    //     velocities[i] = Vector3Add(velocities[i], Vector3Scale(g, dt));
    // }
    Vector3 scaledG = Vector3Scale(g, dt);
    gBuff->upload(&scaledG);
    vBuff->upload(velocities);
    kernel->execute(this->count, 100);
    vBuff->download(velocities);
}

