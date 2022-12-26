//
// Created by יובל קרן on 12/24/2022.
//

#include "../worldcup23a2.h"
#include <iostream>
#include <functional>

using namespace std;

bool run_test(const std::function<bool()>& test, const std::string& test_name )
{
    if(!test()){
        std::cout<< test_name <<" FAILED."<<std::endl;
        std::cout << std::endl;
        return false;
    }
    std::cout<<test_name<<" SUCCEEDED."<<std::endl;
    std::cout << std::endl;
    return true;

}


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


bool getNumOfPlayedGamesTest1(){

    world_cup_t worldCup;

    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    worldCup.add_team(4);
    worldCup.add_team(5);


    int permut1[5] = {1,0,2,3,4};   //(0,1)  a
    int permut2[5] = {0,1,3,4,2};   //(3,4)   b
    int permut3[5] = {4,2,3,1,0};   //(0,4)(1,2,3)  c
    int permut4[5] = {2,0,1,3,4};   //(0,1,2)  d
    int permut5[5] = {2,3,0,1,4};   //(0,2)(1,3)  e



    worldCup.add_player(1,1,permut1,0,0,0,true);
    worldCup.add_player(2,1,permut1,0,0,0,true);
    worldCup.add_player(3,1,permut1,0,0,0,true);
    worldCup.add_player(4,1,permut1,0,0,0,true);
    worldCup.add_player(5,1,permut1,0,0,0,true);

    worldCup.add_player(21,2,permut1,0,0,0,true);
    worldCup.add_player(22,2,permut1,0,0,0,true);
    worldCup.add_player(23,2,permut1,0,0,0,true);

    worldCup.play_match(1,2);
    worldCup.play_match(1,2);

    worldCup.add_player(6,1,permut1,0,0,0,true);
    worldCup.add_player(7,1,permut1,0,0,0,true);
    worldCup.add_player(8,1,permut1,0,0,0,true);

    worldCup.play_match(1,2);
    worldCup.play_match(1,2);

    worldCup.add_player(26,2,permut1,0,0,0,true);
    worldCup.add_player(24,2,permut1,0,0,0,true);
    worldCup.add_player(25,2,permut1,0,0,0,true);

    worldCup.buy_team(1,2);

    worldCup.play_match(1,3);
    worldCup.add_player(300,1,permut1,0,0,0,true);


    output_t<int> r1 = worldCup.num_played_games_for_player(1);
    output_t<int> r2 = worldCup.num_played_games_for_player(2);
    output_t<int> r3 = worldCup.num_played_games_for_player(3);
    output_t<int> r4 = worldCup.num_played_games_for_player(4);
    output_t<int> r5 = worldCup.num_played_games_for_player(5);
    output_t<int> r6 = worldCup.num_played_games_for_player(6);
    output_t<int> r7 = worldCup.num_played_games_for_player(7);
    output_t<int> r8 = worldCup.num_played_games_for_player(8);

    output_t<int> r21 = worldCup.num_played_games_for_player(21);
    output_t<int> r22 = worldCup.num_played_games_for_player(22);
    output_t<int> r23 = worldCup.num_played_games_for_player(23);
    output_t<int> r24 = worldCup.num_played_games_for_player(24);
    output_t<int> r25 = worldCup.num_played_games_for_player(25);
    output_t<int> r26 = worldCup.num_played_games_for_player(26);

    output_t<int> r300 = worldCup.num_played_games_for_player(300);


    if (r1.ans() == 5 &&  r2.ans() == 5 && r3.ans() == 5 && r4.ans() == 5 && r5.ans() == 5 && r6.ans() == 3 && r7.ans() == 3 &&
            r8.ans() == 3 && r21.ans() == 5 && r22.ans() == 5 && r23.ans() == 5 && r24.ans() == 1 && r25.ans() == 1 && r26.ans() == 1 &&
            r300.ans() == 0){
        return true;
    }
    return false;


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

    tree.Delete(new Team(1));
    tree.Delete(new Team(6));

    tree.insert(new Team(12));
    tree.insert(new Team(91));
    tree.insert(new Team(31));

    tree.Delete(new Team(10));
    tree.Delete(new Team(3));
    tree.Delete(new Team(31));




    Team* team = tree.select(2+1);
    if(true){
        return true;
    }
    return true;
}






int main(){
    if(!run_test(getNumOfPlayedGamesTest1, "getNumOfPlayedGamesTest1"))
        return 1;
    return 0;

//    getNumOfPlayedGamesTest1();
//    getRankOfTeamInTree();
//    getPartialTest1();
//
//
//
//    world_cup_t worldCup;
//
//    worldCup.add_team(1);
//    worldCup.add_team(2);
//    worldCup.add_team(3);
//
//    int permut1[5] = {1,0,2,3,4};   //(0,1)
//    int permut2[5] = {0,1,2,4,3};   //(3,4)
//    int permut3[5] = {0,1,3,4,2};   //(3,2,4)
//
//    worldCup.add_player(1, 1, permut1 ,0, 0, 0, true);
//    worldCup.add_player(2, 2, permut2 ,0, 0, 0, true);
//    worldCup.add_player(3, 3, permut3 ,0, 0, 0, true);
//
//
//    worldCup.buy_team(1,2);
//    worldCup.buy_team(1,3);
//
//    output_t<permutation_t> p1 = worldCup.get_partial_spirit(1);
//    output_t<permutation_t> p2 = worldCup.get_partial_spirit(2);
//    output_t<permutation_t> p3 = worldCup.get_partial_spirit(3);
//
//    cout << "First player permut is:"; p1.ans().print(); cout <<endl;
//    cout << "second player permut is:"; p2.ans().print(); cout <<endl;
//    cout << "third player permut is:"; p3.ans().print(); cout <<endl;
//
//
//


}

