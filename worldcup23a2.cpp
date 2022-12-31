#include "worldcup23a2.h"
#include <cassert>


AVL_Tree<Team> teamsRankTree;
playerUnionFind unionFind;
Linked_List<Team> deletedTeamsList;


world_cup_t::world_cup_t() :teamsRankTree(),teamsByAbilityRankTree(), unionFind(), deletedTeamsList(), numOfTeams(0)
{
}

world_cup_t::~world_cup_t()
{
    teamsByAbilityRankTree.emptyTree();
    teamsRankTree.emptyTree();
}

StatusType world_cup_t::add_team(int teamId)
{
    //input check
	if (teamId <= 0){
		return StatusType::INVALID_INPUT;
	}
    if(searchTeamTree(teamId) != nullptr){
        return StatusType::FAILURE;
    }
    try {
        Team* team =new Team(teamId);
        teamsRankTree.insert(team);
        teamByAbility* teamRocket = new teamByAbility(teamId);
        team->setTeamByAbilityPtr(teamRocket);
        teamsByAbilityRankTree.insert(teamRocket);
        numOfTeams++;
    } catch(bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	//input check
    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Team* team = searchTeamTree(teamId);
    if (team == nullptr){
        return  StatusType::FAILURE;
    }

    teamsByAbilityRankTree.Delete(team->getTeamByAbility());
    delete (team->getTeamByAbility());
    teamsRankTree.Delete(team);
    numOfTeams--;
    team->setIsActive(false);

    if (team->getNumOfPlayersInTeam() != 0) {
        try {
            deletedTeamsList.insert(team);
        } catch (bad_alloc &e) {
            return StatusType::ALLOCATION_ERROR;
        }
    }
    else{
        delete team;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    //input check
    if (playerId <=0 || teamId <=0 || !spirit.isvalid() || gamesPlayed < 0 || cards < 0){
        return StatusType::INVALID_INPUT;
    }
    Team* team = searchTeamTree(teamId);
    if (team == nullptr){
        return StatusType::FAILURE;
    }
    Player* temp = unionFind.findPlayer(playerId);
    if (temp != nullptr){
        return StatusType::FAILURE;
    }
    auto player = new Player(playerId, teamId, spirit, gamesPlayed, ability, cards, goalKeeper);
    player->setTeam(team);
    unionFind.insertPlayer(player);

    team->increaseNumberOfPlayers(1);
    team->increaseTeamAbility(ability);
    updateTeamByAbilityTree(teamId,ability);    //update teamByAbilityTREE
    team->updateTeamSpiritRightSide(spirit);

    if (goalKeeper == true){
        team->setIsQualified(true);
    }
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    //input check
    if(teamId1 <=0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }

    Team* team1 = searchTeamTree(teamId1);
    Team* team2 = searchTeamTree(teamId2);

    if(team1 == nullptr || team2 == nullptr){
        return StatusType::FAILURE;
    }
    if (team1->getIsQualified() == false || team2->getIsQualified() == false){
        return StatusType::FAILURE;
    }

    static int numberOfPointsUponVictory = 3;
    static int numberOfPointsUponTie = 1;

    //starting match
    int result = 0;
    long long int team1Score = team1->getTeamTotalScore();
    long long int team2Score = team2->getTeamTotalScore();
    if (team1Score > team2Score){
        result = 1;
        team1->increasePoints(numberOfPointsUponVictory);
    }
    else if (team1Score < team2Score){
        result = 3;
        team2->increasePoints(numberOfPointsUponVictory);
    }
    else{      //ability and team points are equal
        permutation_t team1Permut = team1->getTeamTotalSpirit();
        permutation_t team2Permut = team2->getTeamTotalSpirit();
        int team1SpiritStrength = team1Permut.strength();
        int team2SpiritStrength = team2Permut.strength();
        if(team1SpiritStrength > team2SpiritStrength){
            result = 2;
            team1->increasePoints(numberOfPointsUponVictory);
        }
        else if( team1SpiritStrength < team2SpiritStrength){
            result = 4;
            team2->increasePoints(numberOfPointsUponVictory);
        }
        else{ //there is a tie
            result = 0;
            team1->increasePoints(numberOfPointsUponTie);
            team2->increasePoints(numberOfPointsUponTie);

        }
    }
    team1->incNumOfGamesPlayed(1);
    team2->incNumOfGamesPlayed(1);
	return result;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    //input check
    if (playerId <=0){
        return StatusType::INVALID_INPUT;
    }
    Player* player = unionFind.findPlayer(playerId);
    if(player == nullptr){
        return StatusType::FAILURE;
    }
    return player->get_games_played() + unionFind.getPlayerNumOfGamesPlayed(player);
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    //input check
    if (playerId <= 0 || cards <0){
        return StatusType::INVALID_INPUT;
    }

    //finding the player in the hashMap
    Player* player = unionFind.findPlayer(playerId);
    if(player == nullptr){
        return StatusType::FAILURE;
    }
    Team* team = unionFind.findTeamRootNode(player);
    if (team->getIsActive() == false){
        return StatusType::FAILURE;
    }
    player->incNumOfCards(cards);
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    //input check
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Player* player = unionFind.findPlayer(playerId);
    if(player == nullptr){
        return StatusType::FAILURE;
    }
	return player->getNumOfCards();
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Team* team = searchTeamTree(teamId);
    if(team == nullptr){
        return StatusType::FAILURE;
    }
	return team->getPoints();
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    if(i>= this->numOfTeams || i< 0 || numOfTeams == 0)
    {
        return StatusType::FAILURE;
    }
    i++;//shifting the index to right value
    teamByAbility* team =teamsByAbilityRankTree.select(i);
    assert(team!= nullptr);
    int IdToReturn=  team->getId();
    return  IdToReturn;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    //input check
    if(playerId <=0){
        return StatusType::INVALID_INPUT;
    }

    Player* player = unionFind.findPlayer(playerId);
    if (player == nullptr){
        return StatusType::FAILURE;
    }

    //adding lines
    Team* team = unionFind.findTeamRootNode(player);
    if (team->getIsActive() == false){
        return StatusType::FAILURE;
    }
    //stopped adding lines
	return unionFind.getPlayerSpiral(player);

}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
    if(teamId1 == 100 && teamId2 == 87){
        int meow = 5;    //TODO: REMOVE
    }
	//input check
    if (teamId1 <= 0 || teamId2 <=0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    Team* team1 = searchTeamTree(teamId1);
    Team* team2 = searchTeamTree(teamId2);
    if (team1 == nullptr || team2 == nullptr){
        return  StatusType::FAILURE;
    }

    //edge cases
    if(team2->getNumOfPlayersInTeam()== 0) {//empty team was bought
        remove_team(teamId2);
        return StatusType::SUCCESS;
    }
    if(team1->getNumOfPlayersInTeam()== 0 )// empty team buys not empty team
    {
        team1->copyTeamStats(team2);  //Team1 get team 2 stats without id and without team ability
        Node* team1Rep = team1->getTeamRepresentative();
        team1Rep->team = team1;
        Node* team2Rep = team2->getTeamRepresentative();
        team2Rep->team=team1;////now the representive of team2 points to team1
        updateTeamByAbilityTree(teamId1,team2->getTeamAbility());
        remove_team(teamId2);
        return StatusType::SUCCESS;

    }

    unionFind.playerUnion(team1, team2);

    //updating team1 stats
    team1->increasePoints(team2->getPoints());
    team1->increaseTeamAbility(team2->getTeamAbility());
    updateTeamByAbilityTree(teamId1,team2->getTeamAbility());
    team1->updateTeamSpiritRightSide(team2->getTeamTotalSpirit());
    team1->increaseNumberOfPlayers(team2->getNumOfPlayersInTeam());
    //if the bought team was qualified, now team1 is also qualified
    if (team2->getIsQualified()){
        team1->setIsQualified(true);
    }
    remove_team(teamId2);
//    teamsByAbilityRankTree.Delete(team2->getTeamByAbility());
    return StatusType::SUCCESS;
}

Team *world_cup_t::searchTeamTree(int teamId) const {
    Team tempTeam = Team(teamId);
    Team* tempTeamPtr = &tempTeam;
    StatusType tempStatus = StatusType::SUCCESS;
    StatusType* tempStatusPtr = &tempStatus;
    Team* team = teamsRankTree.search(tempTeamPtr,tempStatusPtr);
    return team;
}

 void world_cup_t::updateTeamByAbilityTree(int teamId, int toInc)  {
    Team *tempTeam = searchTeamTree(teamId);
    teamByAbility* team1 =tempTeam->getTeamByAbility();
    this->teamsByAbilityRankTree.Delete(team1);
    team1->IncTeamAbility(toInc);
    teamsByAbilityRankTree.insert(team1);
}

void world_cup_t::printAllPlayers() {
    unionFind.print();
}


