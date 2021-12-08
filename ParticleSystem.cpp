#include "ParticleSystem.h"
#include "raymath.h"

#include <random>

void ParticleSystem::allocate(size_t count) {
    mesh = GenMeshSphere(0.1f, 8, 8);
    material = LoadMaterialDefault();
    material.maps[MATERIAL_MAP_DIFFUSE].color = RED;
    this->count = count;
    positions = new Vector3[count];
    velocities = new Vector3[count];
}

ParticleSystem::ParticleSystem(Vector3* positions, Vector3* velocities, size_t count) {
    allocate(count);

    for(int i=0; i<count; i++) {
        this->positions[i] = positions[i];
        this->velocities[i] = velocities[i];
    }
}

ParticleSystem::ParticleSystem(size_t count, Vector3 position, float deviation, Vector3 velocity, float velocityDeviation) {
    allocate(count);
    
    std::random_device r;
    std::mt19937 gen(r());
    std::normal_distribution<> xPosDis(position.x, deviation);
    std::normal_distribution<> yPosDis(position.y, deviation);
    std::normal_distribution<> zPosDis(position.z, deviation);
    std::normal_distribution<> xVelDis(velocity.x, velocityDeviation);
    std::normal_distribution<> yVelDis(velocity.y, velocityDeviation);
    std::normal_distribution<> zVelDis(velocity.z, velocityDeviation);


    for(int i=0; i<count; i++) {
        positions[i] = {(float) xPosDis(gen), (float) yPosDis(gen), (float) zPosDis(gen)};
        velocities[i] = {(float) xVelDis(gen), (float) yVelDis(gen), (float) zVelDis(gen)};
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