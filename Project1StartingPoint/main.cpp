#include <gdp/engine.h>
#include <vector>
using namespace gdp;

#define SUCCESS 0

const char* WINDOW_TITLE = "Artillery (Clone)";
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

const int GROUND_WIDTH = 20;
const int GROUND_HEIGHT = 20;

#include "AssetInfo.h"
#include "ArtilleryGame.h"
ArtilleryGame g_ArtilleryGame;

#define RED glm::vec3(1, 0, 0)
#define BLUE glm::vec3(0, 0, 1)
#define GREEN glm::vec3(0, 1, 0)
#define WHITE glm::vec3(1, 1, 1)
#define ORIGIN glm::vec3(0, 0, 0)

/// <summary>
/// Loads all requried assets for the game
/// </summary>
void LoadAllGameAssets() {
	unsigned int enemyTankTextureId;
	unsigned int playerTankTextureId;
	unsigned int bulletTextureId;
	unsigned int groundTextureId;
	GDP_LoadTexture(enemyTankTextureId, "assets/textures/tanktexture.png");
	GDP_LoadTexture(playerTankTextureId, "assets/textures/tanktexture.png");
	GDP_LoadTexture(bulletTextureId, "assets/textures/tanktexture.png");
	GDP_LoadTexture(groundTextureId, "assets/textures/grid.png");

	unsigned int groundMaterialId;
	GDP_CreateMaterial(EnemyMaterialId, enemyTankTextureId, RED);
	GDP_CreateMaterial(PlayerMaterialId, playerTankTextureId, GREEN);
	GDP_CreateMaterial(BulletMaterialId, bulletTextureId, BLUE);
	GDP_CreateMaterial(groundMaterialId, groundTextureId, WHITE);

	unsigned int groundModelId;
	GDP_LoadModel(TankModelId, "assets/models/tank.obj");
	GDP_LoadModel(ProjectileModelId, "assets/models/tankbullet.obj");
	GDP_LoadModel(groundModelId, "assets/models/plane.obj");

	GameObject* ground = GDP_CreateGameObject();
	ground->Renderer.ShaderId = 1;
	ground->Renderer.MeshId = groundModelId;
	ground->Renderer.MaterialId = groundMaterialId;
	ground->Position = ORIGIN;
	ground->Scale = glm::vec3(GROUND_WIDTH, 1, GROUND_HEIGHT);
}


void Update() {
	g_ArtilleryGame.GameUpdate();
}

int main(int argc, char** argv) {
	// Initializes behind the scenes freeglut, and glew
	GDP_Initialize();
	GDP_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

	// This function will be called during the update step 
	GDP_UpdateCallback(&Update);
	LoadAllGameAssets();

	// Must have all assets loaded before initializing the game world!
	g_ArtilleryGame.Initialize();

	// Start the main loop for FreeGlut
	GDP_Run();

	// Destroys all engine related data, and FreeGlut stuff.
	g_ArtilleryGame.Destroy();
	GDP_Destroy();

	return SUCCESS;
}