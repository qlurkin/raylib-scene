#include "raylib.h"
#include "rlgl.h"
#include "Cube.h"
#include "ModelObject.h"
#include "raymath.h"
#include "ParticleSystem.h"
#include "Gravity.h"
#include "Plan.h"
#include <iostream>

#include "GPU.h"

void someCompute() {
    // Create the two input vectors
    int i;
    const int LIST_SIZE = 1024;
    int *A = new int[LIST_SIZE];
    int *B = new int[LIST_SIZE];
    int *C = new int[LIST_SIZE];
    for(i = 0; i < LIST_SIZE; i++) {
        A[i] = i;
        B[i] = LIST_SIZE - i;
    }


    GPU gpu;
    gpu.init();

    Buffer Abuff = gpu.createBuffer(sizeof(int) * LIST_SIZE);
    Buffer Bbuff = gpu.createBuffer(sizeof(int) * LIST_SIZE);
    Buffer Cbuff = gpu.createBuffer(sizeof(int) * LIST_SIZE);

    Abuff.upload(A);
    Bbuff.upload(B);

    Program program = gpu.createProgram("./kernel.cl");

    Kernel kernel = program.getKernel("vector_add");

    kernel.setArg(0, Abuff);
    kernel.setArg(1, Bbuff);
    kernel.setArg(2, Cbuff);

    kernel.execute(LIST_SIZE, 64);

    Cbuff.download(C);

    for(i = 0; i < LIST_SIZE; i++)
        printf("%d + %d = %d\n", A[i], B[i], C[i]);

    Abuff.destroy();
    Bbuff.destroy();
    Cbuff.destroy();

    kernel.destroy();
    program.destroy();
    gpu.destroy();
    
    delete[] A;
    delete[] B;
    delete[] C;
}

int main(void)
{
    //someCompute();

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "LUR - Scene Example");

    Camera camera = { 0 };
    camera.position = { 10.0f, 2.0f, 0.0f };
    camera.target = { 0.0f, 2.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FREE); 
    SetCameraPanControl(3);
    SetTargetFPS(60);

    Object scene;

    ParticleSystem ps(1000, {0.0f, 2.0f, 0.0f}, 0.4f, {0.0f, 0.0f, 0.0f}, 1.0f);
    Cube cube;
    cube.scale(4.0);
    cube.translate({0.0f, 2.0f, 0.0f});
    Gravity g({0.0, -9.81, 0.0}, ps.getCount());
    Plan ground(0, 1, 0, 0);
    Plan wall1(0, 0, 1, 2);
    Plan wall2(1, 0, 0, 2);
    Plan wall3(-1, 0, 0, 2);
    Plan wall4(0, 0, -1, 2);
    Plan ceil(0, -1, 0, 4);
    
    ps.addForce(&g);
    ps.addCollider(&wall1);
    ps.addCollider(&wall2);
    ps.addCollider(&wall3);
    ps.addCollider(&wall4);
    ps.addCollider(&ground);
    //ps.addCollider(&ceil);

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
