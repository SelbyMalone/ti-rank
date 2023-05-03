#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <map>
#include "Player.h"
using namespace std;

//accepts a number between -14 and 14 and uses logistic function to get a number between 0 and 1 where -14 point
//difference is almost 0 and, equal score is 0.5 and +14 points is almost 1
double getScorePercent(int scoreDifference) {
    return 1/(1+pow(10,-0.13*scoreDifference));
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
int getEloAdjustment(Player playerA, Player playerB, int K) { //gets rank adjustment, add to player A and subtract player B
    return getEloAdjustment(playerA.getRank(), playerB.getRank(), playerA.getScore(), playerB.getScore(), K);
}

//uses better Elo adjustment for first place to give winner a better adjustment over everyone
int getEloAdjustmentFirstPlace(int elo, int opponentsElo, int K) {
    double expectedScore = 1/(1+pow(10,(double)(opponentsElo-elo)/400));
    return round(K*(1-expectedScore));
}

int getEloAdjustmentFirstPlace(Player playerA, Player playerB, int K) {
    return getEloAdjustmentFirstPlace(playerA.getRank(), playerB.getRank(), K);
}

//recursive function to compare all players score to eachother
void compareRecurse(map<Player*,pair<int, int>>::iterator it1, map<Player*,pair<int, int>>::iterator it2, map<Player*,pair<int, int>>*players) {
    if(it1==players->end()) { //if first iterator reaches the end, return
        return;
    }
    if(it2==players->end()) {   //if second iterator reaches the end, increase first iterator and move second iterator
                                //to value after first iterator
        compareRecurse(next(it1), next(it1,2), players);
        return;
    }
    //comparison code
    if(it1==players->begin()) {
        //gives an extra "victory bonus" to the player in first place, where the score is calculated as if the victor
        //scored 14 points and all other players have 0 points, this calculation has a significantly smaller development
        //coefficient (K) and only serves as a small bonus on top of normal point calculation

        int adjustment = getEloAdjustmentFirstPlace(*it1->first, *it2->first, 2);
        it1->second.first=it1->second.first+adjustment;
        it2->second.first=it2->second.first-adjustment;

        //race rank
        int raceAdjustment = getEloAdjustmentFirstPlace(it1->first->getRaceRank(), it2->first->getRaceRank(), 2);
        it1->second.second=it1->second.second+raceAdjustment;
        it2->second.second=it2->second.second-raceAdjustment;
    }
    //player rank
    int adjustment = getEloAdjustment(*it1->first, *it2->first, 20);
    it1->second.first=it1->second.first+adjustment;
    it2->second.first=it2->second.first-adjustment;

    //race rank
    int raceAdjustment = getEloAdjustment(it1->first->getRaceRank(), it2->first->getRaceRank(), it1->first->getScore(), it2->first->getScore(), 20);
    it1->second.second=it1->second.second+raceAdjustment;
    it2->second.second=it2->second.second-raceAdjustment;

    compareRecurse(it1, next(it2), players); //increase second iterator
}

int main() {
    cout << "Enter Player Count: ";
    int playerCount;
    cin >> playerCount;

    map<Player*, pair<int, int>>players; //stores each player and their rank adjustment and their race rank adjustment
    //input each player
    for(int i = 0; i < playerCount;) {
        cout << "Player " << ++i << endl;
        cout << "Enter Player Name: ";
        string name;
        cin >> name;

        cout << "Enter Player Race: ";
        string race;
        cin >> race;

        cout << "Enter Player Score: ";
        int score;
        cin >> score;

        ifstream playerFile;
        playerFile.open("Players/"+name+".json");

        if(playerFile) {
            Json::Reader reader;
            Json::Value jsonFile;
            reader.parse(playerFile, jsonFile);

            players[new Player(name, race, score, jsonFile)] = {0,0};
        } else {
            cout << "Enter Player Rank: ";
            int rank;
            cin >> rank;

            players[new Player(name, race, score, rank)] = {0,0};
        }
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
        cout << setw(5) << key->getRank() << " -> " << setw(5) << key->adjustRank(val.first);
        cout << " | ";
        cout << setw(3) << showpos << val.first << noshowpos;
        cout << "\n";

        Json::Value outJson = toJson(key);
        cout << outJson << endl;
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

    for(auto const& [key, val]:players) {
        cout << left << setw(10) << key->getRace();
        cout << " | ";
        cout << setw(5) << key->getScore();
        cout << " | ";
        cout << setw(5) << key->getRaceRank() << " -> " << setw(5) << key->adjustRaceRank(val.second);
        cout << " | ";
        cout << setw(3) << showpos << val.second << noshowpos;
        cout << "\n";
    }
}