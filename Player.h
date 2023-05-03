#include <string>
#include <tuple>
#include "json/json.h"

#ifndef TIRANK_PLAYER_H
#define TIRANK_PLAYER_H
//JSON Serialization code

//struct to convert objects to property struct for JSON
template<typename Class, typename T>
struct PropertyImpl {
    constexpr PropertyImpl (T Class::*aMember, const char* aName) : member{aMember}, name{aName} {}

    using Type = T;
    T Class::*member;
    const char* name;
};

template<typename Class, typename T>
constexpr auto property(T Class::*member, const char* name) {
    return PropertyImpl<Class, T>(member, name);
}

//iterate on tuple
template<typename T, T... S, typename F>
constexpr void for_sequence(std::integer_sequence<T, S...>, F&& f) {
    (static_cast<void>(f(std::integral_constant<T,S>{})), ...);
}

//unserialize from JSON
template<typename T>
T fromJSON(const Json::Value& data);

//serialize to JSON
template<typename T>
Json::Value toJson(const T& object);


//keeps track of a players statistics during a game
static int count = 0;

class Player {
    private:
        int num; //arbitrary number used for sorting

        std::string name;
        std::string race;
        int rank;
        int raceRank = 1000;

        int score;

        int gamesPlayed;
        int raceGamesPlayed;

        double averageScore;
        double raceAverageScore;
    public:
        Player() {
            name = "";
            race = "";
            rank = 1000;
            raceRank = 1000;
            score = 0;
        }

        Player(std::string name, std::string race, int score, int rank) {
            this->name = name; //players real name
            this->race = race; //in game faction
            this->rank = rank; //players current rank
            this->score = score; //final score in game
            num = count++;
        }
        Player(std::string name, std::string race, int score, Json::Value playerFile) {
            this->name = name;
            this->race = race;
            this->score = score;
            num = count++;
            //TODO: Get Rank and RaceRank from file, if no entry for player/race exists in file, make new one with
            //default rank of 1000

            Player loadedFile = fromJSON<Player>(playerFile);
            this->rank = loadedFile.getRank();
            this->gamesPlayed = loadedFile.getRank()+1;
            this->averageScore = (loadedFile.averageScore + averageScore)/2;
        }
        //make tuple of player stats
        constexpr static auto propertiesPlayer = std::make_tuple(
                property(&Player::name, "name"),
                property(&Player::rank, "rank"),
                property(&Player::gamesPlayed, "gamesplayed"),
                property(&Player::averageScore, "averageScore")
                );

        //make tuple of race stats
        constexpr static auto propertiesRace = std::make_tuple(
                property(&Player::race, "name"),
                property(&Player::raceRank, "rank"),
                property(&Player::raceGamesPlayed, "gamesPlayed"),
                property(&Player::averageScore, "raceAverageScore")
                );

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
