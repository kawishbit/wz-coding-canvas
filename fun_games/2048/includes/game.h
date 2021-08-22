#ifndef GAME_H
#define GAME_H

#include <time.h>

#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>

#include "debugger.h"
#include "player.h"
#include "util.h"

class Game {
  public:
	Game();
	virtual ~Game();

	static void startGame();

  private:
	enum class GameState {
		PLAYING,
		QUIT
	};

	static GameState gameState;
	static bool gameOver;
	static int panel[4][4];
	static Player *player;

	static void showGameTitle();
	static void showMenu();
	static void gamePlay();
	static void gameLoop();
	static void initGame();
	static void showGamePlayPanel();
	static int takeGameInput();
	static void handleGameInput(const int &);
	static void actionUp();
	static void actionDown();
	static void actionLeft();
	static void actionRight();
	static void fillRandomTile();
	static int getEmptyTiles();
	static void resetGame();
	static bool checkGameOver();
	static void uploadWinnerData();
	static void showHighScoreTable();
};

#endif
