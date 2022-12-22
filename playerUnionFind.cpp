//
// Created by יובל קרן on 12/22/2022.
//

#include "playerUnionFind.h"


Node* playerUnionFind::insertPlayer(Player *player) {
    Node* node = new Node(player);
    playerArray.add(node);
    return node;
}

Node* playerUnionFind::findTeamRootNode(Player* player) {
    int index = playerArray.find(player);
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
        team2Root->rank = team2Root->rank * team1Root->smallestNodeSpirit;
        permutation_t fuckYouSegelMatam = (oldSmallerRank * team2Root->smallestNodeSpirit);
        team1Root->smallestNodeSpirit =  team1Root->smallestNodeSpirit * fuckYouSegelMatam;
    }
    else{
        team2Root->sizeOfTree += team1Root->sizeOfTree;
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
    Node* node = playerArray[index].node;
    permutation_t spiral = permutation_t::neutral();
    while(node != nullptr){
        spiral = node->rank * spiral ;
        node = node->parent;
    }
    return spiral;
}

permutation_t playerUnionFind::getPlayerRank(Player *player) {
    int index = playerArray.find(player);
    Node* node = playerArray[index].node;
    return node->rank;
}


