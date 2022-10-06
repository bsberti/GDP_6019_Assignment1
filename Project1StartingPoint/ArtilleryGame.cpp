#include "ArtilleryGame.h"
#include <iostream>
#include "AssetInfo.h"
#include <random>

#define DEBUG_LOG_ENABLED
#ifdef DEBUG_LOG_ENABLED
#define DEBUG_PRINT(x, ...) printf(x, __VA_ARGS__)
#else
#define DEBUG_PRINT(x)
#endif

// Ids preloaded in the main.cpp to be referenced when
// creating specific game objects for your game.
// - EnemyTank, PlayerTank, and Bullet
unsigned int TankModelId;
unsigned int ProjectileModelId;
unsigned int PlayerMaterialId;
unsigned int EnemyMaterialId;
unsigned int BulletMaterialId;
unsigned int SphereMaterialId;

const float ENEMY_TANK_RADIUS = 1.5f;

bool gameOver = false;
bool playerShooting = false;
bool enemyHit = false;
bool openFire = false;

Vector3 shotDirection;
Vector3 gravity = Vector3(0.0f, -0.0981f, 0.0f);

// TODO:
// #include "YourPhysicsClass.h"

/// <summary>
/// Default constructor
/// Set all class variables to the desired default state
/// </summary>
ArtilleryGame::ArtilleryGame()
	: m_PlayerTank(nullptr)
	, m_EnemyTank(nullptr)
	, m_Bullet()
{
	DEBUG_PRINT("ArtilleryGame::ArtilleryGame\n");
	// DO NOTHING!!!!!!!!
}

float RandFloat(float min, float max) {
	if (max == min)
		return 0.f;

	int diff = (max - min) * 1000;
	return min + (rand() % diff) / 1000.f;
}

/// <summary>
/// Default destructor
/// </summary>
ArtilleryGame::~ArtilleryGame()
{
	DEBUG_PRINT("ArtilleryGame::~ArtilleryGame\n");
	// DO NOTHING!!!!!!!!
}

/// <summary>
/// Create everything needed for your game here
/// such as memory allocation calls
/// </summary>
void ArtilleryGame::Initialize()
{
	DEBUG_PRINT("ArtilleryGame::Initialize\n");
	// TODO:
	// - Create a Player Tank GameObject
	// - Create an Enemy Tank GameObject
	// - Create projectile(s)
	m_PlayerTank = CreateGameObjectByType("Player");
	m_EnemyTank = CreateGameObjectByType("Enemy");
	
	DEBUG_PRINT("Create Bullet!\n");
	m_Bullet.particle = m_particleSystem.CreateParticle(1000.0f);
	m_Bullet.gameObject = GDP_CreateGameObject();
	m_Bullet.gameObject->Renderer.ShaderId = 1;
	m_Bullet.gameObject->Renderer.MeshId = ProjectileModelId;
	m_Bullet.gameObject->Renderer.MaterialId = BulletMaterialId;

	//m_PlayerTank->Position = glm::vec3(RandFloat(-20, 20), 0, RandFloat(-20, 20));
	//m_EnemyTank->Position = glm::vec3(RandFloat(-20, 20), 0, RandFloat(-20, 20));
	//m_Bullet.gameObject->Position = glm::vec3(0, 0, 0);

	CreateExplosion(10);

	StartNewGame();
}

/// <summary>
/// Handle everything that needs to be destroyed
/// such as memory de-allocation.
/// </summary>
void ArtilleryGame::Destroy()
{
	DEBUG_PRINT("ArtilleryGame::Destroy\n");
	// TODO:
}

float DistanceBetween(glm::vec3 enemy, glm::vec3 bullet) {
	float distance = sqrt((enemy.x - bullet.x) * (enemy.x - bullet.x) +
		(enemy.y - bullet.y) * (enemy.y - bullet.y) +
		(enemy.z - bullet.z) * (enemy.z - bullet.z));
	return distance;
}

void ArtilleryGame::ResetBulletPosition() {
	m_Bullet.gameObject->Position = glm::vec3(m_PlayerTank->Position.x, 0.5f, m_PlayerTank->Position.z);
	m_Bullet.particle->position = Vector3(m_PlayerTank->Position.x, 0.5f, m_PlayerTank->Position.z);
}


/// <summary>
/// StartNewGame
/// 1. Randomly place the enemy tank at a random valid location on the map
/// 2. Randomly place the player tank at a random valid location on the map
/// 3. Reset the bullet(s)
/// </summary>
void ArtilleryGame::StartNewGame()
{
	DEBUG_PRINT("ArtilleryGame::StartNewGame\n");

	gameOver = false;
	playerShooting = false;
	enemyHit = false;
	openFire = false;

	printf("New Game Started! ---------------------------------------------\n");

	m_PlayerTank->Position = glm::vec3(RandFloat(-20, 20), 0, RandFloat(-20, 20));
	m_EnemyTank->Position = glm::vec3(RandFloat(-20, 20), 0, RandFloat(-20, 20));

	ResetBulletPosition();

	shotDirection = Vector3(1.0f, 1.0f, 1.0f);
	//shotDirection.Normalize();
}

