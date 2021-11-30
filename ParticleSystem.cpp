#include "ParticleSystem.h"
#include "raymath.h"

#include <random>

ParticleSystem::ParticleSystem(size_t count) {
    mesh = GenMeshSphere(0.1f, 8, 8);
    material = LoadMaterialDefault();
    material.maps[MATERIAL_MAP_DIFFUSE].color = RED;

    this->count = count;
    positions = new Vector3[count];
    velocities = new Vector3[count];

    std::random_device r;
    std::mt19937 gen(r());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for(int i=0; i<count; i++) {
        positions[i] = {(float) dis(gen), (float) dis(gen), (float) dis(gen)};
        velocities[i] = {(float) dis(gen), (float) dis(gen), (float) dis(gen)};
    }
}

void ParticleSystem::draw(Matrix matModel) {
    for(int i=0; i<count; i++) {
        DrawMesh(mesh, material, MatrixMultiply(matModel, MatrixTranslate(positions[i].x, positions[i].y, positions[i].z)));
    }
}

void ParticleSystem::update(float dt) {
    for(Effect *effect : effects) {
        effect->apply(positions, velocities, count, dt);
    }
    
    for(int i=0; i<count; i++) {
        positions[i] = Vector3Add(positions[i], Vector3Scale(velocities[i], dt));
    }
}

void ParticleSystem::addEffect(Effect *effect) {
    effects.push_back(effect);
}