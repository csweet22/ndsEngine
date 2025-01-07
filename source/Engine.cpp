#include "Engine.h"

Engine::Engine() {
    Init();
}

Engine::~Engine() {
    if (SceneTree::GetInstance().GetRoot())
        delete SceneTree::GetInstance().GetRoot();
}

void Engine::Init() {
    videoSetMode(MODE_0_3D);
    glInit();
    glEnable(GL_TEXTURE_2D);
    glViewport(0, 0, 255, 191);
    glEnable(GL_ANTIALIAS);

    // setup the rear plane
    glClearColor(5, 5, 5, 31);  // BG must be opaque for AA to work
    glClearPolyID(63);          // BG must have a unique polygon ID for AA to work
    glClearDepth(0x7FFF);

    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK);

    vramSetBankA(VRAM_A_TEXTURE);

    consoleDemoInit();
}

void Engine::Start() {
    while (pmMainLoop()) {
        consoleClear();
        scanKeys();

        Time::GetInstance().UpdateDeltaTime();

        for (auto& pair : Input::onHeldFunctions) {
            for (auto& func : pair.second) {
                if (Input::GetKeyHeld(pair.first))
                    func();
            }
        }

        for (auto& pair : Input::onDownFunctions) {
            for (auto& func : pair.second) {
                if (Input::GetKeyDown(pair.first))
                    func();
            }
        }

        for (auto& pair : Input::onUpFunctions) {
            for (auto& func : pair.second) {
                if (Input::GetKeyUp(pair.first))
                    func();
            }
        }

        Renderer::GetInstance().ResetPolyCount();
        Renderer::GetInstance().UpdateMVP();

        SceneTree::GetInstance().GetRoot()->Update();
        for (auto& onUpdate : onUpdateFunctions) {
            onUpdate();
        }

        Renderer::GetInstance().EndRender();

        glFlush(0);
        swiWaitForVBlank();
    }
}