void changingShotDirection(float x, float y, float z) {
	// Changing Shot Direction
	shotDirection.x += x;
	shotDirection.y += y;
	shotDirection.z += z;
	printf("New Shot Diretion: (%.2f, %.2f, %.2f)\n", shotDirection.x, shotDirection.y, shotDirection.z);
}

/// <summary>
/// Update all bullets here
/// - Call your Physics class to update all projectiles
/// Check for bullet collision (position.y <= 0, hit ground)
/// Check for User input:
/// >>> GDP_IsKeyPressed, GDP_IsKeyHeldDown <-- Case Sensitive
/// >>> example: if (GDP_IsKeyPressed('n') || GDP_IsKeyPressed('N'))
/// - Input for changing the bullet direction	(wasd, etc)
/// - Input to change the projectile type		(1,2,3,4,5)
/// - Input to fire a projectile				(space)
/// - Input to start a new game					(n)
/// </summary>
void ArtilleryGame::GameUpdate()
{
	// DEBUG_PRINT("ArtilleryGame::GameUpdate\n");
	
	if (GDP_IsKeyPressed('A') || GDP_IsKeyPressed('a')) {
		// Change fire direction to the left
		if (!playerShooting && !openFire)
			changingShotDirection(1.f, 0.f, 0.f);
	}
	if (GDP_IsKeyPressed('D') || GDP_IsKeyPressed('d')) {
		// Change fire direction to the right
		if (!playerShooting && !openFire)
			changingShotDirection(-1.f, 0.f, 0.f);
	}
	if (GDP_IsKeyPressed('W') || GDP_IsKeyPressed('w')) {
		// Change fire direction up
		if (!playerShooting && !openFire)
			changingShotDirection(0.f, 0.f, 1.f);
	}
	if (GDP_IsKeyPressed('S') || GDP_IsKeyPressed('s')) {
		// Change fire direction down
		if (!playerShooting && !openFire)
			changingShotDirection(0.f, 0.f, -1.f);
	}
	if (GDP_IsKeyPressed('Q') || GDP_IsKeyPressed('q')) {
		// Change fire direction up
		if (!playerShooting && !openFire)
			changingShotDirection(0.f, 1.f, 0.f);
	}
	if (GDP_IsKeyPressed('E') || GDP_IsKeyPressed('e')) {
		// Change fire direction down
		if (!playerShooting && !openFire)
			changingShotDirection(0.f, -1.f, 0.f);
	}
	if (GDP_IsKeyPressed('1')) {
		// Change bullet type to 1
		printf("Changing particle mass to: 1\n");
		if (!playerShooting)
			m_Bullet.particle->invMass = 1.f;
	}
	if (GDP_IsKeyPressed('2')) {
		// Change bullet type to 2
		printf("Changing particle mass to: 0.8\n");
		if (!playerShooting)
			m_Bullet.particle->invMass = 0.8f;
	}
	if (GDP_IsKeyPressed('3')) {
		// Change bullet type to 3
		printf("Changing particle mass to: 0.4\n");
		if (!playerShooting)
			m_Bullet.particle->invMass = 0.4f;
	}
	if (GDP_IsKeyPressed('4')) {
		// Change bullet type to 4
		printf("Changing particle mass to: 0.2\n");
		if (!playerShooting)
			m_Bullet.particle->invMass = 0.2f;
	}
	if (GDP_IsKeyPressed('5')) {
		// Change bullet type to 5
		printf("Changing particle mass to: 0.1\n");
		if (!playerShooting)
			m_Bullet.particle->invMass = 0.1f;
	}

	if (GDP_IsKeyPressed('N') || GDP_IsKeyPressed('n')) {
		if (!playerShooting)
			StartNewGame();
	}

	if (GDP_IsKeyPressed('M') || GDP_IsKeyPressed('m')) {
		printf("Reseting bullet position, try again!\n");
		if (!playerShooting) {
			ResetBulletPosition();
			CleanExplosion();
			openFire = false;
			shotDirection = Vector3(1.0f, 1.0f, 1.0f);
		}
	}

	if (GDP_IsKeyPressed(' ')) {
		// Change fire direction down
		if (!playerShooting && !openFire) {
			m_Bullet.particle->ApplyForce(shotDirection);
			playerShooting = true;
		}
	}

	if (playerShooting) {
		// Upgrade bullet
		printf("Bullet started position:  (%.2f, %.2f, %.2f)\n", m_Bullet.gameObject->Position.x, m_Bullet.gameObject->Position.y, m_Bullet.gameObject->Position.z);

		//World Forces
		m_Bullet.particle->ApplyForce(gravity);
		m_Bullet.particle->age = 100.f;

		//Update the visual object from the phisics object
		m_Bullet.gameObject->Position = glm::vec3(m_Bullet.particle->position.x, 
												  m_Bullet.particle->position.y, 
												  m_Bullet.particle->position.z);
	}

	if (m_Bullet.gameObject->Position.y <= 0.0f) {
		playerShooting = false;
		openFire = true;

		// If Bullet hit the enemy!
		printf("ABS = %2.f\n", DistanceBetween(m_Bullet.gameObject->Position, m_EnemyTank->Position));
		if (DistanceBetween(m_Bullet.gameObject->Position, m_EnemyTank->Position) <= ENEMY_TANK_RADIUS) {
			// TO-DO enemy position range
			ResetBulletPosition();
			Boom();
			m_EnemyTank->Position = glm::vec3(100.0f, 100.f, 100.f);
			enemyHit = true;
			printf("ENEMY TANK HITTED! Congratulations! Press N to start a new Game\n");
		}
		else {
			printf("Enemy Tank missed! Press M to try again\n");
		}

		m_Bullet.gameObject->Position.y = 0.1f;
	}

	if (enemyHit) {
		for (int i = 0; i < m_explosionParticles.size(); i++) {
			m_explosionParticles[i].particle->ApplyForce(gravity);
			m_explosionParticles[i].gameObject->Position =
				glm::vec3(m_explosionParticles[i].particle->position.x,
					m_explosionParticles[i].particle->position.y,
					m_explosionParticles[i].particle->position.z);

			if (m_explosionParticles[i].particle->age <= 0.f)
				CleanExplosion();
		}
	}
	//Integration
	m_particleSystem.Integrate(0.1f);
}

