//
// Created by יובל קרן on 12/24/2022.
//

#include "../worldcup23a2.h"
#include <iostream>
#include <functional>
#include <random>

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
    int permut2[5] = {0,1,3,4,2};   //(2,3,4)   b
    int permut3[5] = {4,2,3,1,0};   //(0,4)(1,2,3)  c
    int permut4[5] = {2,0,1,3,4};   //(0,2,1)  d
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

//    cout << "A player permut is:"; p1.ans().print(); cout <<endl;
//    cout << "B player permut is:"; p2.ans().print(); cout <<endl;
//    cout << "C player permut is:"; p3.ans().print(); cout <<endl;
//    cout << "D player permut is:"; p4.ans().print(); cout <<endl;
//    cout << "E player permut is:"; p5.ans().print(); cout <<endl;



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

    worldCup.add_player(500,3,permut1,0,0,0,true);
    worldCup.play_match(1,3);


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
    output_t<int> r500 = worldCup.num_played_games_for_player(500);



    if (r1.ans() == 5 &&  r2.ans() == 5 && r3.ans() == 5 && r4.ans() == 5 && r5.ans() == 5 && r6.ans() == 3 && r7.ans() == 3 &&
            r8.ans() == 3 && r21.ans() == 5 && r22.ans() == 5 && r23.ans() == 5 && r24.ans() == 1 && r25.ans() == 1 && r26.ans() == 1 &&
            r300.ans() == 1 && r500.ans() == 1){
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




bool addTeamTest1(){
    world_cup_t worldCup;
    StatusType status12 = worldCup.add_team(0);
    StatusType status1 = worldCup.add_team(5);
    StatusType status2 = worldCup.add_team(6);
    StatusType status10 = worldCup.add_team(-3);
    StatusType status3 = worldCup.add_team(54);
    StatusType status102 = worldCup.add_team(54);
    StatusType status101 = worldCup.add_team(5);
    StatusType status4 = worldCup.add_team(52);
    StatusType status11 = worldCup.add_team(-7);
    StatusType status5 = worldCup.add_team(580);
    StatusType status6 = worldCup.add_team(253);
    StatusType status7 = worldCup.add_team(3);
    StatusType status100 = worldCup.add_team(3);
    if (status1 == StatusType::SUCCESS && status2 == StatusType::SUCCESS && status3 == StatusType::SUCCESS &&
        status4 == StatusType::SUCCESS && status5 == StatusType::SUCCESS && status6 == StatusType::SUCCESS &&
        status7 == StatusType::SUCCESS && status10 == StatusType::INVALID_INPUT && status11 == StatusType::INVALID_INPUT &&
        status12 == StatusType::INVALID_INPUT && status100 == StatusType::FAILURE && status101 == StatusType::FAILURE &&
        status102 == StatusType::FAILURE) {
        return true;
    }
    return false;
};

bool removeTeamTest1(){

    world_cup_t worldCup;
    StatusType status1 = worldCup.remove_team(1);
    StatusType status2 = worldCup.remove_team(2);
    StatusType status3 = worldCup.remove_team(-1);
    StatusType status4 = worldCup.remove_team(0);

    if (status1 != StatusType::FAILURE || status2 != StatusType::FAILURE || status3 != StatusType::INVALID_INPUT || status4 != StatusType::INVALID_INPUT){
        return false;
    }

    worldCup.add_team(1);
    worldCup.add_team(500);
    worldCup.add_team(50);
    worldCup.add_team(5000);

    StatusType status11 = worldCup.remove_team(1);
    StatusType status12 = worldCup.remove_team(1);
    StatusType status13 = worldCup.remove_team(-1);
    StatusType status14 = worldCup.remove_team(50);

    if (status11 != StatusType::SUCCESS || status12 != StatusType::FAILURE || status13 != StatusType::INVALID_INPUT || status14 != StatusType::SUCCESS){
        return false;
    }

    worldCup.add_team(1997);
    worldCup.remove_team(1997);
    worldCup.add_team(1997);
    worldCup.remove_team(1997);
    worldCup.add_team(1997);
    worldCup.remove_team(1997);
    worldCup.add_team(1997);
    StatusType status1997 = worldCup.remove_team(1997);
    if (status1997 != StatusType::SUCCESS){
        return false;
    }

    return true;
}

bool addPlayerTest1(){
    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);

    int permut1[5] = {1,0,2,3,4};
    int permut2[5] = {0,1,3,4,2};
    int permut3[5] = {4,2,3,1,0};
    int permut4[5] = {2,0,1,3,4};
    int badPermut[5] = {2,3,0,1,69};

    StatusType status1 = worldCup.add_player(1,1,permut1,0,0,0,true);
    StatusType status2 = worldCup.add_player(1,1,permut1,0,0,0,true);
    StatusType status3 = worldCup.add_player(2,5,permut1,0,0,0,true);
    StatusType status4 = worldCup.add_player(2,2,permut1,0,0,0,true);

    if (status1 != StatusType::SUCCESS || status2 != StatusType::FAILURE || status3 != StatusType::FAILURE || status4 != StatusType::SUCCESS){
        return false;
    }

    StatusType status5 = worldCup.add_player(10,1,badPermut,0,0,0,true);
    StatusType status6 = worldCup.add_player(10,-1,permut1,0,0,0,true);
    StatusType status7 = worldCup.add_player(-89,3,permut1,0,0,0,true);
    StatusType status8 = worldCup.add_player(0,2,permut1,0,0,0,true);
    StatusType status9 = worldCup.add_player(10,3,permut1,-1,0,0,true);
    StatusType status10 = worldCup.add_player(75,2,permut1,0,-1,0,true);
    StatusType status11 = worldCup.add_player(10,2,permut1,0,0,-1,true);

    if (status5 != StatusType::INVALID_INPUT || status6 != StatusType::INVALID_INPUT || status7 != StatusType::INVALID_INPUT ||
            status8 != StatusType::INVALID_INPUT || status9 != StatusType::INVALID_INPUT || status10 != StatusType::SUCCESS ||
            status11 != StatusType::INVALID_INPUT){
        return false;
    }

    worldCup.remove_team(1);
    StatusType status100 = worldCup.add_player(1,2,permut1,0,0,0,true);
    StatusType status200 = worldCup.add_player(1997,1,permut1,0,0,0,true);

    worldCup.add_team(1);
    StatusType status300 = worldCup.add_player(1,2,permut1,0,0,0,true);
    StatusType status400 = worldCup.add_player(1997,1,permut1,0,0,0,true);

    if (status100 != StatusType::FAILURE || status200 != StatusType::FAILURE || status300 != StatusType::FAILURE || status400 != StatusType::SUCCESS){
        return false;
    }
    return true;
}


