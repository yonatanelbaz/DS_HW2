#ifndef TEAM_H
#define TEAM_H

#include "AVLTree.h"
#include "Player.h"

class Player;

class Team {
private:
    int teamId;
    int points;
    int numPlayers;
    bool teamValid;
    int goalKeepers;
    int sumGoals;
    int sumCards;
    int sumAbility;
    int gamesPlayed;
    bool knockedOut;
    AVLTree<std::shared_ptr<Player>> *playersById;
    AVLTree<std::shared_ptr<Player>> *playersByGoals;
    std::weak_ptr<Player> topScorer;

public:
    explicit Team(int teamId, int points);
    ~Team();
    void setSumGoals(int sumGoals);
    void setSumCards(int sumCards);
    int getSumCards();
    int getSumGoals();
    int getSumAbility();
    bool getKnockedOut();
    int getGamesPlayed();
    int getMatchScore();
    void decNumPlayers();
    void decGoalKeepers();
    AVLTree<std::shared_ptr<Player>>* getPlayersById();
    AVLTree<std::shared_ptr<Player>>* getPlayersByGoals();
    std::shared_ptr<Player> getTopScorer();
    void setNumPlayers(int numPlayers);
    void setNumPoints(int points);
    void setTeamId(int teamId);
    void setTeamValid(bool teamVaild);
    void setKnockedOut(bool knockedOut);
    void setTopScorer(const std::shared_ptr<Player>& player);
    void addSumAbility(int ability);
    void incNumPlayers();
    int getTeamId();
    int getPoints();
    int getNumPlayers();
    bool getTeamValid();
    int getGoalkeepers();
    void setGoalkeepers(int num);
    void incGoalKeepers();
    void incGamesPlayed();
    void setPlayersByGoals(AVLTree<std::shared_ptr<Player>>* playersByGoals);
    void setPlayersById(AVLTree<std::shared_ptr<Player>>* playersById);

    //void update(int gamesPlayed, int scoredGoals, int cardsReceived);
    static int compare_TeamID(const std::shared_ptr<Team> &team1, const std::shared_ptr<Team> &team2);
    void setGamesPlayed(int games);
};

#endif