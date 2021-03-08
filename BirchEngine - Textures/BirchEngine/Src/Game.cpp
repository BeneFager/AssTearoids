#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "AssManager.h"


Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

//SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);
bool Game::isRunning = false;
bool Game::isPaused = false;
float Game::Time = 0.0f;
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

	assets->SetWindowSize(width,height);
	//AssManager* assMan = new AssManager(Game::assets);
	
	//assMan->SetWindowSize(width, height);

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
	assets->CreateAsstearoid(Vector2D(0, 0), Vector2D(-.1, -.1), 1, 36, 1, "Ass");
	manager.ChangeGameState(manager.PlayState);
	std::cout << manager.gameState << std::endl;
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

	if (Game::event.type == SDL_KEYUP)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (manager.gameState == manager.PlayState)
				manager.ChangeGameState(manager.MenuState);
			else
				manager.ChangeGameState(manager.PlayState);
			break;

		default:
			break;

		}
	}
}

void Game::update()
{

	manager.refresh();
	if (manager.gameState == manager.PlayState)
	{
		manager.update();
	}
	if (manager.gameState == manager.MenuState)
	{
		std::cout << manager.gameState << std::endl;


		//handleEvents();
		//manager.PauseUpdate();

		return;
	}

	for (auto& a : asstearoids) // kolla player mot asteroid col
	{
		SDL_Rect aCollider = a->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, aCollider))
		{
			player.destroy();
			//Todo lmao fix this
		}
	}
	// kolla projectile mot asteroid col
	for (auto& p : projectiles)
	{
		SDL_Rect pCollider = p->getComponent<ColliderComponent>().collider;
		for (auto& a : asstearoids)
		{
			if (Collision::AABB(pCollider, a->getComponent<ColliderComponent>().collider))
			{
				p->destroy();
				a->getComponent<AsstearoidComponent>().OnDestroy();
				assets->SpawnAss();
				
				std::cout << "p in ass" << std::endl;
				// destroy Ass roid
			}
		}
	}
}


/// <summary>
/// The higher the render object is in this function the further back it renders
/// </summary>
void Game::render()
{
	SDL_RenderClear(renderer);
	if (manager.gameState == manager.PlayState)
	{
		DrawGame();
	}
	else if (manager.gameState == manager.MenuState)
	{
		for (auto& t : tiles) t->draw();
		//DrawMenu();
	}
	SDL_RenderPresent(renderer);
}

void Game::DrawGame()
{
	for (auto& t : tiles) t->draw();
	for (auto& p : projectiles) p->draw();
	for (auto& p : players) p->draw();
	for (auto& a : asstearoids) a->draw();
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::Restart()
{

}
