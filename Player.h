//
// Created by יובל קרן on 12/20/2022.
//

#ifndef DS2_PLAYER_H
#define DS2_PLAYER_H

#include "wet2util.h"
#include "Team.h"

class Player {
    int playerId;
    int teamId;
    const permutation_t& spirit;
    int gamesPlayed;
    int ability;
    int cards;
    bool goalKeeper;
    int numberOfGamesTeamPlayedBeforeInit;
    Team* team;


public:
    Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper) : playerId(playerId),
    teamId(teamId), spirit(spirit), gamesPlayed(gamesPlayed), ability(ability), cards(cards),numberOfGamesTeamPlayedBeforeInit(0), goalKeeper(goalKeeper), team(nullptr){};
    int getPlayerId() const;
    permutation_t getSpirit() const;  //?
    Team* getTeam() const;

    void setTeam(Team* teamToSet);

};


#endif //DS2_PLAYER_H
