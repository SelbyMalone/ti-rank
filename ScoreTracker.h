#include<vector>
#include<string>

#ifndef TIRANK_SCORETRACKER_H
#define TIRANK_SCORETRACKER_H
class AdjustmentRecord {
    private:
        std::string name; //name of player who made this adjustmnet
        int rank;
        int score;
        int adjustment;
    public:
        AdjustmentRecord(std::string name, int rank, int score, int adjustment);
};

class ScoreTracker {
    private:
        int totalAdjustment;
        int totalRaceAdjustment;
        std::vector<AdjustmentRecord>records;
        int rank;
        int raceRank;
    public:
        ScoreTracker(int rank, int racerank);
        int getRank();
        int getRaceRank();
        void addAdjustment(AdjustmentRecord adj);
        void addRaceAdjustment(AdjustmentRecord adj);
};


#endif //TIRANK_SCORETRACKER_H
