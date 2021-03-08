#include "AssetManager.h"
#include "ECS/Components.h"


AssetManager::AssetManager(Manager* man) : manager(man)
{

}

AssetManager::~AssetManager()
{

}
//Createplay() CreateAss tear oid
void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
	auto& projectile(manager->addentity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 5, 5, 1);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("Projectile");
	projectile.addGroup(Game::groupProjectiles);
}


void AssetManager::CreateAsstearoid(Vector2D pos, Vector2D vel, int speed, float rot, int sc, std::string id)
{
	auto& asstearoid(manager->addentity());
	asstearoid.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, sc);
	asstearoid.addComponent<SpriteComponent>(id, false);
	asstearoid.addComponent<AsstearoidComponent>(vel);
	asstearoid.addComponent<ColliderComponent>("Asstearoid");
	asstearoid.addGroup(Game::groupAsstearoids);
	std::cout << " assteriod created at " << asstearoid.addComponent<TransformComponent>().position  << std::endl;
}


void AssetManager::SpawnAss()
{
	Vector2D spawn = GetSpawnPoint();
	CreateAsstearoid(spawn, NormalizeVector2D(Vector2D(windowWidth / 2, windowHeight / 2) - spawn) *2 , 1, 36, 1, "Ass");
	std::cout << "i am dead ass" << std::endl;


}
void AssetManager::SetWindowSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}
Vector2D AssetManager::GetSpawnPoint()
{

	int randWidth = rand() % windowWidth;

	int randHeight = rand() % windowHeight;

	return Vector2D(randWidth, randHeight);

}
Vector2D AssetManager::NormalizeVector2D(Vector2D vector)
{
	float magnitude = sqrtf(vector.x * vector.x + vector.y * vector.y);
	return Vector2D(vector.x / magnitude, vector.y / magnitude);
}
void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}