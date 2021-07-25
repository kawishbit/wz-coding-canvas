#include "game.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_W 119
#define KEY_D 100
#define KEY_S 115
#define KEY_A 97
#define KEY_X 120
#define KEYUP_W 87
#define KEYUP_D 68
#define KEYUP_S 83
#define KEYUP_A 65
#define KEYUP_X 88
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51

Game::Game() {
	//constructor
}

Game::~Game() {
	//constructor
}

Game::GameState Game::gameState;
bool Game::gameOver = false;
int Game::panel[4][4];
Player *Game::player = nullptr;

void Game::initGame() {
	srand(time(0));
	gameState = GameState::PLAYING;
	rlutil::setConsoleTitle("2048 Game Console Version");
	rlutil::setBackgroundColor(rlutil::COLORS::WHITE);
	rlutil::hidecursor();
}
void Game::startGame() {
	initGame();
	while (gameState != GameState::QUIT) {
		rlutil::cls();
		showGameTitle();
		showMenu();
		char menuChoice;
		do {
			menuChoice = takeGameInput();
			switch (menuChoice) {
				case KEY_3:
					gameState = GameState::QUIT;
					break;
				case KEY_1:
					gamePlay();
					_getch();
					break;
				case KEY_2:
					showHighScoreTable();
					_getch();
					break;
			}
		} while (
		    menuChoice < KEY_1 &&
		    menuChoice > KEY_3);
	}
}

void Game::showGameTitle() {
	rlutil::setColor(rlutil::COLORS::BLACK);
	/* Display the 2048 Game Title */
	std::cout << "\n\n\n";
	std::cout << "\t ------------------------------------------------------------------------------------ \n\n";
	std::cout << "\t    /\\\\\\\\\\\\\\\\\\          /\\\\\\\\\\\\\\                /\\\\\\         /\\\\\\\\\\\\\\\\\\ \n";
	std::cout << "\t   /\\\\\\///////\\\\\\      /\\\\\\/////\\\\\\            /\\\\\\\\\\       /\\\\\\///////\\\\\\\n";
	std::cout << "\t   \\///      \\//\\\\\\    /\\\\\\    \\//\\\\\\         /\\\\\\/\\\\\\      \\/\\\\\\     \\/\\\\\\ \n";
	std::cout << "\t              /\\\\\\/    \\/\\\\\\     \\/\\\\\\       /\\\\\\/\\/\\\\\\      \\///\\\\\\\\\\\\\\\\\\/ \n";
	std::cout << "\t            /\\\\\\//      \\/\\\\\\     \\/\\\\\\     /\\\\\\/  \\/\\\\\\       /\\\\\\///////\\\\\\\n";
	std::cout << "\t          /\\\\\\//         \\/\\\\\\     \\/\\\\\\   /\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\   /\\\\\\      \\//\\\\\\ \n";
	std::cout << "\t         /\\\\\\/            \\//\\\\\\    /\\\\\\   \\///////////\\\\\\//   \\//\\\\\\      /\\\\\\\n";
	std::cout << "\t         /\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\   \\///\\\\\\\\\\\\\\/              \\/\\\\\\      \\///\\\\\\\\\\\\\\\\\\/\n";
	std::cout << "\t         \\///////////////      \\///////                \\///         \\///////// \n\n";
	std::cout << "\t ------------------------------------------------------------------------------------ \n\n\n";
	rlutil::setColor(Utilities::defaultTextColor);
}

void Game::showMenu() {
	Utilities::print("\t\t\t\t    ------ MAIN MENU ------\n", true, rlutil::COLORS::BLACK, 0);
	Utilities::print("\t\t\t\t         1. PLAY GAME ", true, rlutil::COLORS::BLUE, 0);
	Utilities::print("\t\t\t\t         2. HIGH SCORES ", true, rlutil::COLORS::BLUE, 0);
	Utilities::print("\t\t\t\t         3. QUIT ", true, rlutil::COLORS::BLUE, 0);
	Utilities::print("\n\t\t\t\t      ( Enter Your Choice )       ", true, rlutil::COLORS::RED, Utilities::defaultDelay);
}

void Game::gamePlay() {
	rlutil::cls();
	resetGame();
	gameLoop();
}