bool playMatchTest1(){
    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    worldCup.add_team(4);
    worldCup.add_team(5);
    worldCup.add_team(6);
    worldCup.add_team(7);

    int permut1[5] = {1,0,2,3,4};

    worldCup.add_player(1,1,permut1,0,1,1,true);
    worldCup.add_player(2,2,permut1,0,2,1,true);
    worldCup.add_player(3,3,permut1,0,3,1,true);
    worldCup.add_player(4,4,permut1,0,4,1,true);
    worldCup.add_player(5,5,permut1,0,5,1,false);

    output_t<int> result1 = worldCup.play_match(1,2);
    output_t<int> result2 = worldCup.play_match(-1,2);
    output_t<int> result3 = worldCup.play_match(1,-2);
    output_t<int> result4 = worldCup.play_match(1,1);
    output_t<int> result5 = worldCup.play_match(0,2);

    if (result1.status() != StatusType::SUCCESS || result2.status() != StatusType::INVALID_INPUT || result3.status() != StatusType::INVALID_INPUT ||
            result4.status() != StatusType::INVALID_INPUT || result5.status() != StatusType::INVALID_INPUT){
        return false;
    }

    output_t<int> result6 = worldCup.play_match(1,5);
    output_t<int> result7 = worldCup.play_match(5,2);
    output_t<int> result8 = worldCup.play_match(1,1997);
    output_t<int> result9 = worldCup.play_match(1997,1);
    if (result6.status() != StatusType::FAILURE || result7.status() != StatusType::FAILURE || result8.status() != StatusType::FAILURE ||
        result9.status() != StatusType::FAILURE){
        return false;
    }

    output_t<int> result10 = worldCup.play_match(1,2);
    worldCup.add_player(1997,5,permut1,0,0,0,true);
    output_t<int> result12 = worldCup.play_match(1,5);
    output_t<int> result13 = worldCup.play_match(4,3);

    if (result10.status() != StatusType::SUCCESS || result12.status() != StatusType::SUCCESS || result13.status() != StatusType::SUCCESS){
        return false;
    }

    return true;
}

