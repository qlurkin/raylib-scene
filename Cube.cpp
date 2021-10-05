#include "Cube.h"
#include <raylib.h>

void Cube::draw() {
    DrawCube({0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, RED);
    DrawCubeWires({0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, BLACK);
}