void Game::gameLoop() {
	while (!gameOver) {
		showGamePlayPanel();
		char actionKey;
		do {
			actionKey = takeGameInput();

		} while (
		    actionKey != KEY_UP &&
		    actionKey != KEY_DOWN &&
		    actionKey != KEY_LEFT &&
		    actionKey != KEY_RIGHT &&
		    actionKey != KEY_W &&
		    actionKey != KEY_D &&
		    actionKey != KEY_S &&
		    actionKey != KEY_A &&
		    actionKey != KEYUP_W &&
		    actionKey != KEYUP_D &&
		    actionKey != KEYUP_S &&
		    actionKey != KEYUP_X &&
		    actionKey != KEY_X &&
		    actionKey != KEYUP_A);
		handleGameInput(actionKey);
	}
	rlutil::cls();
	if (gameOver) {
		Utilities::print("\n\t\tGame Over, Better Luck Next Time...", true, rlutil::COLORS::LIGHTRED, Utilities::defaultDelay);
		Utilities::print("\n\t\tPlease Provide us with Your Name [max 29 characters]: ", false, rlutil::COLORS::BLACK, Utilities::defaultDelay);
		char name[30];
		std::cin.getline(name, sizeof name);
		player->setPlayerName(name);

		std::cout << "\n\n\t\t PLAYER DETAILS \n";
		std::cout << "\n\t\t Name : " << player->getPlayerName();
		std::cout << "\n\t\t Score : " << player->getPlayerScore();

		Utilities::print("\n\n\t\t Uploading Player Details", false);
		Utilities::print("...", true, Utilities::defaultTextColor, Utilities::defaultDelay * 10);
		uploadWinnerData();
		Utilities::print("\n\t\t Done.", true, rlutil::COLORS::BLUE, 0);
		Utilities::print("\n\t\t Press any to return to main menu.", true, rlutil::COLORS::BLUE, 0);
	}

	delete player;
	player = nullptr;
}
void Game::showGamePlayPanel() {
	rlutil::cls();
	std::cout << "\n\n\n";
	Utilities::print("\t\t\t    ------+ GAME PLAY +------", true, rlutil::COLORS::LIGHTRED, 0);
	rlutil::setColor(rlutil::COLORS::BLACK);
	std::cout << "\n\t\t\t  +--------+--------+--------+--------+";
	std::cout << "\n\t\t\t  |        |        |        |        |";
	std::cout << "\n\t\t\t  |        |        |        |        |";
	std::cout << "\n\t\t\t  |        |        |        |        |";
	std::cout << "\n\t\t\t  +--------+--------+--------+--------+";
	std::cout << "\n\t\t\t  |        |        |        |        |";
	std::cout << "\n\t\t\t  |        |        |        |        |";
	std::cout << "\n\t\t\t  |        |        |        |        |";
	std::cout << "\n\t\t\t  +--------+--------+--------+--------+";
	std::cout << "\n\t\t\t  |        |        |        |        |";
	std::cout << "\n\t\t\t  |        |        |        |        |";
	std::cout << "\n\t\t\t  |        |        |        |        |";
	std::cout << "\n\t\t\t  +--------+--------+--------+--------+";
	std::cout << "\n\t\t\t  |        |        |        |        |";
	std::cout << "\n\t\t\t  |        |        |        |        |";
	std::cout << "\n\t\t\t  |        |        |        |        |";
	std::cout << "\n\t\t\t  +--------+--------+--------+--------+";

	rlutil::setColor(Utilities::defaultTextColor);
	const int xInit = 31, yInit = 8, gapHoriz = 9, gapVert = 4;

	for (int i = 0; i < 4; i++) {
		int y = yInit + i * gapVert;
		for (int j = 0; j < 4; j++) {
			int x = xInit + j * gapHoriz;
			rlutil::locate(x, y);
			if (panel[i][j] == -1) {
				std::cout << " ";
			} else {
				int key = log2(panel[i][j]);
				int colorIndex = Utilities::defaultTextColor;

				switch (key) {
					case 1:
					case 2:
						colorIndex = Utilities::defaultTextColor;
						break;

					case 3:
						colorIndex = rlutil::COLORS::DARKGREY;
						break;

					case 4:
						colorIndex = rlutil::COLORS::GREEN;
						break;

					case 5:
						colorIndex = rlutil::COLORS::BROWN;
						break;

					case 6:
						colorIndex = rlutil::COLORS::LIGHTMAGENTA;
						break;

					case 7:
						colorIndex = rlutil::COLORS::LIGHTRED;
						break;

					case 8:
						colorIndex = rlutil::COLORS::RED;
						break;

					case 9:
						colorIndex = rlutil::COLORS::BLUE;
						break;

					case 10:
						colorIndex = rlutil::COLORS::MAGENTA;
						break;

					case 11:
						colorIndex = rlutil::COLORS::GREEN;
						break;

					case 12:
						colorIndex = rlutil::COLORS::CYAN;
						break;
					default:
						colorIndex = Utilities::defaultTextColor;
						break;
				}
				rlutil::setColor(colorIndex);
				std::cout << panel[i][j];
				rlutil::setColor(Utilities::defaultTextColor);
			}
		}
	}

	rlutil::locate(75, 5);
	std::cout << "- CONTROLS -";
	rlutil::setColor(rlutil::COLORS::BLUE);
	rlutil::locate(75, 8);
	std::cout << "UP    :  W / ARROW_UP";
	rlutil::locate(75, 10);
	std::cout << "DOWN  :  S / ARROW_DOWN";
	rlutil::locate(75, 12);
	std::cout << "LEFT  :  A / ARROW_LEFT";
	rlutil::locate(75, 14);
	std::cout << "RIGHT :  D / ARROW_RIGHT";
	rlutil::setColor(rlutil::COLORS::LIGHTRED);
	rlutil::locate(75, 17);
	std::cout << "EXIT  :  X";
	rlutil::setColor(Utilities::defaultTextColor);

	Utilities::print("\n\n\n\n\n\n\n\n \t\t\t\t  SCORE : " + std::to_string(player->getPlayerScore()), true, rlutil::COLORS::BLUE, 0);
}