bool playMatchTest2(){

    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    worldCup.add_team(4);
    worldCup.add_team(5);
    worldCup.add_team(6);
    worldCup.add_team(7);

    int permut1[5] = {1,0,2,3,4};
    int permut2[5] = {0,1,3,4,2};
    int permut3[5] = {4,2,3,1,0};
    int permut4[5] = {2,0,1,3,4};

    permutation_t spirit1(permut1); //54
    permutation_t spirit2(permut2); //52
    permutation_t spirit3(permut3); //36
    permutation_t spirit4(permut4); //52

//    cout << "sprit 1 strength is " << spirit1.strength() << endl;
//    cout << "sprit 2 strength is " << spirit2.strength() << endl;
//    cout << "sprit 3 strength is " << spirit3.strength() << endl;
//    cout << "sprit 4 strength is " << spirit4.strength() << endl;


    worldCup.add_player(1,1,permut1,0,1,1,true);
    worldCup.add_player(2,2,permut2,0,2,1,true);
    output_t<int> result1 = worldCup.play_match(1,2);  //2 wins ,3 returned
    output_t<int> result2 = worldCup.play_match(2,1);  //2 wins, 1 returned

    worldCup.add_player(4,4,permut4,0,4,1,true);
    worldCup.add_player(5,5,permut2,0,4,1,true);
    output_t<int> result3 = worldCup.play_match(4,5);  //tie, 0 returned

    worldCup.add_player(3,3,permut3,0,5,1,true);
    output_t<int> result4 = worldCup.play_match(3,4); //4 wins by spirit, 4 returned
    output_t<int> result5 = worldCup.play_match(4,3); //4 wins regular, 1 returned

    worldCup.add_team(10);
    worldCup.add_team(20);
    worldCup.add_player(10,10, permut1, 0, 10, 0, true);
    worldCup.add_player(20,20, permut2, 0, 10, 0, true);
    output_t<int> result6 = worldCup.play_match(10,20); //10 wins by spirit, 2 returned



    if (result6.ans() != 2 || result1.ans() != 3 || result2.ans() != 1 || result3.ans() != 0  || result4.ans() != 4 ||
        result5.ans() != 1){
        return false;
    }

    return true;

}

bool playMatchTest3(){

    world_cup_t worldCup;

    for(int i =0; i<= 20; ++i){
        worldCup.add_team(i);
    }
    int permut1[5] = {1,0,2,3,4};
    int permut2[5] = {0,1,3,4,2};
    int permut3[5] = {4,2,3,1,0};
    int permut4[5] = {2,0,1,3,4};


    permutation_t spirit1(permut1); //54
    permutation_t spirit2(permut2); //52
    permutation_t spirit3(permut3); //36
    permutation_t spirit4(permut4); //52

    for (int i= 1; i <=20; ++i){
        worldCup.add_player(i,i,permut1,0,i,0,true);
    }

    for(int i = 1; i <= 19; i+=2){
        worldCup.play_match(i,i+1);
    }
    for (int i=1; i <=19; i+=2){
        if(worldCup.get_team_points(i).ans() != 0){
            return false;
        }
        if(worldCup.get_team_points(i+1).ans() != 3){
            return false;
        }
    }

    worldCup.remove_team(5);
    worldCup.remove_team(10);
    output_t<int> result1 = worldCup.play_match(1,5);
    output_t<int> result2 = worldCup.play_match(10,2);
    if(result1.status() != StatusType::FAILURE || result2.status() != StatusType::FAILURE ){
        return false;
    }

    worldCup.buy_team(1,20);
    output_t<int> result3 = worldCup.play_match(1,6); //1 wins

    worldCup.buy_team(2,3);
    worldCup.buy_team(2,19);
    worldCup.buy_team(2,18);
    output_t<int> result4 = worldCup.play_match(1,2); //2 wins

    if (result3.ans() != 1 || result4.ans() != 3){
        return false;
    }


    return true;
}

