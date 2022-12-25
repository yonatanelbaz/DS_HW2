//
// Created by harel on 22/12/2022.
//
#include "UnionFind.h"
StatusType UnionFind::addPlayer(shared_ptr<Player> p, shared_ptr<Team> team) {
    try{
        players.insert(p, team);
    }
    catch(const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}
////TODO: maybe a never ending loop
////TODO: add path shrink
std::shared_ptr<Team> UnionFind::findTeam(int id) {
    auto t = players.find(id);
    auto curr = t;
    while(curr->getValue().team == nullptr || curr->getValue().parentInTree!= nullptr) {
        curr = curr->getValue().parentInTree;
    }
    return curr->getValue().team;
}

std::shared_ptr<Player> UnionFind::getPlayer(int id) {
    auto playerNode = players.find(id);
    return playerNode->getValue().player;
}

std::shared_ptr<Team> UnionFind::union(std::shared_ptr<Team> t1, std::shared_ptr<Team> t2) {

}
