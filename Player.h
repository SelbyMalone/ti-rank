#include <string>

#ifndef TIRANK_PLAYER_H
#define TIRANK_PLAYER_H

//keeps track of a players statistics during a game
class Player {
    private:
        std::string name;
        std::string race;
        int rank;
        int raceRank;
        int score;
    public:
        Player(std::string name, std::string race, int rank, int raceRank, int score) {
            this->name = name; //players real name
            this->race = race; //in game faction
            this->rank = rank; //players current rank
            this->raceRank = raceRank; //players race rank
            this->score = score; //final score in game
        }
        bool operator< (Player &p2);
        std::string getName();
        std::string getRace();
        int getRank();
        int getRaceRank();
        int getScore();
        int adjustRank(int adjustment);
};

#endif //TIRANK_PLAYER_H
