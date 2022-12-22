//
// Created by יובל קרן on 12/20/2022.
//

#include <iostream>
#include "../playerHashMap.h"
#include "../Player.h"
#include "../wet2util.h"
#include "../playerUnionFind.h"

using namespace std;

void print_permutation(permutation_t permuta){

}




int main(){
    Team team1(1);
    Team team2(2);
    Team team3(3);


    Team* teamPtr1 = &team1;
    Team* teamPtr2 = &team2;
    Team* teamPtr3 = &team3;


    int permut1[5] = {1,0,2,3,4};
    int permut2[5] = {0,1,2,4,3};
    int permut3[5] = {0,1,3,4,2};   //(2,3,4)
    int permut4[5] = {5,2,3,4,1};  //(1,5)
    int permut5[5] = {1,3,2,4,5};   //(2,3)

    playerUnionFind unionFind;





    Player player1(5,1, permut1, 1, 1, 1, true);
    Player player2(2,1, permut2, 1, 1, 1, true);
    Player player3(3,1, permut3, 1, 1, 1, true);
//    Player player4(4,1, swagger, 1, 1, 1, true);
//    Player player5(14,1, swagger, 1, 1, 1, true);
//    Player player6(6,1, swagger, 1, 1, 1, true);
//    Player player7(7,1, swagger, 1, 1, 1, true);
//    Player player8(8,1, swagger, 1, 1, 1, true);
//    Player player9(9,1, swagger, 1, 1, 1, true);
//    Player player10(10,1, swagger, 1, 1, 1, true);
//    Player player11(11,1, swagger, 1, 1, 1, true);
//    Player player12(12,1, swagger, 1, 1, 1, true);
    Player* ptr1 = &player1;
    Player* ptr2 = &player2;
    Player* ptr3 = &player3;
//    Player* ptr4 = &player4;
//    Player* ptr5 = &player5;
//    Player* ptr6 = &player6;
//    Player* ptr7 = &player7;
//    Player* ptr8 = &player8;
//    Player* ptr9 = &player9;
//    Player* ptr10 = &player10;
//    Player* ptr11 = &player11;
//    Player* ptr12 = &player12;

    player1.setTeam(teamPtr1);
    player2.setTeam(teamPtr2);
    player3.setTeam(teamPtr3);

    team1.setTeamRepresentative(unionFind.insertPlayer(ptr1));
    team2.setTeamRepresentative(unionFind.insertPlayer(ptr2));
    team3.setTeamRepresentative(unionFind.insertPlayer(ptr3));


    unionFind.playerUnion(teamPtr1, teamPtr2);

    unionFind.getPlayerRank(ptr1).print();
    unionFind.getPlayerRank(ptr2).print();
    cout <<endl;
    unionFind.getPlayerSpiral(ptr1).print();
    unionFind.getPlayerSpiral(ptr2).print();

    cout << "End of first union. Will now begin" << endl;

    unionFind.playerUnion(teamPtr3,teamPtr1);

    unionFind.getPlayerRank(ptr1).print();
    unionFind.getPlayerRank(ptr2).print();
    unionFind.getPlayerRank(ptr3).print();
    cout << endl;
    unionFind.getPlayerSpiral(ptr1).print();
    unionFind.getPlayerSpiral(ptr2).print();
    unionFind.getPlayerSpiral(ptr3).print();




//    unionFind.insertPlayer(ptr2);
    if(true)


    return 0;
}





