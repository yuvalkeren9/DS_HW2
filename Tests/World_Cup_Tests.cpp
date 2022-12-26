//
// Created by יובל קרן on 12/24/2022.
//

#include "../worldcup23a2.h"
#include <iostream>


bool getPartialTest1(){
    world_cup_t worldCup;

    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);

    int permut1[5] = {1,0,2,3,4};   //(0,1)  a
    int permut2[5] = {0,1,3,4,2};   //(3,4)   b
    int permut3[5] = {4,2,3,1,0};   //(0,4)(1,2,3)  c
    int permut4[5] = {2,0,1,3,4};   //(0,1,2)  d
    int permut5[5] = {2,3,0,1,4};   //(0,2)(1,3)  e

    worldCup.add_player(1,1,permut1,0,0,0,true);  //a
    worldCup.add_player(2,2,permut2,0,0,0,true);  //b
    worldCup.add_player(3,1,permut3,0,0,0,true);  //c
    worldCup.add_player(4,3,permut4,0,0,0,true); //d

    worldCup.buy_team(3,2);
    worldCup.add_player(5,3,permut5,0,0,0,true); //e
    worldCup.buy_team(3,1);


    output_t<permutation_t> p1 = worldCup.get_partial_spirit(1);
    output_t<permutation_t> p2 = worldCup.get_partial_spirit(2);
    output_t<permutation_t> p3 = worldCup.get_partial_spirit(3);
    output_t<permutation_t> p4 = worldCup.get_partial_spirit(4);
    output_t<permutation_t> p5 = worldCup.get_partial_spirit(5);

    cout << "First player permut is:"; p1.ans().print(); cout <<endl;
    cout << "second player permut is:"; p2.ans().print(); cout <<endl;
    cout << "third player permut is:"; p3.ans().print(); cout <<endl;
    cout << "fourth player permut is:"; p4.ans().print(); cout <<endl;
    cout << "fifth player permut is:"; p5.ans().print(); cout <<endl;



    return true;
}


bool getRankOfTeamInTree(){
    AVL_Tree<Team> tree;
    tree.insert(new Team(5));

    tree.insert(new Team(1));
    tree.insert(new Team(2));
    tree.insert(new Team(4));
    tree.insert(new Team(7));
    tree.insert(new Team(8));
    tree.insert(new Team(6));
    tree.insert(new Team(10));
    tree.insert(new Team(9));
    tree.insert(new Team(3));
    Team* team = tree.select(9);
    if(true){
        return true;
    }
    return true;
}






int main(){

    getRankOfTeamInTree();
    getPartialTest1();



    world_cup_t worldCup;

    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);

    int permut1[5] = {1,0,2,3,4};   //(0,1)
    int permut2[5] = {0,1,2,4,3};   //(3,4)
    int permut3[5] = {0,1,3,4,2};   //(3,2,4)

    worldCup.add_player(1, 1, permut1 ,0, 0, 0, true);
    worldCup.add_player(2, 2, permut2 ,0, 0, 0, true);
    worldCup.add_player(3, 3, permut3 ,0, 0, 0, true);


    worldCup.buy_team(1,2);
    worldCup.buy_team(1,3);

    output_t<permutation_t> p1 = worldCup.get_partial_spirit(1);
    output_t<permutation_t> p2 = worldCup.get_partial_spirit(2);
    output_t<permutation_t> p3 = worldCup.get_partial_spirit(3);

    cout << "First player permut is:"; p1.ans().print(); cout <<endl;
    cout << "second player permut is:"; p2.ans().print(); cout <<endl;
    cout << "third player permut is:"; p3.ans().print(); cout <<endl;





}

