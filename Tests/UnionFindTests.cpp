//
// Created by יובל קרן on 12/20/2022.
//

#include <iostream>
#include "../playerHashMap.h"
#include "../Player.h"
#include "../wet2util.h"

using namespace std;

int main(){
    permutation_t swagger;
    Player Messi(103,1, swagger, 1, 1, 1, true);
    Player player1(100,1, swagger, 1, 1, 1, true);
    Player player2(2,1, swagger, 1, 1, 1, true);
    Player player3(3,1, swagger, 1, 1, 1, true);
    Player player4(4,1, swagger, 1, 1, 1, true);
    Player player5(14,1, swagger, 1, 1, 1, true);
    Player player6(6,1, swagger, 1, 1, 1, true);
    Player player7(7,1, swagger, 1, 1, 1, true);
    Player player8(8,1, swagger, 1, 1, 1, true);
    Player player9(9,1, swagger, 1, 1, 1, true);
    Player player10(10,1, swagger, 1, 1, 1, true);
    Player player11(11,1, swagger, 1, 1, 1, true);
    Player player12(12,1, swagger, 1, 1, 1, true);
    Player* Messiptr = &Messi;
    Player* ptr1 = &player1;
    Player* ptr2 = &player2;
    Player* ptr3 = &player3;
    Player* ptr4 = &player4;
    Player* ptr5 = &player5;
    Player* ptr6 = &player6;
    Player* ptr7 = &player7;
    Player* ptr8 = &player8;
    Player* ptr9 = &player9;
    Player* ptr10 = &player10;
    Player* ptr11 = &player11;
    Player* ptr12 = &player12;

    playerHashMap hashmap;
    hashmap.add(Messiptr);
    hashmap.add(ptr1);
    hashmap.add(ptr2);
    hashmap.add(ptr3);

    hashmap.printArray();
    cout << endl << endl << endl;

    hashmap.add(ptr4);
    hashmap.printArray();


    hashmap.add(ptr5);
    hashmap.add(ptr6);
    hashmap.add(ptr7);
    hashmap.add(ptr8);
    hashmap.add(ptr9);
    hashmap.add(ptr10);
    hashmap.add(ptr11);
    hashmap.add(ptr12);

}

