#pragma once

#include <gdp/Engine.h>
#include <string>
#include "Bullet.h"
#include "Particle.h"
#include "ParticleSystem.h"

using namespace gdp; 

class ArtilleryGame {
public:
	ArtilleryGame();
	~ArtilleryGame();

	void Initialize();
	void Destroy();

	void StartNewGame();
	void GameUpdate();
	void DisplayTextToUser(const std::string& text);
	
private:
	GameObject* CreateGameObjectByType(const std::string& type);

	GameObject* m_PlayerTank;
	GameObject* m_EnemyTank;
	Bullet m_Bullet;

	ParticleSystem m_particleSystem;
};