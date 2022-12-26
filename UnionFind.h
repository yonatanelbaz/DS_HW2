//
// Created by harel on 22/12/2022.
//

#ifndef DS_HW2_UNIONFIND_H
#define DS_HW2_UNIONFIND_H
#include "AVLTree.h"
#include "Team.h"
#include "Player.h"
#include "HashTable.h"
using namespace std;
class UnionFind {
    private:
    HashTable players;


public:
    struct playerStruct {
        shared_ptr<Player> player;
        Node<playerStruct>* parentInTree;
        shared_ptr<Team> team;
        Node<playerStruct>* rootOfTree;
    };
    UnionFind();
    StatusType addPlayer(shared_ptr<Player> p, std::shared_ptr<Team> team);
    std::shared_ptr<Team> findTeam(int id);
    std::shared_ptr<Player> getPlayer(int id);
    std::shared_ptr<Team> union(std::shared_ptr<Team> buyerTeam, std::shared_ptr<Team> boughtTeam);
    permutation_t& calcPartialSpirit(int playerId);
};
#endif //DS_HW2_UNIONFIND_H
