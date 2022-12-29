//
// Created by יובל קרן on 12/22/2022.
//

#ifndef DS2_PLAYERUNIONFIND_H
#define DS2_PLAYERUNIONFIND_H

#include "wet2util.h"
#include "playerHashMap.h"
#include "Player.h"
#include "Team.h"




class playerUnionFind {
public :
    Node* insertPlayer(Player* player);
    Team * findTeamRootNode(Player* player);
    void playerUnion(Team* team1, Team* team2);
    permutation_t getPlayerSpiral(Player* player);
    Player* findPlayer(int playerId) const;
    int getPlayerNumOfGamesPlayed(Player *player);


    playerUnionFind();
    //functions for testing
    permutation_t getPlayerRank(Player* player);



private:
    playerHashMap playerArray;
};


#endif //DS2_PLAYERUNIONFIND_H
