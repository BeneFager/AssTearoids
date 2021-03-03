#include "AssetManager.h"
#include "ECS/Components.h"


AssetManager::AssetManager(Manager *man) : manager(man)
{

}

AssetManager::~AssetManager()
{

}
//Createplay() CreateAss tear oid
void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
	auto &projectile(manager->addentity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("Projectile");
	projectile.addGroup(Game::groupProjectiles);
}


void AssetManager::AddTexture(std::string id, const char *path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture *AssetManager::GetTexture(std::string id)
{
	return textures[id];
}