#include "worldcup23a2.h"

AVL_Tree<Team> teamsRankTree;
playerUnionFind unionFind;
Linked_List<Team> deletedTeamsList;


world_cup_t::world_cup_t() :teamsRankTree(), unionFind(), deletedTeamsList(), numOfTeams(0)
{

}

world_cup_t::~world_cup_t()
{
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
        teamsRankTree.insert(new Team(teamId));
        teamsByAbilityRankTree.insert(new teamByAbility(teamId));
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

    teamsRankTree.Delete(team);
    teamsByAbilityRankTree.Delete(team->getTeamByAbility());
    numOfTeams--;
    team->setIsActive(false);

    try {
        deletedTeamsList.insert(team);
    } catch (bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
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
        team->setIsActive(true);
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
        updateTeamByAbilityTree(teamId1,numberOfPointsUponVictory);
    }
    else if (team1Score < team2Score){
        result = 3;
        team2->increasePoints(numberOfPointsUponVictory);
        updateTeamByAbilityTree(teamId2,numberOfPointsUponVictory);
    }
    else{      //ability and team points are equal
        permutation_t team1Permut = team1->getTeamTotalSpirit();
        permutation_t team2Permut = team2->getTeamTotalSpirit();
        int team1SpiritStrength = team1Permut.strength();
        int team2SpiritStrength = team2Permut.strength();
        if(team1SpiritStrength > team2SpiritStrength){
            result = 2;
            team1->increasePoints(numberOfPointsUponVictory);
            updateTeamByAbilityTree(teamId1,numberOfPointsUponVictory);
        }
        else if( team1SpiritStrength < team2SpiritStrength){
            result = 4;
            team2->increasePoints(numberOfPointsUponVictory);
            updateTeamByAbilityTree(teamId2,numberOfPointsUponVictory);
        }
        else{ //there is a tie
            result = 0;
            team1->increasePoints(numberOfPointsUponTie);
            updateTeamByAbilityTree(teamId1,numberOfPointsUponTie);
            team2->increasePoints(numberOfPointsUponTie);
            updateTeamByAbilityTree(teamId2,numberOfPointsUponTie);

        }
    }
    team1->incNumOfGamesPlayed(1);
    team2->incNumOfGamesPlayed(1);
	return StatusType::SUCCESS;
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
    return unionFind.getPlayerNumOfGamesPlayed(player);
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    //input check
    if (playerId <= 0 || cards <=0){
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
    int IdToReturn=  this->teamsByAbilityRankTree.select(i)->getId();
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

	return unionFind.getPlayerSpiral(player);

}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	//input check
    if (teamId1 <= 0 || teamId2 <=0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    Team* team1 = searchTeamTree(teamId1);
    Team* team2 = searchTeamTree(teamId2);
    if (team1 == nullptr || team2 == nullptr){
        return  StatusType::FAILURE;
    }
    unionFind.playerUnion(team1, team2);

    //updating team1 stats
    team1->increasePoints(team2->getPoints());
    team1->increaseTeamAbility(team2->getTeamAbility());
    updateTeamByAbilityTree(teamId1,team2->getTeamAbility());
    team1->updateTeamSpiritRightSide(team2->getTeamTotalSpirit());
    //if the bought team was qualified, now team1 is also qualified
    if (team2->getIsQualified()){
        team1->setIsQualified(true);
    }
    remove_team(teamId2);
    teamsByAbilityRankTree.Delete(team2->getTeamByAbility());
    numOfTeams--;
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

 void world_cup_t::updateTeamByAbilityTree(int teamID, int toInc)  {
    teamByAbility* team1 = searchTeamByAbilityTree(teamID);
    this->teamsByAbilityRankTree.Delete(team1);
    team1->IncTeamAbility(toInc);
    teamsByAbilityRankTree.insert(team1);
}

teamByAbility *world_cup_t::searchTeamByAbilityTree(int teamId) const {
    teamByAbility tempTeam = teamByAbility(teamId);
    teamByAbility* tempTeamPtr = &tempTeam;
    StatusType tempStatus = StatusType::SUCCESS;
    StatusType* tempStatusPtr = &tempStatus;
    teamByAbility* team = teamsByAbilityRankTree.search(tempTeamPtr,tempStatusPtr);
    return team;
}
