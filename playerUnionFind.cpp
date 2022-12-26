//
// Created by יובל קרן on 12/22/2022.
//

#include "playerUnionFind.h"


Node* playerUnionFind::insertPlayer(Player *player) {
    Team* team = player->getTeam();
    Node* node = new Node(player);
    if(team->getNumOfPlayersInTeam() == 0){
        team->setTeamRepresentative(node);
    }
    else{
        Node* teamRepresenative = team->getTeamRepresentative();
        node->parent = teamRepresenative;
        teamRepresenative->sizeOfTree += 1;
        permutation_t smallestOfTheRepresenative = teamRepresenative->smallestNodeSpirit;
        permutation_t rankOfBoughtBeforeUpdate = node->rank;
        node->rank = smallestOfTheRepresenative * node->rank;
        teamRepresenative->smallestNodeSpirit = smallestOfTheRepresenative * rankOfBoughtBeforeUpdate;
    }
    playerArray.add(node);
    return node;
}


Node* playerUnionFind::findTeamRootNode(Player* player) {
    int index = playerArray.find(player);

    //TODO: what to do when -1 returns?

    Node* node = playerArray[index].node;
    Node* origNode = node;
    permutation_t allPermutation = permutation_t::neutral();
    while (node->parent != nullptr){
        allPermutation = allPermutation*node->rank;
        node = node->parent;
    }
    Node* root = node;
    node = origNode;
    while (node->parent != root){
        Node* realParent = node->parent;
        node->parent = root;
        permutation_t oldRankInverse = node->rank.inv();
        node->rank = allPermutation;
        allPermutation = oldRankInverse * allPermutation;
        node = realParent;
    }
    return root;
}

void playerUnionFind::playerUnion(Team* team1, Team* team2) {
    Node* team1Root = team1->getTeamRepresentative();
    Node* team2Root = team2->getTeamRepresentative();
    if(team1Root->sizeOfTree >= team2Root->sizeOfTree){   //team1 is larger
        team1Root->sizeOfTree += team2Root->sizeOfTree;
        team2Root->parent = team1Root;

        permutation_t oldSmallerRank = team2Root->rank;
        team2Root->rank =  team1Root->smallestNodeSpirit * team2Root->rank;
        team1Root->smallestNodeSpirit =  team1Root->smallestNodeSpirit * (oldSmallerRank * team2Root->smallestNodeSpirit);
    }
    else{       team2Root->sizeOfTree += team1Root->sizeOfTree;
        team1Root->parent = team2Root;
        team1Root->team = team2Root->team;

        permutation_t oldSmallerRank = team2Root->rank;
        team2Root->rank = team1Root->rank * (team1Root->smallestNodeSpirit * team2Root->rank);
        team1Root->rank = team1Root->rank * team2Root->rank.inv();
        team2Root->smallestNodeSpirit = team2Root->rank * (oldSmallerRank * team1Root->smallestNodeSpirit);
    }
}

playerUnionFind::playerUnionFind() : playerArray() {
}

permutation_t playerUnionFind::getPlayerSpiral(Player *player) {
    int index = playerArray.find(player);
    //TODO: what to do when -1 returns?
    Node* node = playerArray[index].node;
    //TODO: maybe do shortcut thing?
    permutation_t spiral = permutation_t::neutral();
    while(node != nullptr){
        spiral = node->rank * spiral ;
        node = node->parent;
    }
    return spiral;
}

permutation_t playerUnionFind::getPlayerRank(Player *player) {
    int index = playerArray.find(player);

    //TODO: what to do when -1 returns?

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


