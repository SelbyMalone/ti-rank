#include <iostream>
#include "Player.h"

Player::Player() {
    std::cout << "Enter Player Name: ";
    std::cin >> this->name;

    std::cout << "Enter Player Race: ";
    std::cin >> this->race;

    std::cout << "Enter Player Rank: ";
    std::cin >> this->rank;

    std::cout << "Enter Race Rank: ";
    std::cin >> this->raceRank;

    std::cout << "Enter Player Score: ";
    std::cin >> this->score;
}

std::string Player::getName() {
    return name;
}

std::string Player::getRace() {
    return race;
}

int Player::getRank() {
    return rank;
}

int Player::getRaceRank() {
    return raceRank;
}

int Player::getScore() {
    return score;
}

int Player::adjustRank(int adjustment) {
    rank = rank+adjustment;
    return rank;
}

int Player::adjustRaceRank(int adjustment) {
    raceRank = raceRank+adjustment;
    return raceRank;
}

bool Player::operator<(Player &p2) {
    return num<p2.num;
}
