#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>
#include <vector>
#include "Player.h"
using namespace std;

//make maxScore a global variable otherwise it'll have to be passed through almost every function
int maxScore;

////Calculate ELO adjustments between players

//accepts a number between -maxScore and maxScore and uses logistic function to get a number between 0 and 1 where -maxScore point
//difference is almost 0 and, equal score is 0.5 and +maxScore points is almost 1
double getScorePercent(int scoreDifference) {
    double steepness = -1.82; //negative number that determines the "steepness" of the logistics function, larger
                              //number means score differences approach +/- 1 quicker
    return 1/(1+pow(10, steepness*((double)scoreDifference/maxScore)));
}

//performs elo calculation by using rank difference between two players to create an expected score (point difference
// between two players) and then adjusts players ranks based on actual point difference after a game returning the
// adjustment value
int getEloAdjustment(int elo, int opponentsElo, int score, int opponentsScore, int K) {
    double scoreDifference = getScorePercent(score-opponentsScore);
    double expectedScore = 1/(1+pow(10,(double)(opponentsElo-elo)/400));
    return round(K*(scoreDifference-expectedScore));
}

//calls getEloAdjustment with player parameters
int getEloAdjustment(Player* playerA, Player* playerB, int K) { //gets rank adjustment, add to player A and subtract player B
    return getEloAdjustment(playerA->getRank(), playerB->getRank(), playerA->getScore(), playerB->getScore(), K);
}

//uses better Elo adjustment for first place to give winner a better adjustment over everyone
int getEloAdjustmentFirstPlace(int elo, int opponentsElo, int K) {
    double expectedScore = 1/(1+pow(10,(double)(opponentsElo-elo)/400));
    return round(K*(1-expectedScore));
}

int getEloAdjustmentFirstPlace(Player* playerA, Player* playerB, int K) {
    return getEloAdjustmentFirstPlace(playerA->getRank(), playerB->getRank(), K);
}  


//recursive function to compare all players score to eachother
void compareRecurse(map<Player*, pair<int, int>>& players, vector<Player*>& playerOrder,
                    vector<Player*>::iterator it1, vector<Player*>::iterator it2) {
    //if it1 equals players.end, return
    if (it1 == playerOrder.end()) {
        return;
    }

    if (it2 == playerOrder.end()) {
        ++it1;
        it2 = it1;
        if (it2 != playerOrder.end()) {
            ++it2;
        }
        compareRecurse(players, playerOrder, it1, it2);
        return;
    }

    //comparison code
    if(it1==playerOrder.begin()) {
        //gives an extra "victory bonus" to the player in first place, where the score is calculated as if the victor
        //scored 14 points and all other players have 0 points, this calculation has a significantly smaller development
        //coefficient (K) and only serves as a small bonus on top of normal point calculation
        int adjustment = getEloAdjustmentFirstPlace(*it1, *it2, 2);
        players[*it1].first+=adjustment;
        players[*it2].first-=adjustment;

        //race rank
        int raceAdjustment = getEloAdjustmentFirstPlace((*it1)->getRaceRank(), (*it2)->getRaceRank(), 2);
        players[*it1].second+=raceAdjustment;
        players[*it2].second -= raceAdjustment;
    }
    //player rank
    int adjustment = getEloAdjustment(*it1, *it2, 20);
    players[*it1].first += adjustment;
    players[*it2].first -= adjustment;

    //race rank
    int raceAdjustment = getEloAdjustment((*it1)->getRaceRank(), (*it2)->getRaceRank(), (*it1)->getScore(), (*it2)->getScore(), 20);
    players[*it1].second += raceAdjustment;
    players[*it2].second -= raceAdjustment;

    compareRecurse(players, playerOrder, it1, ++it2); //increase second iterator
}

//// Extract functions from main to make main simpler

Player* getPlayer(int playerNum) {
    if (playerNum == 0) {
        cout << "Winner" << endl;
    }
    else {
        cout << "Player " << playerNum+1 << endl;
    }
    cout << "Enter Player Name: ";
    string name;
    cin >> name;

    cout << "Enter Player Race: ";
    string race;
    cin >> race;

    cout << "Enter Player Rank: ";
    int rank;
    cin >> rank;

    cout << "Enter Race Rank: ";
    int raceRank;
    cin >> raceRank;

    cout << "Enter Player Score: ";
    int score;
    cin >> score;

    Player* newplayer = new Player(name, race, rank, raceRank, score);
    return newplayer;
}

int main() {
    cout << "Enter Player Count: ";
    int playerCount;
    cin >> playerCount;

    cout << "Enter Max Score: ";
    cin >> maxScore;

    map<Player*, pair<int, int>>players; //stores each player and their rank adjustment and their race rank adjustment
    vector<Player*> playerOrder; //preserve the order players are entered


    //input each player
    for(int i = 0; i < playerCount;i++) {
        Player* newplayer = getPlayer(i);
        players[newplayer] = {0, 0};
        playerOrder.push_back(newplayer);
    }

    //compare all players score difference to all other players and store adjustment to their score in map
    auto it1 = playerOrder.begin();
    compareRecurse(players, playerOrder, it1, next(it1));

    //TODO: Less spaghetti way of printing table
    cout << left << setw(10) << "Player";
    cout << " | ";
    cout << left << setw(5) << "Score";
    cout << " | ";
    cout << left << setw(14) << "Rank";
    cout << " | ";
    cout << left << setw(3) << "adj";
    cout << "\n-----------+-------+----------------+----" << endl;

    for(auto & it : playerOrder) {
        cout << left << setw(10) << it->getName();
        cout << " | ";
        cout << setw(5) << it->getScore();
        cout << " | ";
        cout << setw(5) << it->getRank() << " -> " << setw(5) << it->adjustRank(players[it].first);
        cout << " | ";
        cout << setw(3) << showpos << players[it].first << noshowpos;
        cout << "\n";
    }
    cout << "-----------+-------+----------------+----" << endl;

    cout << left << setw(10) << "Race";
    cout << " | ";
    cout << left << setw(5) << "Score";
    cout << " | ";
    cout << left << setw(14) << "Rank";
    cout << " | ";
    cout << left << setw(3) << "adj";
    cout << "\n-----------+-------+----------------+----" << endl;

    for (auto& it : playerOrder) {
        cout << left << setw(10) << it->getRace();
        cout << " | ";
        cout << setw(5) << it->getScore();
        cout << " | ";
        cout << setw(5) << it->getRaceRank() << " -> " << setw(5) << it->adjustRaceRank(players[it].second);
        cout << " | ";
        cout << setw(3) << showpos << players[it].second << noshowpos;
        cout << "\n";
    }
}
