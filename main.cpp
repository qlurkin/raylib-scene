#include <raylib.h>
#include "rlgl.h"
#include "Cube.h"
#include "ModelObject.h"
#include <raymath.h>

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
    SetTargetFPS(60);

    Object scene = Object();

    Model model = LoadModel("assets/models/bunny.obj");

    for(int i = 0; i<model.meshes[0].vertexCount; i++) {
        model.meshes[0].texcoords[2*i]   = model.meshes[0].vertices[3*i]*10.0f;
        model.meshes[0].texcoords[2*i+1] = model.meshes[0].vertices[3*i+1]*10.0f;
    }
    UpdateMeshBuffer(model.meshes[0], SHADER_LOC_VERTEX_TEXCOORD01, model.meshes[0].texcoords, model.meshes[0].vertexCount*2*sizeof(float), 0);
    GenMeshTangents(model.meshes);
    Texture texture = LoadTexture("assets/textures/texel_checker.png");
    Shader shader = LoadShader("assets/shaders/base.vs", "assets/shaders/base.fs");

    model.materials[0].shader = shader;
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    int lightPosLoc = GetShaderLocation(shader, "lightPos");
    SetShaderValue(shader, lightPosLoc, (float[]){ 0.0f, 5.0f, 5.0f }, SHADER_UNIFORM_VEC3);

    ModelObject bunny = ModelObject(model);
    bunny.scale(10.0f);

    scene.add(&bunny);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                DrawGrid(10, 1.0f);

                scene.render();
                bunny.rotateY(0.05);
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}