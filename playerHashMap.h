//
// Created by יובל קרן on 12/20/2022.
//

#ifndef DS2_PLAYERHASHMAP_H
#define DS2_PLAYERHASHMAP_H

#include "Player.h"
#include "iostream"

using namespace std;

struct Node{            //circle
    int id;
    Player* player;
    Team* team;
    permutation_t rank;
    Node* parent;
    int sizeOfTree;
    permutation_t smallestNodeSpirit;
    bool wasRepresenative;
    int gamesPlayedRank;

    Node(Player* player);
    Player* getPlayer() const;
    int getPlayerId() const;
    Team* getTeam() const;
};


struct playerStruct{          //square
    bool isEmpty;
    Node* node;
    playerStruct() : isEmpty(true), node(nullptr){};
};



class playerHashMap {
public:
    int numOfPlayers;
    int arrayLength;
    playerStruct* array;
    playerHashMap() : numOfPlayers(0), arrayLength(initialSize), array(nullptr){
        array = new playerStruct[initialSize];
    }
    ~playerHashMap() {
        emptyArray();
        delete[] array;
    }
    void add(Node* node);
    int find(Player* player) const;
    int findUsingId(int playerId) const;
    playerStruct& operator[](int index) const;


    //functions for tests
//    void printArray(){
//        for (int i = 0; i < arrayLength; ++i) {
//            //std::cout << "Hello! At index " << i << " we have the player: ";
//            if (array[i].isEmpty) {
//                std::cout << "Empty!" << std::endl;
//                continue;
//            }
//
//            std::cout <<"player "<< array[i].node->getPlayerId() << "in team " << array[i].node->getTeam()->getTeamId()<< std::endl;
//        }
//    }

private:
    static const int initialSize = 7;  //2^3 - 1 = 7, third mersenne number
    void expand();
    int hash(int playerId) const;
    void remap(playerStruct* oldArray, playerStruct* newArray);
    void emptyArray();
    static int hashFunction1(int playerID, int module);
    static int hashFunction2(int playerID, int module);
};




#endif //DS2_PLAYERHASHMAP_H
