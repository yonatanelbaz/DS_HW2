#include "HashTable.h"

//
// Created by harel on 24/12/2022.
//
int HashTable::hashFunc(int id) {
    return id%capacity;
}

Node<UnionFind::playerStruct>* HashTable::find(int id) {
    auto currNode = this->arr[this->hashFunc(id)];
    while(currNode != nullptr) {
        if(currNode->getValue().player->getPlayerId() == id) {
            return currNode;
        }
        currNode = currNode->getParent();
    }
    return nullptr;
}

void HashTable::extendRehash() {
    int capacityBeforeExtension = this->capacity;
    Node<UnionFind::playerStruct>** tempArr = arr;
    this->capacity = this->capacity * 2;
    this->arr = new Node<UnionFind::playerStruct>*[this->capacity];
    for(int i=0; i<capacityBeforeExtension; i++) {
        arr[i] = nullptr;
    }
    for(int i=0; i<capacityBeforeExtension; i++) {
        auto currNode = tempArr[i];
        while(currNode!= nullptr) {
            auto currPlayer = currNode->getValue();
            this->insert(currPlayer.player, currPlayer.team);
            currNode = currNode->getParent();
        }
    }
    delete[] tempArr;
}

void HashTable::insert(shared_ptr<Player> p, shared_ptr<Team> team) {
    if(numOfPlayers == this->capacity) {
        this->extendRehash();
    }
    auto currNode = this->arr[this->hashFunc(p->getPlayerId())];
    try {
        UnionFind::playerStruct newStruct;
        newStruct.team = team;
        newStruct.player = p;
        newStruct.parentInTree = team->getLastInserted();
        newStruct.rootOfTree = team->getRootOfTree();
        auto newNode = new Node<UnionFind::playerStruct>(newStruct);
        this->numOfPlayers = this->numOfPlayers+1;
        if(currNode== nullptr) {
            //TODO: check this
            this->arr[this->hashFunc(p->getPlayerId())] = newNode;
            team->setLastInserted(newNode);
            newNode->setParent(nullptr);
            team->setRootOfTree(newNode);
        } else {
            while(currNode->getParent()!= nullptr) {
                currNode = currNode->getParent();
            }
            //insert into the chain hashing
            currNode->setParent(newNode);
            team->setLastInserted(currNode);
            if(team->getRootOfTree() == nullptr) {
                team->setRootOfTree(newNode);
            }
        }
    }
    catch(const std::exception& e) {
        throw StatusType::ALLOCATION_ERROR;
    }
}

