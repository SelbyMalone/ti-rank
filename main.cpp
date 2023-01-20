#include <iostream>
#include <cmath>
using namespace std;

int developmentCoefficient = 20; //determines for Elo Adjustment how strongly a result affects changes



double getScorePercent(int scoreDifference) {   //accepts a number between -14 and 14 and converts it into a range
                                                //between 0 and 1 (-14 -> 0, 0 -> 0.5, 14 -> 1)
    return ((double)scoreDifference+14)/28;
}

int getEloAdjustment(int elo, int opponentsElo, int score, int opponentsScore) { //performs elo calculation by using
    double scoreDifference = getScorePercent(score-opponentsScore);   //rank difference between two
                                                                                    //players to create an expected
                                                                                    //score (point difference between
                                                                                    //two players) and then adjusts
                                                                                    //players ranks based on actual
                                                                                    //point difference after a game
                                                                                    //returning the adjustment value
    double expectedScore = 1/(1+pow(10,(double)(opponentsElo-elo)/400));
    return round(developmentCoefficient*(scoreDifference-expectedScore));
}

int main() {
    cout << "Player A's Rank: ";
    int aRank;
    cin >> aRank;
    cout << "Player A's Score: ";
    int aScore;
    cin >> aScore;

    cout << "Player B's Rank: ";
    int bRank;
    cin >> bRank;
    cout << "Player B's Score: ";
    int bScore;
    cin >> bScore;

    cout << "=====" << endl;

    int aAdjust = getEloAdjustment(aRank, bRank, aScore, bScore);
    int bAdjust = -aAdjust;

    cout << "Player A's rank change: " << showpos << aAdjust << endl;
    cout << "Player A's new rank: " << noshowpos << aRank + aAdjust << endl;

    cout << "=====" << endl;

    cout << "Player B's rank change: " << showpos << bAdjust << endl;
    cout << "Player B's new rank: " << noshowpos << bRank + bAdjust;
}