bool num_played_games_for_player_TEST2() {
    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    worldCup.add_team(4);
    worldCup.add_team(5);
    worldCup.add_team(6);
    worldCup.add_team(7);

    int permut1[5] = {1, 0, 2, 3, 4};
    int permut2[5] = {0, 1, 3, 4, 2};
    int permut3[5] = {4, 2, 3, 1, 0};
    int permut4[5] = {2, 0, 1, 3, 4};

    permutation_t spirit1(permut1); //54
    permutation_t spirit2(permut2); //52
    permutation_t spirit3(permut3); //36
    permutation_t spirit4(permut4); //52


    worldCup.add_player(1, 1, permut1, 10, 1, 1, true);
    worldCup.add_player(2, 2, permut2, 20, 2, 1, true);
    //  player 1 - 10 games
    //  player 2 - 20 games
    //  player 3 - 0 games
    //  player 4 - 0 games


    output_t<int> result1 = worldCup.play_match(1, 2);  //player 1 - 11 games , player 2 - 21 games , player 3 - 0 games , player4 - 0 games
    output_t<int> result2 = worldCup.play_match(2, 1);  // player 1 - 12 games , player 2 - 22 games,  player 3 - 0 games , player4 - 0 games
    //  player 1 - 12 games
    //  player 2 - 22 games
    //  player 3 - 0 games
    //  player 4 - 0 games

    worldCup.add_player(3, 3, permut1, 10, 1, 1, true);
    //  player 1 - 12 games ,
    //  player 2 - 22 games
    //  player3 - 10 games
    //  player4 - 0 games

    worldCup.play_match(1,3);
    //  player 1 - 13 games
    //  player 2 - 22 games
    //  player3 - 11 games
    //  player4 - 0 games

    worldCup.add_player(4, 4, permut2, 20, 2, 1, true);
    //  player 1 - 13 games
    //  player 2 - 22 games
    //  player3 - 11 games
    //  player4 - 20 games

    worldCup.buy_team(3,1);
    //  player 1 - 13 games
    //  player 2 - 22 games
    //  player3 - 11 games
    //  player4 - 20 games

    worldCup.play_match(3,2);
    //  player 1 - 14 games
    //  player 2 - 23 games
    //  player3 - 12 games
    //  player4 - 20 games




    int  gamesOffPlayer1 = worldCup.num_played_games_for_player(1).ans();   //  player 1 - 14 games
    int gamesOffPlayer2 = worldCup.num_played_games_for_player(2).ans();    //  player 2 - 23 games
    int gamesOffPlayer3 = worldCup.num_played_games_for_player(3).ans();    //  player3 - 12 games
    int  gamesOffPlayer4 = worldCup.num_played_games_for_player(4).ans();   //  player4 - 20 games


    if (gamesOffPlayer1 != 14 || gamesOffPlayer2 != 23 || gamesOffPlayer3 != 12 ||
        gamesOffPlayer4!= 20) {
        return false;
    }
    return true;
}
bool num_played_games_for_player_TEST3() {
    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    worldCup.add_team(4);
    worldCup.add_team(5);
    worldCup.add_team(6);
    worldCup.add_team(7);

    output_t<int> result1 =  worldCup.buy_team(1,2);// expected success (empty team buys empty team)
    output_t<int> result2 =  worldCup.play_match(1,2); // expected failure

    int permut1[5] = {1, 0, 2, 3, 4};
    int permut2[5] = {0, 1, 3, 4, 2};
    int permut3[5] = {4, 2, 3, 1, 0};
    int permut4[5] = {2, 0, 1, 3, 4};
    int permut5[5] = {2, 0, 1, 3, 4};

    permutation_t spirit1(permut1); //54
    permutation_t spirit2(permut2); //52
    permutation_t spirit3(permut3); //36
    permutation_t spirit4(permut4); //52
    permutation_t spirit5(permut5); //52


    output_t<int> result3 = worldCup.add_player(1, 1, permut1, 10, 1, 1, true);// expected success
    output_t<int> result4 = worldCup.add_player(2, 2, permut2, 20, 2, 1, true);// expected failure

    //  player 1 - 10 games

    output_t<int> result5 = worldCup.add_player(2, 2, permut1, 10, 1, 1, true);// expected  failure
    worldCup.add_player(2, 3, permut1, 10, 1, 1, true);
    worldCup.add_player(3, 3, permut1, 10, 1, 1, true);

    //  player 1 - 10 games (team1)
    //  player 2 - 10 games (team3)
    //  player 3 - 10 games (team3)

    worldCup.play_match(3, 1);
    //  player 1 - 11 games (team1)
    //  player 2 - 11 games (team3)
    //  player 3 - 11 games (team3)

    worldCup.add_player(4, 3, permut1, 10, 1, 1, true);
    //  player 1 - 11 games (team1)
    //  player 2 - 11 games (team3)
    //  player3 - 11 games (team3)
    //  player4 - 10 games (team3)

    worldCup.play_match(1,3);
    //  player 1 - 12 games (team1)
    //  player 2 - 12 games (team3)
    //  player3 - 12 games (team3)
    //  player4 - 11 games (team3)

    output_t<int> result6 = worldCup.buy_team(4,3); // expected success (empty team buys nun empty team)
    //  player 1 - 12 games (team1)
    //  player 2 - 12 games (team4)
    //  player3 - 12 games (team4)
    //  player4 - 11 games (team4)

    worldCup.play_match(4,1);
    //  player 1 - 13 games (team1)
    //  player 2 - 13 games (team4)
    //  player3 - 13 games (team4)
    //  player4 - 12 games (team4)
    worldCup.buy_team(1,4);
    //  player 1 - 13 games (team1)
    //  player 2 - 13 games (team1)
    //  player3 - 13 games (team1)
    //  player4 - 12 games (team1)

    worldCup.buy_team(4,5);
    output_t<int> result7 =  worldCup.add_player(5, 4, permut5, 10, 1, 1, true);// expected  failure
    worldCup.add_player(5, 1, permut5, 10, 1, 1, true);
    //  player 1 - 13 games (team1)
    //  player 2 - 13 games (team1)
    //  player3 - 13 games (team1)
    //  player4 - 12 games (team1)
    //  player5 - 10 games (team1)

    //worldCup.printAllPlayers();
    int  gamesOffPlayer1 = worldCup.num_played_games_for_player(1).ans();   //  player 1 - 13 games
    int gamesOffPlayer2 = worldCup.num_played_games_for_player(2).ans();    //  player 2 - 13 games
    int gamesOffPlayer3 = worldCup.num_played_games_for_player(3).ans();    //  player3 - 13 games
    int  gamesOffPlayer4 = worldCup.num_played_games_for_player(4).ans();   //  player4 - 12 games
    int  gamesOffPlayer5 = worldCup.num_played_games_for_player(5).ans();   //  player5 - 10 games

    if (gamesOffPlayer1 != 13 || gamesOffPlayer2 != 13 || gamesOffPlayer3 != 13 || gamesOffPlayer4 != 12 ||
            gamesOffPlayer5!= 10
            || result1.status() !=  StatusType::SUCCESS ||
            result2.status() !=  StatusType::FAILURE || result3.status() !=  StatusType::SUCCESS ||  result4.status() !=  StatusType::FAILURE
            ||  result5.status() !=  StatusType::FAILURE || result6.status() !=  StatusType::SUCCESS ||  result7.status() !=  StatusType::FAILURE)
    {
        return false;
    }
    return true;
}
bool buy_team_TEST1() {
    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    worldCup.add_team(4);
    worldCup.add_team(5);
    worldCup.add_team(6);
    worldCup.add_team(7);

    output_t<int> result1 =  worldCup.buy_team(1,2);// expected success (empty team buys empty team)

    int permut1[5] = {1, 0, 2, 3, 4};
    int permut2[5] = {0, 1, 3, 4, 2};
    int permut3[5] = {4, 2, 3, 1, 0};
    int permut4[5] = {2, 0, 1, 3, 4};
    int permut5[5] = {2, 0, 1, 3, 4};

    permutation_t spirit1(permut1); //54
    permutation_t spirit2(permut2); //52
    permutation_t spirit3(permut3); //36
    permutation_t spirit4(permut4); //52
    permutation_t spirit5(permut5); //52


    worldCup.add_player(1, 1, permut1, 10, 1, 1, true);
    worldCup.add_player(2, 1, permut2, 20, 2, 1, true);
    output_t<int> result2 =  worldCup.buy_team(1,2);// expected  failure (tries to buy team that was bought already)
    output_t<int> result3 =  worldCup.buy_team(2,1);// expected  failure (team that was already bought tries to buy a team)
    output_t<int> result4 =  worldCup.buy_team(3,1);// expected  success (empty team buys nun empty team)
    output_t<int> result5 =  worldCup.buy_team(3,5);// expected  success (nun empty team buys an empty team)
    output_t<int> result6 = worldCup.add_player(3, 4, permut1, 10, 1, 1, true);// expected  success
    output_t<int> result7 =  worldCup.buy_team(3,4);// expected  success (nun empty buys nun empty)
   // worldCup.printAllPlayers();

    if (result1.status() !=  StatusType::SUCCESS ||
        result2.status() !=  StatusType::FAILURE || result3.status() !=  StatusType::FAILURE ||  result4.status() !=  StatusType::SUCCESS
        ||  result5.status() !=  StatusType::SUCCESS || result6.status() !=  StatusType::SUCCESS ||  result7.status() !=  StatusType::SUCCESS)
    {
        return false;
    }
    return true;
}
bool buy_team_TEST2() {
    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    worldCup.add_team(4);
    worldCup.add_team(5);
    worldCup.add_team(6);
    worldCup.add_team(7);

    output_t<int> result1 =  worldCup.buy_team(1,2);// expected success (empty team buys empty team)
    output_t<int> result2 = worldCup.add_team(2);// expected success
    int permut1[5] = {1, 0, 2, 3, 4};
    int permut2[5] = {0, 1, 3, 4, 2};
    int permut3[5] = {4, 2, 3, 1, 0};
    int permut4[5] = {2, 0, 1, 3, 4};
    int permut5[5] = {2, 0, 1, 3, 4};

    permutation_t spirit1(permut1); //54
    permutation_t spirit2(permut2); //52
    permutation_t spirit3(permut3); //36
    permutation_t spirit4(permut4); //52
    permutation_t spirit5(permut5); //52


    worldCup.add_player(1, 1, permut1, 10, 1, 1, true);
    worldCup.add_player(2, 2, permut2, 20, 2, 1, true);
    output_t<int> result3 =  worldCup.buy_team(2,1);// expected success

     worldCup.printAllPlayers();

    if (result1.status() !=  StatusType::SUCCESS ||result2.status() !=  StatusType::SUCCESS || result3.status() !=  StatusType::SUCCESS)
    {
        return false;
    }
    return true;
}
bool get_ith_pointless_ability1_TEST1() {
    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    worldCup.add_team(4);
    worldCup.add_team(5);
    worldCup.add_team(6);
    worldCup.add_team(7);

    output_t<int> result1 = worldCup.get_ith_pointless_ability(0);
    output_t<int> result2 = worldCup.get_ith_pointless_ability(1);
    output_t<int> result3 = worldCup.get_ith_pointless_ability(2);
    output_t<int> result4 = worldCup.get_ith_pointless_ability(3);
    output_t<int> result5 = worldCup.get_ith_pointless_ability(4);
    output_t<int> result6 = worldCup.get_ith_pointless_ability(5);
    output_t<int> result7 = worldCup.get_ith_pointless_ability(6);

    if (result1.ans()!=1 || result2.ans()!=2  || result3.ans()!=3 || result4.ans()!=4 || result5.ans()!=5|| result6.ans()!=6 || result7.ans()!=7 )
    {
        return false;
    }

    int permut1[5] = {1, 0, 2, 3, 4};
    int permut2[5] = {0, 1, 3, 4, 2};
    int permut3[5] = {4, 2, 3, 1, 0};
    int permut4[5] = {2, 0, 1, 3, 4};
    int permut5[5] = {2, 0, 1, 3, 4};

    permutation_t spirit1(permut1); //54
    permutation_t spirit2(permut2); //52
    permutation_t spirit3(permut3); //36
    permutation_t spirit4(permut4); //52
    permutation_t spirit5(permut5); //52

    worldCup.add_player(1, 1, permut1, 10, 1, 1, true);
    worldCup.add_player(2, 2, permut2, 20, 1, 1, true);
    worldCup.add_player(3, 3, permut1, 10, 1, 1, true);
    worldCup.add_player(4, 4, permut2, 20, 1, 1, true);
    worldCup.add_player(5, 5, permut1, 10, 1, 1, true);
    worldCup.add_player(6, 6, permut2, 20, 1, 1, true);
    worldCup.add_player(7, 7, permut1, 10, 1, 1, true);

    output_t<int> result11 = worldCup.get_ith_pointless_ability(0);
    output_t<int> result12 = worldCup.get_ith_pointless_ability(1);
    output_t<int> result13 = worldCup.get_ith_pointless_ability(2);
    output_t<int> result14 = worldCup.get_ith_pointless_ability(3);
    output_t<int> result15 = worldCup.get_ith_pointless_ability(4);
    output_t<int> result16 = worldCup.get_ith_pointless_ability(5);
    output_t<int> result17 = worldCup.get_ith_pointless_ability(6);

    if (result11.ans()!=1 || result12.ans()!=2  || result13.ans()!=3 || result14.ans()!=4 || result15.ans()!=5|| result16.ans()!=6 || result17.ans()!=7 )
    {
        return false;
    }
    worldCup.add_player(11, 1, permut1, 10, 70, 1, true);
    worldCup.add_player(12, 2, permut2, 20, 60, 1, true);
    worldCup.add_player(13, 3, permut1, 10, 50, 1, true);
    worldCup.add_player(14, 4, permut2, 20, 40, 1, true);
    worldCup.add_player(15, 5, permut1, 10, 30, 1, true);
    worldCup.add_player(16, 6, permut2, 20, 20, 1, true);
    worldCup.add_player(17, 7, permut1, 10, 10, 1, true);

    output_t<int> result21 = worldCup.get_ith_pointless_ability(0);
    output_t<int> result22 = worldCup.get_ith_pointless_ability(1);
    output_t<int> result23 = worldCup.get_ith_pointless_ability(2);
    output_t<int> result24 = worldCup.get_ith_pointless_ability(3);
    output_t<int> result25 = worldCup.get_ith_pointless_ability(4);
    output_t<int> result26 = worldCup.get_ith_pointless_ability(5);
    output_t<int> result27 = worldCup.get_ith_pointless_ability(6);

    if (result27.ans()!=1 || result26.ans()!=2  || result25.ans()!=3 || result24.ans()!=4 || result23.ans()!=5|| result22.ans()!=6 || result21.ans()!=7 )
    {
        return false;
    }
    return true;
}

