#include "Engine.h"

// Assets
#include "cubeMesh.h"
#include "cubeMeshColored.h"
#include "texture_bin.h"

void onTimerTimeout() {
}

void ProcessCameraTurnInputs();
void MoveForward();
void MoveBackward();
void MoveRight();
void MoveLeft();
void DrawDebugPlaneFloor();

int main() {
    // INITIALIZE ENGINE ===========================================
    Engine engine = Engine();


    // CREATE TEXTURE DATA =========================================
    TextureData textureData = TextureData(GL_RGB, TEXTURE_SIZE_128, TEXTURE_SIZE_128, TEXGEN_TEXCOORD, (u8*)texture_bin);


    // CREATE MESH DATA ============================================

    MeshData cubeData;
    cubeData.vertices = cubeVertices;
    cubeData.faces = cubeFaces;

    MeshData colorCubeData;
    colorCubeData.vertices = cubeColorVertices;
    colorCubeData.faces = cubeFaces;

    MeshData textureCubeData;
    textureCubeData.vertices = cubeVertices;
    textureCubeData.faces = cubeFaces;
    textureCubeData.textureID = textureData.GetTextureID();

    MeshData colorTextureCubeData;
    colorTextureCubeData.vertices = cubeColorVertices;
    colorTextureCubeData.faces = cubeFaces;
    colorTextureCubeData.textureID = textureData.GetTextureID();


    // CREATE MESH3D CUBES =====================================

    Mesh3D* movingParent = new Mesh3D();
    movingParent->meshData = &textureCubeData;
    SceneTree::GetInstance().GetRoot()->AddChild(movingParent);

    Mesh3D* staticChild = new Mesh3D();
    staticChild->meshData = &colorTextureCubeData;
    movingParent->AddChild(staticChild);
    staticChild->SetLocalPosition(glm::vec3(-1.5, 0.0, 0.0));

    Mesh3D* defaultCube = new Mesh3D();
    defaultCube->meshData = &cubeData;
    defaultCube->SetLocalPosition(glm::vec3(4.0, 0.0, 0.0));
    SceneTree::GetInstance().GetRoot()->AddChild(defaultCube);

    Mesh3D* defaultColorCube = new Mesh3D();
    defaultColorCube->meshData = &colorCubeData;
    defaultColorCube->SetLocalPosition(glm::vec3(6.0, 0.0, 0.0));
    SceneTree::GetInstance().GetRoot()->AddChild(defaultColorCube);

    Mesh3D* defaultCubeTexture = new Mesh3D();
    defaultCubeTexture->meshData = &textureCubeData;
    defaultCubeTexture->SetLocalPosition(glm::vec3(8.0, 0.0, 0.0));
    defaultCubeTexture->SetLocalRotation(glm::vec3(90.0, 0.0, 0.0));
    SceneTree::GetInstance().GetRoot()->AddChild(defaultCubeTexture);

    Mesh3D* defaultCubeTextureColor = new Mesh3D();
    defaultCubeTextureColor->meshData = &colorTextureCubeData;
    defaultCubeTextureColor->SetLocalPosition(glm::vec3(10.0, 0.0, 0.0));
    defaultCubeTextureColor->SetLocalRotation(glm::vec3(90.0, 0.0, 0.0));
    SceneTree::GetInstance().GetRoot()->AddChild(defaultCubeTextureColor);


    // CREATE CAMERA =======================================

    Camera3D* cam = new Camera3D();
    cam->SetGlobalPosition(glm::vec3(0, 0, 5));
    Renderer::GetInstance().currentCamera = cam;


    // CREATE EXAMPLE ANIMATION =============================

    AnimationData animData;
    Keyframe f2{1.0, glm::vec3(-2, 1, 0), glm::vec3(90), glm::vec3(0.5, 1, 1)};
    animData.AddKeyframe({});
    animData.AddKeyframe(f2);
    animData.AddKeyframe({2.0});

    Animator* animator = new Animator(movingParent, animData);
    SceneTree::GetInstance().GetRoot()->AddChild(animator);
    animator->Start();


    // CREATING INPUTS ======================================

    Input::AddBindingKey("move_forward", KEY_UP);
    Input::AddBindingKey("move_backward", KEY_DOWN);
    Input::AddBindingKey("move_right", KEY_RIGHT);
    Input::AddBindingKey("move_left", KEY_LEFT);
    Input::AddBindingKey("turn_right", KEY_R);
    Input::AddBindingKey("turn_left", KEY_L);

    Input::AddBindingKey("spawn", KEY_A);
    Input::AddBindingKey("spawn", KEY_B);

    engine.onUpdateFunctions.emplace_back(DrawDebugPlaneFloor);
    engine.onUpdateFunctions.emplace_back(ProcessCameraTurnInputs);
    engine.onUpdateFunctions.emplace_back([]() -> void {
        printf("Warning: Spawns Break Console\n");
        printf("Movement: D-Pad\n");
        printf("Turn: Shoulders L / R\n");
        printf("Spawn: A / B\n");
    });

    Input::AddOnHeld("move_forward", MoveForward);
    Input::AddOnHeld("move_backward", MoveBackward);
    Input::AddOnHeld("move_right", MoveRight);
    Input::AddOnHeld("move_left", MoveLeft);

    Input::AddOnDown("spawn", [&cubeData]() -> void {
        Mesh3D* defaultCube = new Mesh3D();
        defaultCube->meshData = &cubeData;
        SceneTree::GetInstance().GetRoot()->AddChild(defaultCube);
        defaultCube->SetGlobalPosition(Renderer::GetInstance().currentCamera->GetGlobalPosition() + (Renderer::GetInstance().currentCamera->GetForward() * 2.0f));
    });


    // ROTATING DISPLAY CUBES ============================================

    engine.onUpdateFunctions.emplace_back([&defaultCube, &defaultColorCube, &defaultCubeTexture, &defaultCubeTextureColor]() -> void {
        defaultCube->SetLocalRotation(defaultCube->GetLocalRotation() + glm::vec3(0.0, 0.5, 0.0));
        defaultColorCube->SetLocalRotation(defaultColorCube->GetLocalRotation() + glm::vec3(0.0, 0.5, 0.0));
        defaultCubeTexture->SetLocalRotation(defaultCubeTexture->GetLocalRotation() + glm::vec3(0.0, 0.0, -0.5));
        defaultCubeTextureColor->SetLocalRotation(defaultCubeTextureColor->GetLocalRotation() + glm::vec3(0.0, 0.0, -0.5));
    });


    // STARTING ENGINE (ENTER MAIN LOOP) ====================================

    engine.Start();

    return 0;
}

