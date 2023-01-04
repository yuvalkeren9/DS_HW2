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
    long long int numberOfGamesTeamPlayedBeforeInit;
    Team* team;


public:
    Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper) : playerId(playerId),
    teamId(teamId), spirit(spirit), gamesPlayed(gamesPlayed), ability(ability), cards(cards), goalKeeper(goalKeeper),numberOfGamesTeamPlayedBeforeInit(0),  team(nullptr){};
    int getPlayerId() const;
    permutation_t getSpirit() const;  //?
    Team* getTeam() const;


    long long int getNumberOfGamesTeamPlayedBeforeInit() const;
    void setNumberOfGamesTeamPlayedBeforeInit(long long int toSet) ;

    int getNumOfCards() const;
    int get_games_played() const;
    void incNumOfCards(int cardsToAdd);
    void setTeam(Team* teamToSet);

};


#endif //DS2_PLAYER_H
