#include "Game.h"
#include <SDL.h>
#include <algorithm>
#include "Combat.h"
#include "Player.h"
#include "Window.h"
#include "Input.h"
#include <string>
#include <iostream>
#include "Displaystats.h"

extern int g_playerSpendMp, g_maxMp, g_HpRed, g_playerHp, g_playerTotalDamage, g_magicManipulationSkillExp, g_swordArtsSkillExp, g_currentExp;
extern double g_monHp, g_monTotalDamage;

namespace {
	const int FPS = 60;
	const int MAX_FRAME_TIME = 1000 / FPS;
}


Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->running();
}


Game::~Game()
{
}


long double currentExp, totalExp(0);
std::string charName;
bool stop(false), controlStop(false);
char YN;

void Game::running()
{
	Window screen;
	Input input;
	SDL_Event event;

	//this->_player = Sprite(graphics, "INSERT FILEPATH HERE", START X, STRT Y, END X, END Y, SCREEN POS X, SCREEN POS Y);
	this->_character.character(totalExp, 0, g_playerSpendMp, charName, false);

	int LAST_UPDATE_TIME = SDL_GetTicks();


	//Startet Spielschleife
	while (true) {

		input.startFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
					std::cout <<"Hi";
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
				std::cout << "Eh?";
			}
			else if (event.type == SDL_QUIT) {
				std::cout << "By";
				return;
			}
		}

				//Schlie�t das Programm wenn ALT + F4 gedr�ckt wird
		if (input.wasKeyPressed(SDL_SCANCODE_LALT) == true){
			if (input.wasKeyPressed(SDL_SCANCODE_F4) == true) {
				return;
			}
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		std::cout << CURRENT_TIME_MS << "\n";
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		std::cout << ELAPSED_TIME_MS << "\n";

		this->_screen = screen;
		std::cout << this->_screen.getRenderer() << "\n";
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		//This allways creates a new window instead of updation the content
		//Something about blitSurface?
		this->draw(screen);

		/*
		After  this follows a sequenze of stuff that has to be updated
		It should not be used like this	
		The whole combat.cpp has to be updated or flat out removed
		currently it buggs
		*/
		/*
		std::cout << "Input your character name: ";
		std::getline(std::cin, charName);
		std::cout << "\n\n";
		std::cin >> totalExp;
		std::cin >> g_magicManipulationSkillExp;
		std::cin >> g_swordArtsSkillExp;
		player player1;
		combat battle;

		//Initialisiert den Charakter
		player1.character(totalExp, 0, 0, charName, false);
		//Zeigt Charakterfenster an
		player1.displayStatsWindow(window, 1, charName);
		std::cout << "\n\n";

		//Initiates combat //Starte Kampfphase
		do {

			currentExp = battle.battle(totalExp, charName);
			totalExp = currentExp + totalExp;
			//Aktualisiert Spieler
			player1.character(totalExp, 0, g_playerSpendMp, charName, false);

			//Displays player Status 
			//Zeigt spieler Status an wenn Exp nicht 0 ist (In diesem Falle w�rde der Status in combat.cpp dargestellt
			if (currentExp != 0) {
				player1.character(totalExp, 0, g_playerSpendMp, charName, false);
				player1.displayStatsWindow(window, 1, charName);
			}

			//Fragt ob die Schleife abgebrochen werden soll
			while (1) {		//Asks for continuation of monster encounters/ simple loop
				std::cout << "\nStop? Y/N\n";
				std::cin >> YN;
				if (YN == 'Y') {
					stop = true;
					break;
				}
				if (YN == 'y') {
					stop = true;
					break;
				}
				if (YN == 'n') {
					stop = false;
					break;
				}
				if (YN == 'N') {
					stop = false;
					break;
				}
			}

		} while (stop == false);


		*/
	}
}

void Game::draw(Window & screen)
{
	screen.clear();

	//this->_sprite.draw(screen, SCREEN POS X, SCREEN POS Y);
	//this->_battleWindow.battleWindow(screen, 10, 200, 1, 100, 100, 100, 100, "Void");
	this->_character.displayStatsWindow(screen, 3, charName);


	screen.flip();
}

void Game::update(float elapsedTime)
{

}


