#include <raylib.h>
#include "rlgl.h"
#include "Cube.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "LUR - Scene Example");

    Camera camera = { 0 };
    camera.position = { 16.0f, 16.0f, 16.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FREE); 
    SetTargetFPS(60);

    Object scene = Object();

    Cube central = Cube();
    scene.add(&central);
    
    Object turn120 = Object();
    turn120.rotation.y = 2*PI/3;
    central.add(&turn120);
    
    Object turn240 = Object();
    turn240.rotation.y = 4*PI/3;
    central.add(&turn240);

    Cube orbit = Cube();
    orbit.position.x = 2.0f;
    orbit.scale = {0.5, 0.5, 0.5};
    central.add(&orbit);
    turn240.add(&orbit);
    turn120.add(&orbit);

    Object orbitTurn120 = Object();
    orbitTurn120.rotation.y = 2*PI/3;
    orbit.add(&orbitTurn120);
    
    Object orbitTurn240 = Object();
    orbitTurn240.rotation.y = 4*PI/3;
    orbit.add(&orbitTurn240);

    Cube satelit = Cube();
    satelit.position.x = 2.0f;
    satelit.scale = {0.5, 0.5, 0.5};
    orbit.add(&satelit);
    orbitTurn240.add(&satelit);
    orbitTurn120.add(&satelit);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);

                scene.render();
                central.rotation.y += 0.05;
                orbit.rotation.y -= 0.1;
                satelit.rotation.y += 0.1;

            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}