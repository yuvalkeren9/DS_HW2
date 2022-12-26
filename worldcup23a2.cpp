#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
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
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    //TODO: this function. Made fake impllnation for testing
    Team* team1 = searchTeamTree(teamId1);
    Team* team2 = searchTeamTree(teamId2);

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
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
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
