#include "RehabilitationGame.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include "CrustCrawlerKinematics.h"
#include "SimpleSerial.h"
#include <string>
#include <sstream>
std::vector<RehabilitationGame::GameObject> asteroids;
RehabilitationGame::GameObject player;
CrustCrawlerKinematics CCK;
CrustCrawlerKinematics::Angles TargetAngles;
double currentPosX = 0;
double currentPosY = 147;
double currentPosZ = 210;
SDL_Event event;
SimpleSerial serial("COM3",9600);
int counter = 0;
void RehabilitationGame::init(const char* title, int posx, int posy, int width, int height, MyoController &collector)
{
	GameSettings();
	
	CrustCrawlerKinematics::Pos tempPos;
	tempPos = CCK.ForwardKinematics(0, 45, 80, 180);
	currentPosX = tempPos.x;
	currentPosZ = tempPos.z;
	currentPosY = tempPos.y;
	TargetAngles = CCK.InverseKinematics(currentPosX, currentPosY, currentPosZ);

	TargetAngles.theta1 += 90;
	TargetAngles.theta2 += 180;
	TargetAngles.theta3 += 180;
	TargetAngles.theta4 += 180;

	std::string message = "1 " + std::to_string(int(TargetAngles.theta1)) + ":" +
		"2 " + std::to_string(int(TargetAngles.theta2)) + ":" +
		"3 " + std::to_string(int(TargetAngles.theta3)) + ":" +
		"4 " + std::to_string(int(TargetAngles.theta4)) + ":";
	std::cout << message << std::endl;
	serial.writeString(message);
	
	SDL_Init(SDL_INIT_EVERYTHING);
	const int FlAGS = IMG_INIT_PNG;
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow(title, posx, posy, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Surface *temp;
	temp = IMG_Load("Sea.png");
	
	background = SDL_CreateTextureFromSurface(renderer, temp);
		
	for (int i = 0; i < NumberOfPoints; i++)
	{
		GameObject asteroid;
		asteroids.push_back(asteroid);
	}
	std::cout << asteroids.size() << std::endl;
	startGame = true;
	SDL_Delay(3000);
}

void RehabilitationGame::update(MyoController& collector)
{
	counter++;
	
	if (startGame) {

		if (!gameIsInitialized) {
			initGameObject(player,400,300,50,50,"Boat.png","Player");
			for (int i = 0; i < asteroids.size(); i++)
			{
				srand(time(NULL)+i*i);
				initGameObject(asteroids[i], rand() % 450 + 150, rand() % 450 + 150, 50, 50, "Ice.png", "Asteroid");
				SDL_Delay(100);
				std::cout << "init Asteroid: " << i << std::endl;
			}
			gameIsInitialized = true;
			
		}
		else {
			// In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
		// In this case, we wish to update our display 20 times a second, so we run for 1000/20 milliseconds.
			

			
			
			for (int i = 0; i < asteroids.size(); i++) {
				UpdateGameObject(asteroids[i]);
				srand(time(NULL) + i);
				if ((player.DestR.x - asteroids[i].DestR.x) * (player.DestR.x - asteroids[i].DestR.x) + (player.DestR.y - asteroids[i].DestR.y) * (player.DestR.y - asteroids[i].DestR.y) < 50 * 50) {
					asteroids[i].DestR.x = rand() % 450 + 150;
					SDL_Delay(300);
					asteroids[i].DestR.y = rand() % 450 + 150, 50, 50;
				}
			}	
			    
			if (collector.Direction == MyoController::Left) {
				player.xdir = -1;
				player.ydir = 0;
				double targetX, targetY, targetZ;
				targetX = currentPosX + player.xdir;
				targetY = currentPosY;
				targetZ = currentPosZ + player.ydir;

				
				//if (targetX * targetX + targetY * targetY + targetZ * targetZ <= 370 * 370) {
					currentPosX -= player.xdir;
					currentPosZ -= player.ydir;
				//}
				
				

			}
			else if (collector.Direction == MyoController::Right) {
				player.xdir = 1;
				player.ydir = 0;
				double targetX, targetY, targetZ;
				targetX = currentPosX + player.xdir;
				targetY = currentPosY;
				targetZ = currentPosZ + player.ydir;
				//if (targetX * targetX + targetY * targetY + targetZ * targetZ <= 370 * 370) {
					currentPosX -= player.xdir;
					currentPosZ -= player.ydir;
				//}
				
			}
			else if (collector.Direction == MyoController::Down) {
				player.xdir = 0;
				player.ydir = 1;
				double targetX, targetY, targetZ;
				targetX = currentPosX + player.xdir;
				targetY = currentPosY;
				targetZ = currentPosZ + player.ydir;
				//if (targetX * targetX + targetY * targetY + targetZ * targetZ <= 370 * 370) {
					currentPosX -= player.xdir;
					currentPosZ -= player.ydir;
				//}
				
			}
			else if (collector.Direction == MyoController::Up) {
				player.xdir = 0;
				player.ydir = -1;
				double targetX, targetY, targetZ;
				targetX = currentPosX + player.xdir;
				targetY = currentPosY;
				targetZ = currentPosZ + player.ydir;
				//if (targetX * targetX + targetY * targetY + targetZ * targetZ <= 360 * 360) {
					currentPosX -= player.xdir;
					currentPosZ -= player.ydir;
				//}
				

			}
			else {
				player.xdir = 0;
				player.ydir = 0;
			}
			TargetAngles = CCK.InverseKinematics(currentPosX, currentPosY, currentPosZ);
			std::string message = "";
			if (TargetAngles.theta1 + TargetAngles.theta2 + TargetAngles.theta3 + TargetAngles.theta4 <= 1440) {
				TargetAngles.theta1 += 90;
				TargetAngles.theta2 += 180;
				TargetAngles.theta3 += 180;
				TargetAngles.theta4 += 180;
				message = "1 " + std::to_string(int(TargetAngles.theta1)) + ":" +
					"2 " + std::to_string(int(TargetAngles.theta2)) + ":" +
					"3 " + std::to_string(int(TargetAngles.theta3)) + ":" +
					"4 " + std::to_string(int(TargetAngles.theta4)) + ":";

				if (counter == 10) {
					serial.writeString(message);
					counter = 0;
				}
			}
			else {
				CrustCrawlerKinematics::Pos tempPos;
				tempPos = CCK.ForwardKinematics(0, 45, 80, 180);
				currentPosX = tempPos.x;
				currentPosZ = tempPos.z;
				currentPosY = tempPos.y;
				TargetAngles = CCK.InverseKinematics(currentPosX, currentPosY, currentPosZ);

				TargetAngles.theta1 += 90;
				TargetAngles.theta2 += 180;
				TargetAngles.theta3 += 180;
				TargetAngles.theta4 += 180;

				std::string message = "1 " + std::to_string(int(TargetAngles.theta1)) + ":" +
					"2 " + std::to_string(int(TargetAngles.theta2)) + ":" +
					"3 " + std::to_string(int(TargetAngles.theta3)) + ":" +
					"4 " + std::to_string(int(TargetAngles.theta4)) + ":";
				std::cout << message << std::endl;
				serial.writeString(message);
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
		

		gameObject.DestR.x += gameObject.xdir*2;
		gameObject.DestR.y += gameObject.ydir*2;
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

void RehabilitationGame::GameSettings()
{
	SDL_Window* settingswindow = SDL_CreateWindow("Game Settings", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 360, SDL_WINDOW_SHOWN);
	SDL_Renderer* settingsrenderer = SDL_CreateRenderer(settingswindow, -1, 0);
	SDL_SetRenderDrawColor(settingsrenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(settingsrenderer);
	SDL_RenderPresent(settingsrenderer);
	SDL_Rect GameSettingsHeight;
	GameSettingsHeight.x = 94;
	GameSettingsHeight.y = 60;
	GameSettingsHeight.w = 181;
	GameSettingsHeight.h = 60;
	SDL_Rect GameSettingsHeightValue;
	GameSettingsHeightValue.x = 276;
	GameSettingsHeightValue.y = 60;
	GameSettingsHeightValue.w = 113;
	GameSettingsHeightValue.h = 60;
	SDL_Rect GameSettingsDist;
	GameSettingsDist.x = 94;
	GameSettingsDist.y = 122;
	GameSettingsDist.w = 181;
	GameSettingsDist.h = 60;
	SDL_Rect GameSettingsDistValue;
	GameSettingsDistValue.x = 276;
	GameSettingsDistValue.y = 122;
	GameSettingsDistValue.w = 113;
	GameSettingsDistValue.h = 60;
	SDL_Rect GameSettingsPoints;
	GameSettingsPoints.x = 94;
	GameSettingsPoints.y = 184;
	GameSettingsPoints.w = 181;
	GameSettingsPoints.h = 60;
	SDL_Rect GameSettingsPointsValue;
	GameSettingsPointsValue.x = 276;
	GameSettingsPointsValue.y = 184;
	GameSettingsPointsValue.w = 113;
	GameSettingsPointsValue.h = 60;
	SDL_Rect GameSettingsDone;
	GameSettingsDone.x = 145;
	GameSettingsDone.y = 270;
	GameSettingsDone.w = 208;
	GameSettingsDone.h = 40;
	
	SDL_SetRenderDrawColor(settingsrenderer, 192, 192, 192, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(settingsrenderer, &GameSettingsHeight);
	SDL_RenderFillRect(settingsrenderer, &GameSettingsPoints);
	SDL_RenderFillRect(settingsrenderer, &GameSettingsDist);
	SDL_RenderFillRect(settingsrenderer, &GameSettingsDone);

	SDL_RenderFillRect(settingsrenderer, &GameSettingsHeightValue);
	SDL_RenderFillRect(settingsrenderer, &GameSettingsPointsValue);
	SDL_RenderFillRect(settingsrenderer, &GameSettingsDistValue);
	
	TTF_Init();
	TTF_Font* TextFont = TTF_OpenFont("Roboto-Black.ttf", 16);
	SDL_Color black = { 0, 0, 0 };

	SDL_Surface* HeightText = TTF_RenderText_Solid(TextFont, "  Shoulder Height : ", black);
	SDL_Texture* HeightTexture = SDL_CreateTextureFromSurface(settingsrenderer, HeightText);
	SDL_RenderCopy(settingsrenderer, HeightTexture, NULL, &GameSettingsHeight);

	SDL_Surface* DistText = TTF_RenderText_Solid(TextFont, "  Distance :       ", black);
	SDL_Texture* DistTexture = SDL_CreateTextureFromSurface(settingsrenderer, DistText);
	SDL_RenderCopy(settingsrenderer, DistTexture, NULL, &GameSettingsDist);

	SDL_Surface* PointsText = TTF_RenderText_Solid(TextFont, "  Number of points :", black);
	SDL_Texture* PointsTexture = SDL_CreateTextureFromSurface(settingsrenderer, PointsText);
	SDL_RenderCopy(settingsrenderer, PointsTexture, NULL, &GameSettingsPoints);

	SDL_Surface* DoneText = TTF_RenderText_Solid(TextFont, "  Done  ", black);
	SDL_Texture* DoneTexture = SDL_CreateTextureFromSurface(settingsrenderer, DoneText);
	SDL_RenderCopy(settingsrenderer, DoneTexture, NULL, &GameSettingsDone);
	std::stringstream text;
	text << "" << CCK.ShoulderHeightFromBase;
	
	SDL_Surface* HeightValueText = TTF_RenderText_Solid(TextFont, text.str().c_str(), black);
	SDL_Texture* HeightValueTexture = SDL_CreateTextureFromSurface(settingsrenderer, HeightValueText);
	SDL_RenderCopy(settingsrenderer, HeightValueTexture, NULL, &GameSettingsHeightValue);
	
	text.str("");
	text << "" << CCK.ShoulderDistanceFromBase;
	SDL_Surface* DistValueText = TTF_RenderText_Solid(TextFont, text.str().c_str(), black);
	SDL_Texture* DistValueTexture = SDL_CreateTextureFromSurface(settingsrenderer, DistValueText);
	SDL_RenderCopy(settingsrenderer, DistValueTexture, NULL, &GameSettingsDistValue);

	text.str("");
	text << "" << NumberOfPoints;
	SDL_Surface* PointsValueText = TTF_RenderText_Solid(TextFont, text.str().c_str(), black);
	SDL_Texture* PointsValueTexture = SDL_CreateTextureFromSurface(settingsrenderer, PointsValueText);
	SDL_RenderCopy(settingsrenderer, PointsValueTexture, NULL, &GameSettingsPointsValue);

	SDL_Surface* DoneValueText = TTF_RenderText_Solid(TextFont, "  Done  ", black);
	SDL_Texture* DoneValueTexture = SDL_CreateTextureFromSurface(settingsrenderer, DoneText);
	SDL_RenderCopy(settingsrenderer, DoneValueTexture, NULL, &GameSettingsDone);


	SDL_RenderPresent(settingsrenderer);
	int MousePosX, MousePosY;
	bool endsettings = false;
	while (endsettings == false)
	{
		SDL_Event Buttonclick;
		SDL_WaitEvent(&Buttonclick);
		switch (Buttonclick.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&MousePosX, &MousePosY);
			if (MousePosX > GameSettingsDone.x && MousePosX < GameSettingsDone.w + GameSettingsDone.x && MousePosY > GameSettingsDone.y && MousePosY < GameSettingsDone.h + GameSettingsDone.y)
			{
				endsettings = true;
			}
			else if (MousePosX > GameSettingsHeightValue.x && MousePosX < GameSettingsHeightValue.w + GameSettingsHeightValue.x && MousePosY > GameSettingsHeightValue.y && MousePosY < GameSettingsHeightValue.h + GameSettingsHeightValue.y) {
			text.str("100");
			SDL_Surface* HeightValueText = TTF_RenderText_Solid(TextFont, text.str().c_str(), black);
			SDL_Texture* HeightValueTexture = SDL_CreateTextureFromSurface(settingsrenderer, HeightValueText);
			SDL_RenderCopy(settingsrenderer, HeightValueTexture, NULL, &GameSettingsHeightValue);
			SDL_RenderPresent(settingsrenderer);
			SDL_StartTextInput();

			SDL_Event event;
			SDL_WaitEvent(&event);
			switch (event.type) {
				case SDL_TEXTINPUT:

					break;
			}
			}
			else if (MousePosX > GameSettingsDistValue.x && MousePosX < GameSettingsDistValue.w + GameSettingsDistValue.x && MousePosY > GameSettingsDistValue.y && MousePosY < GameSettingsDistValue.h + GameSettingsDistValue.y) {

			}
			else if (MousePosX > GameSettingsPointsValue.x && MousePosX < GameSettingsPointsValue.w + GameSettingsPointsValue.x && MousePosY > GameSettingsPointsValue.y && MousePosY < GameSettingsPointsValue.h + GameSettingsPointsValue.y)
			{

			}
			break;
		default:
			break;
		}
	}
	SDL_DestroyWindow(settingswindow);
}