int Game::takeGameInput() {
	return _getch();
}
void Game::handleGameInput(const int &actionKey) {
	switch (actionKey) {
		case KEYUP_X:
		case KEY_X:
			gameOver = true;
			return;
			break;
		case KEYUP_W:
		case KEY_UP:
		case KEY_W:
			actionUp();
			break;
		case KEYUP_S:
		case KEY_DOWN:
		case KEY_S:
			actionDown();
			break;
		case KEYUP_A:
		case KEY_LEFT:
		case KEY_A:
			actionLeft();
			break;
		case KEYUP_D:
		case KEY_RIGHT:
		case KEY_D:
			actionRight();
			break;
	}
	gameOver = checkGameOver();
	if (!gameOver) {
		fillRandomTile();
	}
}
void Game::actionUp() {
	unsigned long int scoreAdd = 0;
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (panel[i][j] != -1) {
				int k = 0;
				for (k = 0; k <= i; k++)
					if (panel[k][j] == -1)
						break;

				if (k <= i) {
					panel[k][j] = panel[i][j];
					panel[i][j] = -1;

					if (k - 1 >= 0) {
						if (panel[k - 1][j] == panel[k][j]) {
							panel[k - 1][j] += panel[k][j];
							scoreAdd = panel[k - 1][j];
							panel[k][j] = -1;
						}
					}
				} else if (i - 1 >= 0) {
					if (panel[i][j] == panel[i - 1][j]) {
						panel[i - 1][j] += panel[i][j];
						scoreAdd = panel[i - 1][j];
						panel[i][j] = -1;
					}
				}
			}
		}
	}
	player->addToPlayerScore(scoreAdd);
}
void Game::actionDown() {
	unsigned long int scoreAdd = 0;
	for (int j = 0; j < 4; j++) {
		for (int i = 3; i >= 0; i--) {
			if (panel[i][j] != -1) {
				int k = 0;
				for (k = 3; k >= i; k--)
					if (panel[k][j] == -1)
						break;

				if (k >= i) {
					panel[k][j] = panel[i][j];
					panel[i][j] = -1;
					if (k + 1 <= 3) {
						if (panel[k + 1][j] == panel[k][j]) {
							panel[k + 1][j] += panel[k][j];
							scoreAdd = panel[k + 1][j];
							panel[k][j] = -1;
						}
					}
				} else if (i + 1 <= 3) {
					if (panel[i][j] == panel[i + 1][j]) {
						panel[i + 1][j] += panel[i][j];
						scoreAdd = panel[i + 1][j];
						panel[i][j] = -1;
					}
				}
			}
		}
	}
	player->addToPlayerScore(scoreAdd);
}
void Game::actionLeft() {
	unsigned long int scoreAdd = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (panel[i][j] != -1) {
				int k = 0;
				for (k = 0; k <= j; k++)
					if (panel[i][k] == -1)
						break;

				if (k <= j) {
					panel[i][k] = panel[i][j];
					panel[i][j] = -1;
					if (k - 1 >= 0) {
						if (panel[i][k - 1] == panel[i][k]) {
							panel[i][k - 1] += panel[i][k];
							scoreAdd = panel[i][k - 1];
							panel[i][k] = -1;
						}
					}
				} else if (j - 1 >= 0) {
					if (panel[i][j] == panel[i][j - 1]) {
						panel[i][j - 1] += panel[i][j];
						scoreAdd = panel[i][j - 1];
						panel[i][j] = -1;
					}
				}
			}
		}
	}
	player->addToPlayerScore(scoreAdd);
}
void Game::actionRight() {
	unsigned long int scoreAdd = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j >= 0; j--) {
			if (panel[i][j] != -1) {
				int k = 0;
				for (k = 3; k >= j; k--)
					if (panel[i][k] == -1)
						break;

				if (k >= j) {
					panel[i][k] = panel[i][j];
					panel[i][j] = -1;
					if (k + 1 <= 3) {
						if (panel[i][k + 1] == panel[i][k]) {
							panel[i][k + 1] += panel[i][k];
							scoreAdd = panel[i][k + 1];
							panel[i][k] = -1;
						}
					}
				} else if (j + 1 <= 3) {
					if (panel[i][j] == panel[i][j + 1]) {
						panel[i][j + 1] += panel[i][j];
						scoreAdd = panel[i][j + 1];
						panel[i][j] = -1;
					}
				}
			}
		}
	}
	player->addToPlayerScore(scoreAdd);
}