bool get_ith_pointless_ability1_TEST2() {
    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    worldCup.add_team(4);
    worldCup.add_team(5);
    worldCup.add_team(6);
    worldCup.add_team(7);

    output_t<int> result1 = worldCup.get_ith_pointless_ability(0);
    output_t<int> result2 = worldCup.get_ith_pointless_ability(1);
    output_t<int> result3 = worldCup.get_ith_pointless_ability(2);
    output_t<int> result4 = worldCup.get_ith_pointless_ability(3);
    output_t<int> result5 = worldCup.get_ith_pointless_ability(4);
    output_t<int> result6 = worldCup.get_ith_pointless_ability(5);
    output_t<int> result7 = worldCup.get_ith_pointless_ability(6);

    if (result1.ans()!=1 || result2.ans()!=2  || result3.ans()!=3 || result4.ans()!=4 || result5.ans()!=5|| result6.ans()!=6 || result7.ans()!=7 )
    {
        return false;
    }

    int permut1[5] = {1, 0, 2, 3, 4};
    int permut2[5] = {0, 1, 3, 4, 2};
    int permut3[5] = {4, 2, 3, 1, 0};
    int permut4[5] = {2, 0, 1, 3, 4};
    int permut5[5] = {2, 0, 1, 3, 4};

    permutation_t spirit1(permut1); //54
    permutation_t spirit2(permut2); //52
    permutation_t spirit3(permut3); //36
    permutation_t spirit4(permut4); //52
    permutation_t spirit5(permut5); //52

    worldCup.add_player(1, 1, permut1, 10, 0, 1, true);
    worldCup.add_player(2, 2, permut2, 20, 0, 1, true);
    worldCup.add_player(3, 3, permut1, 10, 0, 1, true);
    worldCup.add_player(4, 4, permut2, 20, 0, 1, true);
    worldCup.add_player(5, 5, permut1, 10, 0, 1, true);
    worldCup.add_player(6, 6, permut2, 20, 0, 1, true);
    worldCup.add_player(7, 7, permut1, 10, 0, 1, true);

    output_t<int> result11 = worldCup.get_ith_pointless_ability(0);
    output_t<int> result12 = worldCup.get_ith_pointless_ability(1);
    output_t<int> result13 = worldCup.get_ith_pointless_ability(2);
    output_t<int> result14 = worldCup.get_ith_pointless_ability(3);
    output_t<int> result15 = worldCup.get_ith_pointless_ability(4);
    output_t<int> result16 = worldCup.get_ith_pointless_ability(5);
    output_t<int> result17 = worldCup.get_ith_pointless_ability(6);

    if (result11.ans()!=1 || result12.ans()!=2  || result13.ans()!=3 || result14.ans()!=4 || result15.ans()!=5|| result16.ans()!=6 || result17.ans()!=7 )
    {
        return false;
    }
    worldCup.add_player(11, 1, permut1, 10, 70, 1, true);
    worldCup.add_player(12, 2, permut2, 20, 60, 1, true);
    worldCup.add_player(13, 3, permut1, 10, 50, 1, true);
    worldCup.add_player(14, 4, permut2, 20, 40, 1, true);
    worldCup.add_player(15, 5, permut1, 10, 30, 1, true);
    worldCup.add_player(16, 6, permut2, 20, 20, 1, true);
    worldCup.add_player(17, 7, permut1, 10, 10, 1, true);

    output_t<int> result21 = worldCup.get_ith_pointless_ability(0);
    output_t<int> result22 = worldCup.get_ith_pointless_ability(1);
    output_t<int> result23 = worldCup.get_ith_pointless_ability(2);
    output_t<int> result24 = worldCup.get_ith_pointless_ability(3);
    output_t<int> result25 = worldCup.get_ith_pointless_ability(4);
    output_t<int> result26 = worldCup.get_ith_pointless_ability(5);
    output_t<int> result27 = worldCup.get_ith_pointless_ability(6);

    if (result27.ans()!=1 || result26.ans()!=2  || result25.ans()!=3 || result24.ans()!=4 || result23.ans()!=5|| result22.ans()!=6 || result21.ans()!=7 )
    {
        return false;
    }
    worldCup.buy_team(4,1);//team 4 abillity now is : 110
    worldCup.buy_team(2,3);//team 2 abillity now is : 110
    worldCup.buy_team(5,6);//team 5 abillity now is : 50
    //team 7 abillity now is : 10
    output_t<int> result31 = worldCup.get_ith_pointless_ability(0);// supposed to be team 7
    output_t<int> result32 = worldCup.get_ith_pointless_ability(1);// supposed to be team 5
    output_t<int> result33 = worldCup.get_ith_pointless_ability(2);// supposed to be team 2
    output_t<int> result34 = worldCup.get_ith_pointless_ability(3);// supposed to be team 4

    if (result31.ans()!=7 || result32.ans()!=5  || result33.ans()!=2 || result34.ans()!=4)
    {
        return false;
    }

    return true;
}
//bool remove_team_test1(){
//    world_cup_t worldCup;
//    worldCup.add_team(0);
//    worldCup.add_team(5);
//    worldCup.add_team(6);
//    worldCup.add_team(-3);
//    worldCup.add_team(54);
//    worldCup.add_team(54);
//    StatusType status101 = worldCup.add_team(5);
//    StatusType status4 = worldCup.add_team(52);
//    StatusType status11 = worldCup.add_team(-7);
//    StatusType status5 = worldCup.add_team(580);
//    StatusType status6 = worldCup.add_team(253);
//    StatusType status7 = worldCup.add_team(3);
//    StatusType status100 = worldCup.add_team(3);
//
//
//
//
//    if (status1 == StatusType::SUCCESS && status2 == StatusType::SUCCESS && status3 == StatusType::SUCCESS &&
//        status4 == StatusType::SUCCESS && status5 == StatusType::SUCCESS && status6 == StatusType::SUCCESS &&
//        status7 == StatusType::SUCCESS && status10 == StatusType::INVALID_INPUT && status11 == StatusType::INVALID_INPUT &&
//        status12 == StatusType::INVALID_INPUT && status100 == StatusType::FAILURE && status101 == StatusType::FAILURE &&
//        status102 == StatusType::FAILURE) {
//        return true;
//    }
//    return false;
//}