void ProcessCameraTurnInputs() {
    Camera3D* cam = Renderer::GetInstance().currentCamera;
    cam->SetLocalRotation(cam->GetLocalRotation() + glm::vec3(0, -5 * Input::GetAxis("turn_left", "turn_right"), 0));
}

void MoveForward() {
    Camera3D* cam = Renderer::GetInstance().currentCamera;
    if (Input::GetKeyHeld("move_forward"))
        cam->SetGlobalPosition(cam->GetGlobalPosition() + cam->GetForward() * 0.1f);
}

void MoveBackward() {
    Camera3D* cam = Renderer::GetInstance().currentCamera;
    if (Input::GetKeyHeld("move_backward"))
        Renderer::GetInstance().currentCamera->SetGlobalPosition(cam->GetGlobalPosition() - cam->GetForward() * 0.1f);
}

void MoveRight() {
    Camera3D* cam = Renderer::GetInstance().currentCamera;
    if (Input::GetKeyHeld("move_right"))
        cam->SetGlobalPosition(cam->GetGlobalPosition() + cam->GetRight() * 0.1f);
}

void MoveLeft() {
    Camera3D* cam = Renderer::GetInstance().currentCamera;
    if (Input::GetKeyHeld("move_left"))
        cam->SetGlobalPosition(cam->GetGlobalPosition() - cam->GetRight() * 0.1f);
}

void DrawDebugPlaneFloor() {
    Debug::DrawQuad(glm::vec3(0, -2, 0), glm::vec3(90, 0, 0), glm::vec3(40), glm::vec3(0.5));
}