void Game::fillRandomTile() {
	int tileNum = Utilities::getRandomNumber(1, getEmptyTiles());
	int possibleValues[] = {2, 4};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (panel[i][j] == -1) {
				tileNum--;
				if (tileNum == 0) {
					try {
						int index = Utilities::getRandomNumber(0, 1);
						if (index < 0 || index > 1)
							throw "Invalid Index Accessed";
						panel[i][j] = possibleValues[index];
					} catch (const char *error) {
						panel[i][j] = 2;
						Debugger::handleException(error);
					}

					break;
				}
			}
		}
	}
}

int Game::getEmptyTiles() {
	int tilesCount = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (panel[i][j] == -1)
				tilesCount++;
		}
	}
	return tilesCount;
}
void Game::resetGame() {
	gameOver = false;
	if (player != nullptr)
		delete player;
	try {
		player = new Player();
	} catch (const std::bad_alloc &err) {
		Debugger::handleException(err.what(), true);
	} catch (...) {
		Debugger::handleException("UNDEFINED ERROR", true);
	}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			panel[i][j] = -1;

	fillRandomTile();
	fillRandomTile();
}

bool Game::checkGameOver() {
	int leftMoves = getEmptyTiles();
	return leftMoves <= 0;
}
void Game::uploadWinnerData() {
	bool isLast = true;
	Player currPlayer;
	std::ifstream fin;
	std::ofstream fout;
	try {
		fin.open(Utilities::defaultHighscoreFileName);
		if (!fin) {
			std::ofstream f(Utilities::defaultHighscoreFileName);
			f.close();
			fin.open(Utilities::defaultHighscoreFileName);
		}

		fout.open("temp.txt");
	} catch (const char *errMessage) {
		Debugger::handleException(errMessage);
	}

	while (!fin.eof()) {
		fin.read((char *)&currPlayer, sizeof(Player));
		if (currPlayer.getPlayerScore() <= player->getPlayerScore()) {
			fout.write((char *)player, sizeof(Player));
			fout.write((char *)&currPlayer, sizeof(Player));
			isLast = false;  //indicate record inserted, and not last record
			break;
		} else {
			fout.write((char *)&currPlayer, sizeof(Player));
		}
	}
	if (isLast) {
		fout.write((char *)player, sizeof(Player));
	} else if (!fin.eof()) {
		while (!fin.eof()) {
			fin.read((char *)&currPlayer, sizeof(Player));
			fout.write((char *)&currPlayer, sizeof(Player));
		}
	}
	fin.close();
	fout.close();
	try {
		std::remove(Utilities::defaultHighscoreFileName);
		std::rename("temp.txt", Utilities::defaultHighscoreFileName);
	} catch (...) {
		Debugger::handleException("Error in Deleting/Renaming Files");
	}
}
void Game::showHighScoreTable() {
	rlutil::cls();
	Utilities::print("\n\n\t\t   -----+ HIGH SCORES +----- ", true, rlutil::COLORS::BLACK, 0);
	std::cout << "\n\n\t\t";
	std::cout.setf(std::ios::left);
	std::cout << std::setw(7) << "SR";
	std::cout << std::setw(30) << "NAME";
	std::cout << std::setw(20) << "SCORE ";
	std::cout << "\n\t      -----------------------------------------------------\n";

	std::ifstream fin;
	try {
		fin.open(Utilities::defaultHighscoreFileName);
		if (!fin) {
			std::ofstream f(Utilities::defaultHighscoreFileName);
			f.close();
			fin.open(Utilities::defaultHighscoreFileName);
		}
	} catch (const char *errMessage) {
		Debugger::handleException(errMessage);
	}
	int serialNo = 1;
	while (!fin.eof()) {
		Player currPlayerData;
		fin.read((char *)&currPlayerData, sizeof(Player));
		std::cout << "\n\t\t";
		if (currPlayerData.getPlayerScore() > 0) {
			std::cout << std::setw(7) << serialNo++;
			std::cout << std::setw(30) << currPlayerData.getPlayerName();
			std::cout << std::setw(20) << currPlayerData.getPlayerScore();
		}
	}

	fin.close();
}
