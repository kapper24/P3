#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "RehabilitationGame.h"
class GameObject
{
public:
		std::string name;
		SDL_Texture* Sprite;
		SDL_Point Position;
		SDL_Point Size;
		SDL_Rect SrcR;
		SDL_Rect DestR;
		void Init(SDL_Renderer* renderer,int x, int y, int width, int height, const char* spriteLocation);
		void Update();
		void Render(SDL_Renderer* renderer);
};

