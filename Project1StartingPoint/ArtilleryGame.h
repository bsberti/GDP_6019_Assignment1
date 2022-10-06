#pragma once

#include <gdp/Engine.h>
#include <string>
#include "Bullet.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Fire.h"

using namespace gdp; 

class ArtilleryGame {
public:
	ArtilleryGame();
	~ArtilleryGame();

	void Initialize();
	void Destroy();

	ParticleSystem m_particleSystem;

	std::vector<Fire> m_explosionParticles;

	void StartNewGame();
	void GameUpdate();
	void DisplayTextToUser(const std::string& text);
	void CreateExplosion(float explosionSize);
	void ResetBulletPosition();
	void CleanExplosion();
	void Boom();
	
private:
	GameObject* CreateGameObjectByType(const std::string& type);

	GameObject* m_PlayerTank;
	GameObject* m_EnemyTank;
	Bullet m_Bullet;

};