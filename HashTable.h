//
// Created by harel on 24/12/2022.
//

#ifndef DS_HW2_HASHTABLE_H
#define DS_HW2_HASHTABLE_H
#include "Team.h"
#include "Player.h"
#include "UnionFind.h"
#include "worldcup23a2.h"
#include "AVLTree.h"
class HashTable {
    /*struct playerStruct {
        shared_ptr<Player> player;
        Node<playerStruct>* parent;
        shared_ptr<Team> team;
    };
     */
private:
    int numOfPlayers;
    int capacity;
    Node<playerStruct>** arr;

public:
    HashTable(int value);
    void insert(shared_ptr<Player> p, shared_ptr<Team> team);
    int hashFunc(int id);
    void extendRehash();
    //void shrinkRehash();
    Node<playerStruct>* find(int id);
};
#endif //DS_HW2_HASHTABLE_H