void ArtilleryGame::Boom() {
	for (int i = 0; i < m_explosionParticles.size(); i++) {
		m_explosionParticles[i].gameObject->Position = glm::vec3(m_EnemyTank->Position.x, 0.5f, m_EnemyTank->Position.z);
		m_explosionParticles[i].particle->position = Vector3(m_EnemyTank->Position.x, 0.5f, m_EnemyTank->Position.z);

		m_explosionParticles[i].particle->ApplyForce(Vector3(RandFloat(-5.0f, 5.0f), 7.0f, RandFloat(-5.0f, 5.0f)));
		m_explosionParticles[i].particle->age = 10.0f;
	}
}

void ArtilleryGame::CreateExplosion(float explosionSize) {
	for (int i = 0; i <= explosionSize; i++) {
		Fire f;
		f.particle = m_particleSystem.CreateParticle(1.0f);
		f.gameObject = GDP_CreateGameObject();
		f.gameObject->Renderer.ShaderId = 1;
		f.gameObject->Renderer.MeshId = SphereMaterialId;
		f.gameObject->Renderer.MaterialId = SphereMaterialId;
		f.gameObject->Scale = glm::vec3(0.5f, 0.5f, 0.5f);

		f.gameObject->Position = glm::vec3(100.f, 100.f, 100.f);

		m_explosionParticles.push_back(f);
	}

	int amazingBreakPoint = 5;
}

void ArtilleryGame::CleanExplosion() {
	for (int i = 0; i < m_explosionParticles.size(); i++) {
		m_explosionParticles[i].gameObject->Position = glm::vec3(100.f, 100.f, 100.f);
	}
}

/// <summary>
/// Print provided text to the console for the user
/// </summary>
/// <param name="text"></param>
void ArtilleryGame::DisplayTextToUser(const std::string& text)
{
	std::cout << text << "\n";
}

GameObject* ArtilleryGame::CreateGameObjectByType(const std::string& type)
{
	DEBUG_PRINT("ArtilleryGame::CreateGameObjectByType(%s)\n", type.c_str());

	if (type.compare("Player") == 0) {
		DEBUG_PRINT("Create player!\n");
		GameObject* go = GDP_CreateGameObject();
		go->Renderer.ShaderId = 1;
		go->Renderer.MeshId = TankModelId;
		go->Renderer.MaterialId = PlayerMaterialId;
		return go;
	}
	if (type.compare("Enemy") == 0) {
		DEBUG_PRINT("Create Enemy!\n");
		GameObject* go = GDP_CreateGameObject();
		go->Renderer.ShaderId = 1;
		go->Renderer.MeshId = TankModelId;
		go->Renderer.MaterialId = EnemyMaterialId;
		return go;
	}

	// Invalid game object type, return nullptr
	return nullptr;
}