bool addCardsTests1(){

    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    worldCup.add_team(4);
    worldCup.add_team(5);
    worldCup.add_team(6);
    worldCup.add_team(7);

    int permut1[5] = {1,0,2,3,4};
    int permut2[5] = {0,1,3,4,2};
    int permut3[5] = {4,2,3,1,0};
    int permut4[5] = {2,0,1,3,4};

    permutation_t spirit1(permut1); //54
    permutation_t spirit2(permut2); //52
    permutation_t spirit3(permut3); //36
    permutation_t spirit4(permut4); //52


    worldCup.add_player(1,1,spirit1,5,5,5,true);
    worldCup.add_player(2,1,spirit1,5,5,0,true);
    StatusType status1 = worldCup.add_player_cards(1,5);
    StatusType status2 = worldCup.add_player_cards(0,5);
    StatusType status3 = worldCup.add_player_cards(-1,5);
    StatusType status4 = worldCup.add_player_cards(-1,-1);
    StatusType status5 = worldCup.add_player_cards(1,0);
    StatusType status6 = worldCup.add_player_cards(5,2);

    if (status1 !=StatusType::SUCCESS || status2 != StatusType::INVALID_INPUT || status3 != StatusType::INVALID_INPUT ||
            status4 != StatusType::INVALID_INPUT || status5 != StatusType::SUCCESS ||
            status6 != StatusType::FAILURE ){
        return false;
    }
    return true;
}

