#include "RehabilitationGame.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
std::vector<RehabilitationGame::GameObject> asteroids;
RehabilitationGame::GameObject player;
SDL_Event event;
void RehabilitationGame::init(const char* title, int posx, int posy, int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	const int FlAGS = IMG_INIT_PNG;
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow(title, posx, posy, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Surface *temp;
	temp = IMG_Load("backgroundSpace.png");
	
	background = SDL_CreateTextureFromSurface(renderer, temp);
		
	for (int i = 0; i < 1; i++)
	{
		GameObject asteroid;
		asteroids.push_back(asteroid);
	}
	std::cout << asteroids.size() << std::endl;
	startGame = true;
}

void RehabilitationGame::update()
{
	if (startGame) {
		if (!gameIsInitialized) {
			initGameObject(player,0	,0,50,50,"SpaceShip.png","Player");
			for (int i = 0; i < asteroids.size(); i++)
			{
				srand(time(NULL)+i*i);
				initGameObject(asteroids[i], rand() % 650 + 50, rand() % 550 + 0, 50, 50, "Asteroid.png", "Asteroid");
				SDL_Delay(100);
				std::cout << "init Asteroid: " << i << std::endl;
			}
			gameIsInitialized = true;
		}
		else {
			
			
			for (int i = 0; i < asteroids.size(); i++) {
				float x = asteroids[i].DestR.x - player.DestR.x;
				float y = asteroids[i].DestR.y - player.DestR.y;
				
				player.xdir = x/sqrt(x*x + y*y);
				player.ydir = y/sqrt(x*x+y*y);
				if (x > 0) {
					player.xdir += 1;
				}
				else if (x < 0) {
					player.xdir -= 1;
				}
				if (y > 0) {
					y += 1;
				}
				else if (player.ydir < 0) {
					player.ydir -= 1;
				}
				UpdateGameObject(asteroids[i]);
				srand(time(NULL) + i);
				if ((player.DestR.x - asteroids[i].DestR.x) * (player.DestR.x - asteroids[i].DestR.x) + (player.DestR.y - asteroids[i].DestR.y) * (player.DestR.y - asteroids[i].DestR.y) < 50 * 50) {
					asteroids[i].DestR.x = rand() % 650 + 50;
					SDL_Delay(300);
					asteroids[i].DestR.y = rand() % 550 + 0, 50, 50;
				}
			}	
			UpdateGameObject(player);
		}
		
	}
	else {
		clean();
	}
	
}

void RehabilitationGame::render()
{	
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	if (gameIsInitialized) {
		RenderGameObject(player);
		for (int i = 0; i < asteroids.size(); i++) {
			RenderGameObject(asteroids[i]);
			//SDL_RenderPresent(renderer);
		}
	}

	
	SDL_RenderPresent(renderer);
}

void RehabilitationGame::initGameObject(GameObject& gameObject,int x, int y, int width, int height, const char* spriteLocation, std::string name)
{
	gameObject.name = name;
	gameObject.Position.x = x;
	gameObject.Position.y = y;
	gameObject.Size.x = width;
	gameObject.Size.y = height;
	gameObject.DestR.x = gameObject.Position.x;
	gameObject.DestR.y = gameObject.Position.y;
	gameObject.DestR.w = gameObject.Size.x;
	gameObject.DestR.h = gameObject.Size.y;
	SDL_Surface* temp = IMG_Load(spriteLocation);
	gameObject.Sprite = SDL_CreateTextureFromSurface(renderer, temp);
}

void RehabilitationGame::UpdateGameObject(GameObject& gameObject)
{
		

		gameObject.DestR.x += gameObject.xdir;
		gameObject.DestR.y += gameObject.ydir;
		gameObject.DestR.w = gameObject.Size.x;
		gameObject.DestR.h = gameObject.Size.y;
	
	
}

void RehabilitationGame::RenderGameObject(GameObject& gameObject)
{
	SDL_RenderCopy(renderer, gameObject.Sprite, NULL, &gameObject.DestR);
}

void RehabilitationGame::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
}

