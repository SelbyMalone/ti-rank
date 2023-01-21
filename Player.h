#include <string>

#ifndef TIRANK_PLAYER_H
#define TIRANK_PLAYER_H
static int count = 0;
//keeps track of a players statistics during a game
class Player {
    private:
        std::string name;
        std::string race;
        int rank;
        int raceRank;
        int score;
        int num; //arbitrary number used for sorting
    public:
        Player(std::string name, std::string race, int rank, int raceRank, int score) {
            this->name = name; //players real name
            this->race = race; //in game faction
            this->rank = rank; //players current rank
            this->raceRank = raceRank; //players race rank
            this->score = score; //final score in game
            num = count++;
        }
        std::string getName();
        std::string getRace();
        int getRank();
        int getRaceRank();
        int getScore();
        int adjustRank(int adjustment); //return rank after and adjustment and updates rank
        int adjustRaceRank(int adjustment);

        bool operator< (Player &p2);
};

#endif //TIRANK_PLAYER_H
