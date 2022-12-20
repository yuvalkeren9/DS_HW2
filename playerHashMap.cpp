//
// Created by יובל קרן on 12/20/2022.
//

#include "playerHashMap.h"
#include <cassert>



void playerHashMap::add(Player* player) {
    int playerId = player->getPlayerId();
    if (find(player) != -1){
        return;  //TODO: maybe return failed?
    }
    int index = hash(playerId);
    if(array[index].isEmpty)  //object isnt already in hash map
    {
        array[index].element = player;
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
    while (array[hashVal].isEmpty != true && array[hashVal].element->getPlayerId() != playerId){
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
        return;   //TODO: something
    }
    remap(temp, array);
    delete[] temp;
}

void playerHashMap::remap(playerStruct *oldArray, playerStruct *newArray) {
    int oldSize = arrayLength/2;
    for (int i= 0; i < oldSize; ++i){
        int currentPlayerId = oldArray[i].element->getPlayerId();
        newArray[hash(currentPlayerId)] = oldArray[i];
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