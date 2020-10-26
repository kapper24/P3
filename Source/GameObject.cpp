#include "GameObject.h"

void GameObject::Init(SDL_Renderer* renderer,int x, int y, int width, int height, const char* spriteLocation)
{
	Position.x = x;
	Position.y = y;
	Size.x = width;
	Size.y = height;
	SDL_Surface* temp = IMG_Load(spriteLocation);
	Sprite = SDL_CreateTextureFromSurface(renderer,temp);
}

void GameObject::Update()
{
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = Size.x;
	SrcR.h = Size.y;

	DestR.x = Position.x;
	DestR.y = Position.y;
	DestR.w = Size.x;
	DestR.h = Size.y;
}

void GameObject::Render(SDL_Renderer* renderer)
{
	
	SDL_RenderCopy(renderer, Sprite, &SrcR, &DestR);
}
