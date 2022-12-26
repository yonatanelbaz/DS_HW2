//
// Created by harel on 22/12/2022.
//
#include "UnionFind.h"
std::shared_ptr<Team> UnionFind::union(std::shared_ptr<Team> buyerTeam, std::shared_ptr<Team> boughtTeam) {
if(buyerTeam->g)
}

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
////TODO: add path shrink
permutation_t& UnionFind::calcPartialSpirit(int playerId) {
    auto tempPlayer = this->getPlayer(playerId);
    permutation_t calcSpirit =
}

std::shared_ptr<Player> UnionFind::getPlayer(int id) {
    auto playerNode = players.find(id);
    return playerNode->getValue().player;
}

