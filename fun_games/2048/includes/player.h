#ifndef PLAYER_H
#define PLAYER_H

#include <cstring>

class Player {
	public:
	Player();
	virtual ~Player();
	unsigned long int getPlayerScore();
	void setPlayerScore(const unsigned long int &);
	void addToPlayerScore(const unsigned long int &);
	char *getPlayerName();
	void setPlayerName(const char *);

	protected:
	private:
	char playerName[30];
	unsigned long int playerScore;
};

#endif
