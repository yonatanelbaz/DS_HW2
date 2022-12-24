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
    struct playerStruct {
        int id;
        int parentId;
        int size;
        shared_ptr<Team> team;
    };
    private:
    HashTable players;


public:

    UnionFind();
    StatusType addPlayer(shared_ptr<Player> p);
    Node<std::shared_ptr<Team>> * findTeam(int i);
    Node<std::shared_ptr<Player>>* getPlayerNode(int id);
};
#endif //DS_HW2_UNIONFIND_H
