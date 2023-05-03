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

template<typename T>
T fromJSON(const Json::Value& data) {
    T object;

    //get number of properties
    constexpr auto nbProperties  = std::tuple_size<decltype(T::propertiesPlayer)>::value;

    //iterate on index sequence of size nbProperties
    for_sequence(std::make_index_sequence<nbProperties>{}, [&](auto i) {
        //get property
        constexpr auto property = std::get<i>(T::propertiesPlayer);

        //get property type
        using Type = typename decltype(property)::Type;

        //set value to the member
        object.*(property.member) = data[property.name].template as<Type>();
    });

    return object;
}

template<typename T>
Json::Value toJson(const T& object) {
    Json::Value data;

    //get number of properties
    constexpr auto nbProperties = std::tuple_size<decltype(T::properties)>::value;

    //iterate on index sequence of size nbProperties
    for_sequence(std::make_index_sequence<nbProperties>{}, [&](auto i) {
       //get property
       constexpr auto property = std::get<i>(T::properties);

       //set value to the member
       data[property.name] = object.*(property.member);
    });

    return data;
}