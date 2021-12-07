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
    std::uniform_real_distribution<> dis(-2.0, 2.0);

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
    for(Force *force : forces) {
        force->apply(positions, velocities, count, dt);
    }

    for(int i=0; i<count; i++) {
        positions[i] = Vector3Add(positions[i], Vector3Scale(velocities[i], dt));
    }

    for(Collider *collider : colliders) {
        collider->collide(positions, velocities, count);
    }
}

void ParticleSystem::addForce(Force *force) {
    forces.push_back(force);
}

void ParticleSystem::addCollider(Collider *collider) {
    colliders.push_back(collider);
}