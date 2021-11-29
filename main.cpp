#include "raylib.h"
#include "rlgl.h"
#include "Cube.h"
#include "ModelObject.h"
#include "raymath.h"

#include "compute.h"
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
	someCompute();

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

    Model model = LoadModel("assets/models/bunny.obj");

    MeshTangents(model.meshes);

    Texture texture = LoadTexture("assets/textures/stone_wall/cgaxis_pbr_17_stone_wall_5_diffuse.png");
    Shader shader = LoadShader("assets/shaders/base.vs", "assets/shaders/base.fs");

    model.materials[0].shader = shader;
    model.materials[0].shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(model.materials[0].shader, "matModel");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    int lightPosLoc = GetShaderLocation(shader, "lightPos");
    float lightPos[] = { 0.0f, 5.0f, 5.0f };
    SetShaderValue(shader, lightPosLoc, lightPos, SHADER_UNIFORM_VEC3);

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
                bunny.rotateY(0.01);
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
