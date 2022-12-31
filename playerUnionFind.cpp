//
// Created by יובל קרן on 12/22/2022.
//

#include "playerUnionFind.h"
#include <cassert>


Node* playerUnionFind::insertPlayer(Player *player) {
    Team* team = player->getTeam();
    Node* node = new Node(player);
    if(team->getNumOfPlayersInTeam() == 0){
        team->setTeamRepresentative(node);
        node->wasRepresenative = true;
    }
    else{

        //calculating permutation
        Node* teamRepresenative = team->getTeamRepresentative();
        node->parent = teamRepresenative;
        teamRepresenative->sizeOfTree += 1;
        permutation_t smallestOfTheRepresenative = teamRepresenative->smallestNodeSpirit;
        permutation_t rankOfBoughtBeforeUpdate = node->rank;
        node->rank = smallestOfTheRepresenative * node->rank;
        teamRepresenative->smallestNodeSpirit = smallestOfTheRepresenative * rankOfBoughtBeforeUpdate;

        //calculating gamesPlayedRank
        node->gamesPlayedRank = 0 - team->getNumOfGamesPlayed();
    }
    playerArray.add(node);
    return node;
}


Team * playerUnionFind::findTeamRootNode(Player* player) {
    int index = playerArray.find(player);
    assert( index != -1);
    Node* node = playerArray[index].node;
    Node* origNode = node;
    permutation_t allPermutation = permutation_t::neutral();
    long long int allGamesPlayed = 0;
    while (node->parent != nullptr){
        allPermutation = allPermutation*node->rank;
        allGamesPlayed += node->gamesPlayedRank;
        node = node->parent;
    }
    Node* root = node;
    node = origNode;
    if (origNode == root){
        return root->team;
    }
    while (node->parent != root){
        Node* realParent = node->parent;
        node->parent = root;

        //calculating permutation
        permutation_t oldRankInverse = node->rank.inv();
        node->rank = allPermutation;
        allPermutation = oldRankInverse * allPermutation;

        //calculating gamesPlayed
        long long int oldGamesPlayedRank = node->gamesPlayedRank;
        node->gamesPlayedRank = allGamesPlayed;
        allGamesPlayed = allGamesPlayed - oldGamesPlayedRank;


        node = realParent;
    }
    return root->team;
}

void playerUnionFind::playerUnion(Team* team1, Team* team2) {
    Node* team1Root = team1->getTeamRepresentative();
    Node* team2Root = team2->getTeamRepresentative();
//    if(team1Root== nullptr && team2Root != nullptr){//empty team buys nun empty team
//
//        team2Root->team=team1;
//    }
    if(team1Root->sizeOfTree >= team2Root->sizeOfTree){   //team1 is larger
        team1Root->sizeOfTree += team2Root->sizeOfTree;
        team2Root->parent = team1Root;

        //updating permutations
        permutation_t oldSmallerRank = team2Root->rank;
        team2Root->rank =  team1Root->smallestNodeSpirit * team2Root->rank;
        team1Root->smallestNodeSpirit =  team1Root->smallestNodeSpirit * (oldSmallerRank * team2Root->smallestNodeSpirit);

        //updating gamesRank
        team2Root->gamesPlayedRank = team2Root->gamesPlayedRank + team2->getNumOfGamesPlayed() - team1->getNumOfGamesPlayed() - team1Root->gamesPlayedRank;
    }
    else{
        team2Root->sizeOfTree += team1Root->sizeOfTree;
        team1Root->parent = team2Root;
       // team1Root->team = team2Root->team;
        team2Root->team = team1Root->team;

        //updating permutations
        permutation_t oldSmallerRank = team2Root->rank;
        team2Root->rank = team1Root->rank * (team1Root->smallestNodeSpirit * team2Root->rank);
        team1Root->rank = team2Root->rank.inv() * team1Root->rank;   //changed here
        team2Root->smallestNodeSpirit = team2Root->rank * (oldSmallerRank * team1Root->smallestNodeSpirit); //TODO:check this out


        //updating gamesPlayedRank
        team2Root->gamesPlayedRank = team2Root->gamesPlayedRank + team2->getNumOfGamesPlayed() - team1->getNumOfGamesPlayed();
        team1Root->gamesPlayedRank =  team1Root->gamesPlayedRank - team2Root->gamesPlayedRank;

        team1->setTeamRepresentative(team2Root);

    }

}

playerUnionFind::playerUnionFind() : playerArray() {
}

permutation_t playerUnionFind::getPlayerSpiral(Player *player) {
    int index = playerArray.find(player);
    assert( index != -1);
    Node* node = playerArray[index].node;
    permutation_t spiral = permutation_t::neutral();
    while(node != nullptr){
        spiral = node->rank * spiral ;
        node = node->parent;
    }
    //making shortcuts
    findTeamRootNode(player);
    return spiral;
}


int playerUnionFind::getPlayerNumOfGamesPlayed(Player *player) {
    int index = playerArray.find(player);
    assert( index != -1);
    Node* node = playerArray[index].node;
    int gamesPlayed = 0;
    while(node->parent != nullptr){
        gamesPlayed += node->gamesPlayedRank;
        node = node->parent;
    }
    assert(node->wasRepresenative == true);
    gamesPlayed += node->gamesPlayedRank;
    gamesPlayed += node->team->getNumOfGamesPlayed();
    Team* team = node->team;

    //making shortcuts
    findTeamRootNode(player);
    return gamesPlayed;
}

permutation_t playerUnionFind::getPlayerRank(Player *player) {
    int index = playerArray.find(player);
    assert( index != -1);
    Node* node = playerArray[index].node;
    return node->rank;
}

Player* playerUnionFind::findPlayer(int playerId) const {
    int index = playerArray.findUsingId(playerId);
    if (index == -1){
        return nullptr;
    }
    Node* node = playerArray[index].node;
    return node->player;
}

void playerUnionFind::print() {
    for (int i = 0; i < this->playerArray.arrayLength; ++i) {
        //std::cout << "Hello! At index " << i << " we have the player: ";
        if (this->playerArray[i].isEmpty) {
            std::cout << "Empty!" << std::endl;
            continue;
        }
        std::cout << "player " << playerArray[i].node->getPlayerId() << "in team "<< findTeamRootNode(playerArray[i].node->player)->getTeamId()<<endl;

    }
}



