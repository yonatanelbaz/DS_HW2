#include "HashTable.h"

//
// Created by harel on 24/12/2022.
//
int HashTable::hashFunc(int id) {
    return id%capacity;
}
void HashTable::insert(int id) {
    auto currNode = this->arr[this->hashFunc(id)];
    try {
        Node<HashTable::playerStruct>* newNode = new Node<HashTable::playerStruct>();
        if(currNode== nullptr) {

        } else {
            while(currNode->getParent()!= nullptr) {
                currNode = currNode->getParent();
            }
            currNode->setParent(newNode);
        }
    }
    catch(const std::exception& e) {
        throw StatusType::ALLOCATION_ERROR;
    }
}

