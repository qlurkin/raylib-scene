#include "raylib.h"
#include "rlgl.h"
#include "Cube.h"
#include "ModelObject.h"
#include "raymath.h"
#include "ParticleSystem.h"
#include "Gravity.h"

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

    Object scene = Object();

    ParticleSystem ps = ParticleSystem(10);
    Gravity g({0.0, -9.81, 0.0});

    ps.addEffect(&g);

    scene.add(&ps);

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
