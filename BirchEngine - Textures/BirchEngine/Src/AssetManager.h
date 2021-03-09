#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
#include "SDL_ttf.h"

class AssetManager
{
public:
	AssetManager(Manager *man);
	~AssetManager();

	//gameobjects
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);
	void CreateAsstearoid(Vector2D pos, Vector2D vel, int speed, float rot, int sc, std::string id);
	
	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font *GetFont(std::string id);
	//textures
	void AddTexture(std::string id, const char *path);
	SDL_Texture *GetTexture(std::string id);
	void SpawnAss();
	void SetWindowSize(int width, int height);
	Vector2D GetSpawnPoint();
	Vector2D GetVel();
	Vector2D NormalizeVector2D(Vector2D vector);



private:

	Manager *manager;
	std::map<std::string, SDL_Texture *> textures;
	std::map<std::string, TTF_Font *> fonts;
	int activeAss = 1;
	int windowWidth;
	int windowHeight;
};
