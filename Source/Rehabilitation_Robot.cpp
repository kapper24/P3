// Rehabilitation_Robot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define SDL_MAIN_HANDLED
#include <iostream>
#include <armadillo>
#include <SDL.h>
#include "CrustCrawlerDynamics.h"
#include "CrustCrawlerKinematics.h"
#include "RehabilitationGame.h"
#include <SDL_ttf.h>
void settings();
int main()
{
    SDL_SetMainReady();
	//variables to use for the robot
	float armlength = 63;
	int functional_level = 2;
	bool quit = false;
	int mousecoordinatex;
	int mousecoordinatey;
	int settingsplacementx = 530;
	int startplacementx = 400;
	int quitplacementx = 660;
	int buttonplacementy = 120;
	int buttonw = 100;
	int buttonh = 30;
	bool continue_func = false;

	while (quit == false)
	{

		// make a window
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_Window* window = SDL_CreateWindow("GUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 957, 538, SDL_WINDOW_SHOWN);
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

		//init image loader functions
		const int FLAGS = IMG_INIT_PNG;

		//upload image file to memory as an sdl surface
		SDL_Surface* background = IMG_Load("armeobackground.png");


		//convert the image into something usefull
		SDL_Texture* armeobackground = SDL_CreateTextureFromSurface(renderer, background);

		SDL_Rect background_rect;
		background_rect.x = 0;
		background_rect.y = 0;
		background_rect.w = 957;
		background_rect.h = 538;

		SDL_RenderClear(renderer);

		//make the texture file into background
		SDL_RenderCopy(renderer, armeobackground, NULL, &background_rect);

		//present the rendered data
		SDL_RenderPresent(renderer);

		// create button for start
		SDL_Rect BUTTON_start;
		BUTTON_start.w = buttonw;
		BUTTON_start.h = buttonh;
		BUTTON_start.x = startplacementx;
		BUTTON_start.y = buttonplacementy;

		// create button for settings
		SDL_Rect BUTTON_settings;
		BUTTON_settings.w = buttonw;
		BUTTON_settings.h = buttonh;
		BUTTON_settings.x = settingsplacementx;
		BUTTON_settings.y = buttonplacementy;

		// create button for quitting
		SDL_Rect BUTTON_quit;
		BUTTON_quit.w = buttonw;
		BUTTON_quit.h = buttonh;
		BUTTON_quit.x = quitplacementx;
		BUTTON_quit.y = buttonplacementy;

		// draw button color
		SDL_SetRenderDrawColor(renderer, 192, 192, 192, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &BUTTON_start);
		SDL_RenderFillRect(renderer, &BUTTON_settings);
		SDL_RenderFillRect(renderer, &BUTTON_quit);
		SDL_RenderPresent(renderer);
		//initiate text library
		TTF_Init();
		//this opens a font style and sets a size
		TTF_Font* Sans = TTF_OpenFont("Roboto-Black.ttf", 20);
		// this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
		SDL_Color black = { 0, 0, 0 };
		// as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "settings", black);
		//now you can convert it into a texture like the image
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);


		//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

		//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

		SDL_RenderCopy(renderer, Message, NULL, &BUTTON_settings); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

		SDL_RenderPresent(renderer);
		//Don't forget to free your surface and texture
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);

		// create start button

		SDL_Surface* starttext = TTF_RenderText_Solid(Sans, "  Start  ", black);
		//now you can convert it into a texture like the image
		SDL_Texture* starttexttexture = SDL_CreateTextureFromSurface(renderer, starttext);

		SDL_Surface* quittext = TTF_RenderText_Solid(Sans, "  quit  ", black);
		//now you can convert it into a texture like the image
		SDL_Texture* quittexttexture = SDL_CreateTextureFromSurface(renderer, quittext);
		//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

		//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

		SDL_RenderCopy(renderer, starttexttexture, NULL, &BUTTON_start); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
		SDL_RenderCopy(renderer, quittexttexture, NULL, &BUTTON_quit);

		SDL_RenderPresent(renderer);


		while (continue_func == false)
		{


			SDL_Event Buttonclick;
			SDL_WaitEvent(&Buttonclick);

			switch (Buttonclick.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mousecoordinatex, &mousecoordinatey);
				if (mousecoordinatex < settingsplacementx + buttonw && mousecoordinatex > settingsplacementx && mousecoordinatey < buttonplacementy + buttonw && mousecoordinatey > buttonplacementy)
				{
					SDL_DestroyWindow(window);
					settings();
					continue_func = true;
				}

				if (mousecoordinatex < startplacementx + buttonw && mousecoordinatex > startplacementx && mousecoordinatey < buttonplacementy + buttonw && mousecoordinatey > buttonplacementy)
				{
					SDL_DestroyWindow(window);
					 RehabilitationGame game;
					game.init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
					 int i = 0;
						while (true) {
							
						game.update();
						game.render();
						}
						game.clean();
   
					continue_func = true;
				}

				if (mousecoordinatex < quitplacementx + buttonw && mousecoordinatex > quitplacementx && mousecoordinatey < buttonplacementy + buttonw && mousecoordinatey > buttonplacementy)
				{
					quit = true;
					continue_func = true;
				}

				break;
			default:
				break;
			}
		}
		continue_func = false;
	}

  
    
    
    return 0;
}
void settings() {
	bool settingscont = false;
	SDL_Window* settingswindow = SDL_CreateWindow("GUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 957, 538, SDL_WINDOW_SHOWN);
	SDL_Renderer* settingsrenderer = SDL_CreateRenderer(settingswindow, -1, 0);
	SDL_SetRenderDrawColor(settingsrenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(settingsrenderer);
	SDL_RenderPresent(settingsrenderer);
	while (settingscont == false)
	{


		SDL_Event Buttonclick;

		SDL_WaitEvent(&Buttonclick);
		switch (Buttonclick.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			settingscont = true;
			break;
		default:
			break;
		}
	}
	SDL_DestroyWindow(settingswindow);
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
