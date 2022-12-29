//
// Created by יובל קרן on 12/20/2022.
//

#include "playerHashMap.h"
#include <cassert>


Node::Node(Player *player): player(player) {
    team = player->getTeam();
    id = player->getPlayerId();
    rank = player->getSpirit();
    parent = nullptr;
    sizeOfTree = 1;
    smallestNodeSpirit = permutation_t::neutral();
    wasRepresenative = false;
    gamesPlayedRank = 0;
}

Player* Node::getPlayer() const {
    return player;
}

int Node::getPlayerId() const {
    return id;
}

Team* Node::getTeam() const {
    return team;
}

void playerHashMap::add(Node* node) {
    Player* player = node->getPlayer();
    int playerId = player->getPlayerId();
    assert(find(player) == -1);
    int index = hash(playerId);
    if(array[index].isEmpty)  //object isnt already in hash map
    {
        array[index].node = node;
        array[index].isEmpty = false;
        ++numOfPlayers;
        if (arrayLength == numOfPlayers){
            expand();
        }
    }
}



int playerHashMap::hash(int playerId) const {
    assert (arrayLength != numOfPlayers);
    int hashVal = hashFunction1(playerId, arrayLength);
    int stepSize = hashFunction2(playerId, arrayLength);
    while (array[hashVal].isEmpty != true && array[hashVal].node->getPlayerId() != playerId){
        hashVal = hashVal + stepSize;
        hashVal %= arrayLength;
    }
    return hashVal;
}

void playerHashMap::expand() {
    playerStruct* temp = array;
    try {
        array = new playerStruct[2*arrayLength];
        arrayLength *=2;
    }
    catch (std::bad_alloc& e){
        array = temp;
        emptyArray();
        delete[] temp;
        throw e;
    }
    remap(temp, array);
    delete[] temp;
}

void playerHashMap::remap(playerStruct *oldArray, playerStruct *newArray) {
    int oldSize = arrayLength/2;
    for (int i= 0; i < oldSize; ++i){
        int currentPlayerId = oldArray[i].node->getPlayerId();
        int indexToPlaceIn = hash(currentPlayerId);
        newArray[indexToPlaceIn].node= oldArray[i].node;
        newArray[indexToPlaceIn].isEmpty =false;
        cout << "!!!!!'" << endl;
    }
}

int playerHashMap::hashFunction1(int playerID, int module) {
    return playerID % module;
}

int playerHashMap::hashFunction2(int playerID, int module) {
    int number = playerID  % (module - 1);
    if (number == 0){
        number = 1;
    }
    return number;
}

int playerHashMap::find(Player *player) const {
    int index = hash(player->getPlayerId());
    if (array[index].isEmpty) {
        return -1;
    }
    return index;
}

int playerHashMap::findUsingId(int playerId) const {
    int index = hash(playerId);
    if (array[index].isEmpty) {
        return -1;
    }
    return index;
}

playerStruct &playerHashMap::operator[](int index) const {
    assert(index < arrayLength);
    return array[index];
}

void playerHashMap::emptyArray() {
    for (int i=0; i < arrayLength; ++i){
        Node* node = array[i].node;
        delete node;
    }
}


