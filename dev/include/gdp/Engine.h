#pragma once

#ifdef GDP_EXPORTS
#define GDPENGINE_API __declspec(dllexport)
#else
#define GDPENGINE_API __declspec(dllimport)
#endif

#include "GameObject.h"


namespace gdp
{
    // Engine
    extern "C" GDPENGINE_API void GDP_Initialize();
    extern "C"  GDPENGINE_API void GDP_Destroy();
    extern "C"  GDPENGINE_API void GDP_UpdateCallback(void (*Callback)(void));
    extern "C" GDPENGINE_API void GDP_Run();
    extern "C" GDPENGINE_API void GDP_CreateWindow(
        const char* title, const int width, const int height);

    // Assets
    extern "C"  GDPENGINE_API void GDP_LoadTexture(
        unsigned int& id, const char* filepath);
    extern "C" GDPENGINE_API void GDP_LoadModel(
        unsigned int& id, const char* filepath);
    extern "C"  GDPENGINE_API void GDP_CreateMaterial(
        unsigned int& id, unsigned int textureId, const glm::vec3& color);
    extern "C" GDPENGINE_API void GDP_CreateShaderProgramFromFiles(
        unsigned int& id, const char* vertexShader, const char* fragmentShader);

    // Game World
    extern "C" GDPENGINE_API GameObject* GDP_CreateGameObject();

    // User Input
    extern "C" GDPENGINE_API bool GDP_IsKeyHeldDown(unsigned char key);
    extern "C" GDPENGINE_API bool GDP_IsKeyPressed(unsigned char key);
    extern "C" GDPENGINE_API bool GDP_IsKeyReleased(unsigned char key);
    extern "C" GDPENGINE_API void GDP_GetMousePosition(int& x, int& y);
    extern "C" GDPENGINE_API bool GDP_GetMouseButtonState(int button, int& state);
}