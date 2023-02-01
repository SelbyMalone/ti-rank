#include <string>
#include <tuple>
#include <jsoncpp/json/json.h>

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
T fromJSON(const Json::)

//serialize to JSON


static int count = 0;
//keeps track of a players statistics during a game
class Player {
    private:
        int num; //arbitrary number used for sorting

        std::string name;
        std::string race;
        int rank;
        int raceRank;

        int score;

        int gamesPlayed;
        int raceGamesPlayed;

        double averageScore;
        double raceAverageScore;
    public:
        Player(std::string name, std::string race, int rank, int raceRank, int score) {
            this->name = name; //players real name
            this->race = race; //in game faction
            this->rank = rank; //players current rank
            this->raceRank = raceRank; //players race rank
            this->score = score; //final score in game
            num = count++;
        }
        Player(std::string name, std::string race, int score) {
            this->name = name;
            this->race = race;
            this->score = score;
            num = count++;
            //TODO: Get Rank and RaceRank from file, if no entry for player/race exists in file, make new one with
            //default rank of 1000
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
