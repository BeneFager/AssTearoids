#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"


Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

//SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addentity());

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	assets->AddTexture("terrain", "Assets/terrain_ss.png");
	assets->AddTexture("ship", "Assets/Ship.png");
	assets->AddTexture("point", "Assets/Point.png");
	assets->AddTexture("Ass", "Assets/Asstearoid.png");

	map = new Map("terrain", 1, 32);

	//ecs implementation

	map->LoadMap("Assets/map.map", 25, 20);

	//player class / put in assetmanager 
	player.addComponent<TransformComponent>(400, 320, 32, 32, 1);
	player.addComponent<SpriteComponent>("ship");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);


	//State class som tar han om lvls och spawning etc

	//assets->CreateProjectile(Vector2D(600, 600), Vector2D(2,0), 200, 2, "point");

}


auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& asstearoids(manager.getGroup(Game::groupAsstearoids));


void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{

	manager.refresh();
	manager.update();

	for (auto& a : asstearoids) // kolla player mot asteroid col
	{
		SDL_Rect aCollider = a->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, aCollider)) {
			player.destroy();

		}
	}

	for (auto& p : projectiles) {

		SDL_Rect pCollider = p->getComponent<ColliderComponent>().collider;
		for (auto& a : asstearoids) {
			if (Collision::AABB(pCollider, a->getComponent<ColliderComponent>().collider)) {
				// destroy Ass roid
			}
		}
	}





	// kolla projectile mot asteroid col


}


/// <summary>
/// The higher the render object is in this function the further back it renders
/// </summary>
void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles) t->draw();
	for (auto& p : projectiles) p->draw();
	for (auto& p : players) p->draw();
	for (auto& a : asstearoids) a->draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
