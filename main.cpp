#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>
#include "Player.h"
using namespace std;

int developmentCoefficient = 40; //determines for Elo Adjustment how strongly a result affects changes

double getScorePercent(int scoreDifference) {   //accepts a number between -14 and 14 and converts it into a range
                                                //between 0 and 1 (-14 -> 0, 0 -> 0.5, 14 -> 1)
    return ((double)scoreDifference+14)/28;
}

//performs elo calculation by using rank difference between two players to create an expected score (point difference
// between two players) and then adjusts players ranks based on actual point difference after a game returning the
// adjustment value
int getEloAdjustment(int elo, int opponentsElo, int score, int opponentsScore) {
    double scoreDifference = getScorePercent(score-opponentsScore);
    double expectedScore = 1/(1+pow(10,(double)(opponentsElo-elo)/400));
    return round(developmentCoefficient*(scoreDifference-expectedScore));
}

//calls getEloAdjustment with player parameters
int getEloAdjustment(Player playerA, Player playerB) { //gets rank adjustment, add to player A and subtract player B
    return getEloAdjustment(playerA.getRank(), playerB.getRank(), playerA.getScore(), playerB.getScore());
}

//recursive function to compare all players score to eachother
void compareRecurse(map<Player*, int>::iterator it1, map<Player*, int>::iterator it2, map<Player*,int>*players) {
    if(it1==players->end()) { //if first iterator reaches the end, return
        return;
    }
    if(it2==players->end()) {   //if second iterator reaches the end, increase first iterator and move second iterator
                                //to value after first iterator
        compareRecurse(next(it1), next(it1,2), players);
        return;
    }
    //comparison code
    int adjustment = getEloAdjustment(*it1->first, *it2->first);
    it1->second=it1->second+adjustment;
    it2->second=it2->second-adjustment;

    compareRecurse(it1, next(it2), players); //increase second iterator
}

int main() {
    cout << "Enter Player Count: ";
    int playerCount;
    cin >> playerCount;

    map<Player*, int>players; //stores each player and their total rank adjustment
    //input each player
    for(int i = 0; i < playerCount;) {
        cout << "Player " << ++i << endl;
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

        players[new Player(name, race, rank, raceRank, score)] = 0;
    }

    //compare all players score difference to all other players and store adjustment to their score in map
    auto it1 = players.begin();
    compareRecurse(it1, next(it1), &players);

    cout << left << setw(10) << "Player";
    cout << " | ";
    cout << left << setw(5) << "Score";
    cout << " | ";
    cout << left << setw(14) << "Rank";
    cout << " | ";
    cout << left << setw(3) << "adj";
    cout << "\n-----------+-------+----------------+----" << endl;

    for(auto const& [key, val]:players) {
        cout << left << setw(10) << key->getName();
        cout << " | ";
        cout << setw(5) << key->getScore();
        cout << " | ";
        cout << setw(5) << key->getRank() << " -> " << setw(5) << key->adjustRank(val);
        cout << " | ";
        cout << setw(3) << showpos << val << noshowpos;
        cout << "\n";
    }
}