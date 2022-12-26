//
// Created by harel on 27/11/2022.
//
#ifndef DATA_STRUCTURES_1_PLAYER_H
#define DATA_STRUCTURES_1_PLAYER_H
#include "AVLTree.h"
#include "UnionFind.h"
#include "HashTable.h"
#include "worldcup23a2.h"
#include "Team.h"
#include "wet2util.h"

class Team;

class Player{
private:
    int playerId;
    int gamesPlayed;
    int cardsReceived;
    bool goalKeeper;
    int ability;
    permutation_t &spirit;

public:
    static int compare_playerID(const std::shared_ptr<Player> &a, const std::shared_ptr<Player> &b);
    static int compare_playerGoals(const std::shared_ptr<Player> &player1, const std::shared_ptr<Player> &player2);
    static int compare_playerCards(const std::shared_ptr<Player> &player1, const std::shared_ptr<Player> &player2);
    Player(int playerId, int gamesPlayed, int ability, int cardsReceived, bool goalKeeper, const permutation_t &spirit): playerId(playerId),
    gamesPlayed(gamesPlayed), ability(ability), cardsReceived(cardsReceived), goalKeeper(goalKeeper), spirit(spirit){};
    Player(const Player& other);
    void update(int gamesPlayed, int scoredGoals, int cardsReceived);
    void updateTeam();
    void setSpirit(const permutation_t& spirit);
    int getGamesPlayed();
    int getPlayerGoals();
    int getCards();
    permutation_t& getSpirit();
    int getAbility();
    int getPlayerId();
    bool getGoalKeeper();
    int getTeamId();
    void setSpirit(const permutation_t& spirit);
    void setTeam(std::shared_ptr<Team> team);
    std::shared_ptr<Team> getTeam();
    std::shared_ptr<Player> getClosestBelow();
    std::shared_ptr<Player> getClosestAbove();
    void setClosestBelow(const std::shared_ptr<Player>& player);
    void setClosestAbove(const std::shared_ptr<Player>& player);
    void setAbility(int ability);
    void setGamesPlayed(int games);
    void setGoalKeeper(bool goalKeeper);
    void addGamesPlayed(int games);
    void addCards(int cards);
    Player()=default;
    void setPlayerTeam(const std::shared_ptr<Team>& t);
    ////add play dtor
     ~Player()=default;
};

#endif //DATA_STRUCTURES_1_PLAYER_H
