//
// Created by יובל קרן on 12/20/2022.
//

#ifndef DS2_PLAYERHASHMAP_H
#define DS2_PLAYERHASHMAP_H

#include "Player.h"
#include "iostream"

using namespace std;

struct playerStruct{
    bool isEmpty;
    Player* element;
    playerStruct() : isEmpty(true), element(nullptr){};
};

class playerHashMap {
public:
    int numOfPlayers;
    int arrayLength;
    playerStruct* array;
    playerHashMap() : numOfPlayers(0), arrayLength(initialSize), array(nullptr){
        array = new playerStruct[initialSize];
    }
    void add(Player* player);
    int find(Player* player) const;


    //functions for tests
    void printArray(){
        for (int i = 0; i < arrayLength; ++i) {
            std::cout << "Hello! At index " << i << " we have the player: ";
            if (array[i].isEmpty) {
                std::cout << "Empty!" << std::endl;
                continue;
            }
            std::cout << array[i].element->getPlayerId() << std::endl;
        }
    }

private:
    static const int initialSize = 5;
    void expand();
    int hash(int playerId) const;
    void remap(playerStruct* oldArray, playerStruct* newArray);
    static int hashFunction1(int playerID, int module);
    static int hashFunction2(int playerID, int module);
};




#endif //DS2_PLAYERHASHMAP_H