bool getCardsTests1(){

    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    worldCup.add_team(4);
    worldCup.add_team(5);
    worldCup.add_team(6);
    worldCup.add_team(7);

    int permut1[5] = {1,0,2,3,4};
    int permut2[5] = {0,1,3,4,2};
    int permut3[5] = {4,2,3,1,0};
    int permut4[5] = {2,0,1,3,4};

    permutation_t spirit1(permut1); //54
    permutation_t spirit2(permut2); //52
    permutation_t spirit3(permut3); //36
    permutation_t spirit4(permut4); //52


    worldCup.add_player(1,1,spirit1,5,5,5,true);
    worldCup.add_player(2,1,spirit1,5,5,0,true);
    worldCup.add_player_cards(1,5);
    worldCup.add_player_cards(5,2);
    worldCup.add_player_cards(2,80);
    worldCup.add_player(3,1,permut1,0,0,1997,true);

    output_t<int> status1 = worldCup.get_player_cards(1);
    output_t<int> status2 = worldCup.get_player_cards(2);
    output_t<int> status3 = worldCup.get_player_cards(3);
    output_t<int> status4 = worldCup.get_player_cards(4);
    output_t<int> status5 = worldCup.get_player_cards(-4);
    output_t<int> status6 = worldCup.get_player_cards(0);
    worldCup.remove_team(1);
    output_t<int> status7 = worldCup.get_player_cards(1);


    if (status1.ans() != 10 || status2.ans() != 80 || status3.ans() != 1997 ||
        status4.status() != StatusType::FAILURE || status5.status() != StatusType::INVALID_INPUT ||
        status6.status() != StatusType::INVALID_INPUT || status7.ans() != 10 ){
        return false;
    }
    return true;
}
int main() {
    if (!run_test(getNumOfPlayedGamesTest1, "getNumOfPlayedGamesTest1"))
        return 1;
    if (!run_test(addTeamTest1, "addTeamTest1"))
        return 1;
    if (!run_test(removeTeamTest1, "removeTeamTest1"))
        return 1;
    if (!run_test(addPlayerTest1, "addPlayerTest1"))
        return 1;
    if (!run_test(playMatchTest1, "playMatchTest1"))
        return 1;
    if (!run_test(playMatchTest2, "playMatchTest2"))
        return 1;
    if (!run_test(playMatchTest3, "playMatchTest3"))
        return 1;
    if (!run_test(getPartialTest1, "getPartialTest1"))
        return 1;
    if (!run_test(num_played_games_for_player_TEST2, "num_played_games_for_player_TEST2"))
        return 1;
    if (!run_test(num_played_games_for_player_TEST3, "num_played_games_for_player_TEST3"))
        return 1;
    if (!run_test(addCardsTests1, "addCardsTests1"))
        return 1;
    if (!run_test(getCardsTests1, "getCardsTests1"))
        return 1;
    if (!run_test(buy_team_TEST1, "buy_team_TEST1"))
        return 1;
    if (!run_test(buy_team_TEST2, "buy_team_TEST2"))
        return 1;
    if (!run_test(get_ith_pointless_ability1_TEST1, "get_ith_pointless_ability1_TEST1"))
        return 1;
    if (!run_test(get_ith_pointless_ability1_TEST2, "get_ith_pointless_ability1_TEST2"))
        return 1;
    return 0;
}