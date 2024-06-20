#include "Player.h"

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
