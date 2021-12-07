#include "raylib.h"
#include "rlgl.h"
#include "Cube.h"
#include "ModelObject.h"
#include "raymath.h"
#include "ParticleSystem.h"
#include "Gravity.h"
#include "Plan.h"
#include <iostream>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "LUR - Scene Example");

    Camera camera = { 0 };
    camera.position = { 5.0f, 5.0f, 5.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FREE); 
    SetCameraPanControl(3);
    SetTargetFPS(60);

    Object scene;

    ParticleSystem ps(10);
    Cube cube;
    cube.scale(4.0);
    cube.translate({0.0f, 2.0f, 0.0f});
    Gravity g({0.0, -9.81, 0.0});
    Plan ground(0, 1, 0, 0);
    Plan wall1(0, 0, 1, 2);
    Plan wall2(1, 0, 0, 2);
    Plan wall3(-1, 0, 0, 2);
    Plan wall4(0, 0, -1, 2);
    Plan ceil(0, -1, 0, 4);

    Vector3 ref = Vector3Reflect({1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    std::cout << ref.x << " " << ref.y << " " << ref.z << std::endl;

    
    ps.addForce(&g);
    ps.addCollider(&wall1);
    ps.addCollider(&wall2);
    ps.addCollider(&wall3);
    ps.addCollider(&wall4);
    ps.addCollider(&ground);
    ps.addCollider(&ceil);

    scene.add(&ps);
    scene.add(&cube);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                DrawGrid(10, 1.0f);

                scene.render();
                ps.update(GetFrameTime());
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
